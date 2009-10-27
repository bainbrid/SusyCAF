#ifndef SUSY_CAF_CALOTAU
#define SUSY_CAF_CALOTAU

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include <string>

template< typename T >
class SusyCAF_CaloTau : public edm::EDProducer {
 public: 
  explicit SusyCAF_CaloTau(const edm::ParameterSet&);
 private: 
  void produce(edm::Event &, const edm::EventSetup & );

  typedef reco::Candidate::LorentzVector LorentzVector;
  const edm::InputTag inputTag;
  const std::string Prefix,Suffix;
};

template< typename T >
SusyCAF_CaloTau<T>::SusyCAF_CaloTau(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
  Prefix(iConfig.getParameter<std::string>("Prefix")),
  Suffix(iConfig.getParameter<std::string>("Suffix"))
{
  produces <std::vector<LorentzVector> > ( Prefix + "P4" + Suffix );
  produces <std::vector<int> > (  Prefix + "Charge" + Suffix);

  produces <std::vector<float> > ( Prefix + "IsolationTracksPtsum" + Suffix);
produces <std::vector<float> > ( Prefix + "IsolationECALhitsEtSum" + Suffix);
produces <std::vector<float> > ( Prefix + "leadTrkHCAL3x3hitsEtSum" + Suffix);


}

template< typename T >
void SusyCAF_CaloTau<T>::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  std::auto_ptr<std::vector<LorentzVector> > p4 ( new std::vector<LorentzVector>() );
  std::auto_ptr<std::vector<int> >  charge   ( new std::vector<int>()  ) ;

  std::auto_ptr<std::vector<float> > isoTracksPtSum (new std::vector<float>() );
  std::auto_ptr<std::vector<float> > isoECALhitsEtSum (new std::vector<float>() );
  std::auto_ptr<std::vector<float> > leadTrkHCAL3x3hitsEtSum (new std::vector<float>() );
 
  
  edm::Handle<std::vector<T> > collection;
  iEvent.getByLabel(inputTag,collection);
  
  for(typename std::vector<T>::const_iterator it = collection->begin(); it!=collection->end(); it++) {
   
    p4->push_back(it->p4());
    charge->push_back(it->charge());
     isoTracksPtSum->push_back(it->isolationTracksPtSum());
     isoECALhitsEtSum->push_back(it->isolationECALhitsEtSum());
     leadTrkHCAL3x3hitsEtSum->push_back(it->leadTrackHCAL3x3hitsEtSum());

  }
  
  iEvent.put( p4,  Prefix + "P4" + Suffix );
  iEvent.put( charge,  Prefix + "Charge" + Suffix );
  iEvent.put (isoTracksPtSum, Prefix + "IsolationTracksPtsum" + Suffix);
  iEvent.put (isoECALhitsEtSum, Prefix + "IsolationECALhitsEtSum" + Suffix);
  iEvent.put (leadTrkHCAL3x3hitsEtSum,  Prefix + "leadTrkHCAL3x3hitsEtSum" + Suffix);

}

#endif
