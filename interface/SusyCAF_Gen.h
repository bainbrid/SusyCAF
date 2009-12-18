#ifndef ICF_GEN
#define ICF_GEN

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include <map>

template< typename T >
class ICF_Gen : public edm::EDProducer {
 public:
  explicit ICF_Gen(const edm::ParameterSet&);
 private:
  void produce(edm::Event &, const edm::EventSetup & );
  typedef reco::Candidate::LorentzVector LorentzVector;
  const edm::InputTag inputTag;
  const std::string Prefix,Suffix;
};

template< typename T >
ICF_Gen<T>::ICF_Gen(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
  Prefix(iConfig.getParameter<std::string>("Prefix")),
  Suffix(iConfig.getParameter<std::string>("Suffix"))
{
  produces <bool                        >(Prefix + "HandleValid"          + Suffix);
  produces <std::vector<LorentzVector> > ( Prefix + "P4"  + Suffix );
  produces <std::vector<int> > (Prefix + "PdgId" + Suffix);
  produces <std::vector<int> > (Prefix + "Status" + Suffix);
  produces <std::vector<bool> > (Prefix + "HasMother" + Suffix);
  produces <std::vector<int> > (Prefix + "Mother" + Suffix);
  produces <std::vector<bool> > (Prefix + "MotherStored" + Suffix);
}

template< typename T >
void ICF_Gen<T>::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  edm::Handle<std::vector<T> > collection;
  iEvent.getByLabel(inputTag,collection);
  std::auto_ptr<bool                        > isHandleValid       ( new bool(collection.isValid())    );
  std::auto_ptr<std::vector<LorentzVector> >  p4  ( new std::vector<LorentzVector>()  ) ;
  std::auto_ptr<std::vector<int> > status ( new std::vector<int>() ) ;
  std::auto_ptr<std::vector<int> > pdgId ( new std::vector<int>() ) ;
  std::auto_ptr<std::vector<bool> > hasMother ( new std::vector<bool>() ) ;
  std::auto_ptr<std::vector<int> > mother ( new std::vector<int>() );
  std::auto_ptr<std::vector<bool> > motherStored ( new std::vector<bool>() );
  std::map<const reco::Candidate*,int> refs;
  if(collection.isValid()){
    int idx_gen=0;
    for(typename std::vector<T>::const_iterator it = collection->begin(); it != collection->end(); ++it,++idx_gen) {
      if(it->status()==3 ||
         (abs(it->pdgId())==11 | abs(it->pdgId())==13)){
        p4->push_back(it->p4());
        status->push_back(it->status());
        pdgId->push_back(it->pdgId());
        hasMother->push_back(it->numberOfMothers()>0);
        refs[dynamic_cast<const reco::Candidate*>(&(*it))]=idx_gen++;
      }
    }
    for(typename std::vector<T>::const_iterator it = collection->begin(); it != collection->end(); ++it) {
      if(it->numberOfMothers()>0){
        const reco::Candidate* mom = it->mother();
        if (mom->pdgId() == it->pdgId()) { mom = mom->mother(); }
        if(mom==0) continue;
        if(refs.count(mom)>0){
          motherStored->push_back(true);
          mother->push_back(refs[mom]);
        }
        else{
          mother->push_back(mom->pdgId());
          motherStored->push_back(false);
        }
      }
    }
  }

  iEvent.put(isHandleValid        , Prefix + "HandleValid"          + Suffix);
  iEvent.put( p4,  Prefix + "P4"  + Suffix );
  iEvent.put( status, Prefix + "Status" + Suffix );
  iEvent.put( pdgId, Prefix + "PdgId" + Suffix );
  iEvent.put( hasMother, Prefix + "HasMother" + Suffix );
  iEvent.put( mother, Prefix + "Mother" + Suffix );
  iEvent.put( motherStored, Prefix + "MotherStored" + Suffix );
}

#endif
