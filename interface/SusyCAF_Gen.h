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
  void produceGenJets(edm::Event &);
  static int index(const reco::Candidate*, const std::vector<const T*>&);
  typedef reco::Candidate::LorentzVector LorentzVector;
  const edm::InputTag inputTag;
  const std::vector<edm::InputTag> jetCollections;
  const std::string Prefix,Suffix;
  const double GenStatus1PtCut;
};

template< typename T > SusyCAF_Gen<T>::
SusyCAF_Gen(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
  jetCollections(iConfig.getParameter<std::vector<edm::InputTag> >("JetCollections")),
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

  for(unsigned i=0; i<jetCollections.size(); ++i)
    produces<std::vector<LorentzVector> >(Prefix + jetCollections[i].label() +"P4" + Suffix);
}

template< typename T > int SusyCAF_Gen<T>::
index(const reco::Candidate* item, const typename std::vector<const T*>& collection) {
  typename std::vector<const T*>::const_iterator it(collection.begin()), begin(collection.begin()), end(collection.end());
  for(; it!=end; it++) if ((*it)==item) return it-begin; //Compare addresses
  return -2;
}

template< typename T > void SusyCAF_Gen<T>::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  produceGenJets(iEvent);

  edm::Handle<std::vector<T> > collection;   iEvent.getByLabel(inputTag,collection);
  edm::Handle<GenEventInfoProduct> geninfo;  iEvent.getByLabel("generator",geninfo);

  std::auto_ptr<bool> handleValid ( new bool(collection.isValid()) );
  std::auto_ptr<bool> genInfoValid ( new bool( geninfo.isValid() && !geninfo->binningValues().empty()));
  std::auto_ptr<double> pthat (new double(*genInfoValid ? geninfo->binningValues()[0] : -1.));
  std::auto_ptr<std::vector<LorentzVector> >  p4  ( new std::vector<LorentzVector>()  ) ;
  std::auto_ptr<std::vector<int> > status ( new std::vector<int>() ) ;
  std::auto_ptr<std::vector<int> > pdgId ( new std::vector<int>() ) ;
  std::auto_ptr<std::vector<int> > motherIndex ( new std::vector<int>() ) ;
  std::auto_ptr<std::vector<int> > motherPdgId ( new std::vector<int>() ) ;
  std::vector<const T*> self;
  std::vector<const reco::Candidate*> mom;

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
	motherPdgId->push_back( it->numberOfMothers() ? it->mother()->pdgId() : 0 );
	self.push_back(&*it);
	mom.push_back( it->numberOfMothers() ? it->mother(): 0);
      }
    }
  }
  for(typename std::vector<const reco::Candidate*>::const_iterator it = mom.begin(); it!=mom.end(); ++it)
    motherIndex->push_back( index(*it,self) );

  iEvent.put( handleValid,  Prefix + "HandleValid"        + Suffix);
  iEvent.put( genInfoValid, Prefix + "GenInfoHandleValid" + Suffix);
  iEvent.put( pthat,        Prefix + "pthat"  + Suffix);
  iEvent.put( p4,           Prefix + "P4"     + Suffix );
  iEvent.put( status,       Prefix + "Status" + Suffix );
  iEvent.put( pdgId,        Prefix + "PdgId"  + Suffix );
  iEvent.put( motherIndex,  Prefix + "MotherIndex" + Suffix );
  iEvent.put( motherPdgId,  Prefix + "MotherPdgId" + Suffix );
}

template< typename T > void SusyCAF_Gen<T>::
produceGenJets(edm::Event& iEvent) {
  for(unsigned i=0; i<jetCollections.size(); ++i) {
    std::auto_ptr<std::vector<LorentzVector> > p4(new std::vector<LorentzVector>());
    edm::Handle<edm::View<reco::GenJet> > genjets;
    iEvent.getByLabel(jetCollections[i], genjets);
    if(genjets.isValid()) 
      for(edm::View<reco::GenJet>::const_iterator it(genjets->begin()), end(genjets->end()); it!=end; ++it) {
	//if (it->pt() < GenStatus1PtCut ) break;
	p4->push_back(it->p4());
      }
    iEvent.put(p4, Prefix + jetCollections[i].label() + "P4" + Suffix);
  }
}

#endif
