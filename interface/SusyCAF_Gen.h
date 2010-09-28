#ifndef SusyCAF_GEN
#define SusyCAF_GEN

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include <map>

template< typename T >
class SusyCAF_Gen : public edm::EDProducer {
 public:
  explicit SusyCAF_Gen(const edm::ParameterSet&);
 private:
  void produce(edm::Event &, const edm::EventSetup & );
  static int index(const reco::Candidate*, const std::vector<T>&);
  typedef reco::Candidate::LorentzVector LorentzVector;
  const edm::InputTag inputTag;
  const std::string Prefix,Suffix;
  const double GenStatus1PtCut;
};

template< typename T >
SusyCAF_Gen<T>::SusyCAF_Gen(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
  Prefix(iConfig.getParameter<std::string>("Prefix")),
  Suffix(iConfig.getParameter<std::string>("Suffix")),
  GenStatus1PtCut(iConfig.getParameter<double>("GenStatus1PtCut"))
 {
  produces <bool>   (Prefix + "GenInfoHandleValid" + Suffix);
  produces <double> (Prefix + "pthat" + Suffix);
  produces <bool >  (Prefix + "HandleValid" + Suffix);
  produces <std::vector<LorentzVector> > ( Prefix + "P4"  + Suffix );
  produces <std::vector<int> > (Prefix + "PdgId" + Suffix);
  produces <std::vector<int> > (Prefix + "Status" + Suffix);
  produces <std::vector<int> > (Prefix + "MotherIndex" + Suffix);
  produces <std::vector<int> > (Prefix + "MotherPdgId" + Suffix);
}

template< typename T >
int SusyCAF_Gen<T>::
index(const reco::Candidate* item, 
      const typename std::vector<T>& collection) 
{
  typename std::vector<T>::const_iterator
    it = collection.begin(),
    end = collection.end();
  //Compare addresses
  for(; it!=end; it++) { if (&(*it)==item) { return it - collection.begin(); } }
  return -2;
}

template< typename T >
void SusyCAF_Gen<T>::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  edm::Handle<std::vector<T> > collection;
  edm::Handle<GenEventInfoProduct> geninfo;
  iEvent.getByLabel(inputTag,collection);
  iEvent.getByLabel("generator",geninfo);

  // Check if pthat variable is available
  std::auto_ptr<bool> isGenInfoValid (new bool(geninfo.isValid()));
  std::auto_ptr<double> pthat (new double(-1.));
  if ( *isGenInfoValid && !geninfo->binningValues().empty() ) { pthat.reset( new double(geninfo->binningValues()[0]) ); }
  else { isGenInfoValid.reset( new bool(false) ); }

  std::auto_ptr<bool> isHandleValid ( new bool(collection.isValid()) );
  std::auto_ptr<std::vector<LorentzVector> >  p4  ( new std::vector<LorentzVector>()  ) ;
  std::auto_ptr<std::vector<int> > status ( new std::vector<int>() ) ;
  std::auto_ptr<std::vector<int> > pdgId ( new std::vector<int>() ) ;
  std::auto_ptr<std::vector<int> > motherIndex ( new std::vector<int>() ) ;
  std::auto_ptr<std::vector<int> > motherPdgId ( new std::vector<int>() ) ;

  if(collection.isValid()){
    for(typename std::vector<T>::const_iterator it = collection->begin(); it != collection->end(); ++it) {
      if ( it->status() == 3         // any status 3 genParticle
	   || abs(it->pdgId()) == 11 // any electron
	   || abs(it->pdgId()) == 13 // any muon
	   || abs(it->pdgId()) == 15 // any tau
	   || ( it->status() == 1    //        status 1 particles
		&& it->pt() > GenStatus1PtCut) // above threshold
	   ) {
        p4->push_back(it->p4());
        status->push_back(it->status());
        pdgId->push_back(it->pdgId());
	motherIndex->push_back( it->numberOfMothers() ? index(it->mother(),*collection) : -1 );
	motherPdgId->push_back( it->numberOfMothers() ? it->mother()->pdgId()          :  0 );
      }
    }
  }
    
  iEvent.put( isGenInfoValid, Prefix + "GenInfoHandleValid" + Suffix);
  iEvent.put( pthat,          Prefix + "pthat" + Suffix);
  iEvent.put( isHandleValid,  Prefix + "HandleValid"          + Suffix);
  iEvent.put( p4,             Prefix + "P4"  + Suffix );
  iEvent.put( status,         Prefix + "Status" + Suffix );
  iEvent.put( pdgId,          Prefix + "PdgId" + Suffix );
  iEvent.put( motherIndex,    Prefix + "MotherIndex" + Suffix );
  iEvent.put( motherPdgId,    Prefix + "MotherPdgId" + Suffix );
}

#endif
