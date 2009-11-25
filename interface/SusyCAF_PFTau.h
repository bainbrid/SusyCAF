#ifndef SUSY_CAF_PFTAU
#define SUSY_CAF_PFTAU

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include <string>

template< typename T >
class SusyCAF_PFTau : public edm::EDProducer {
 public: 
  explicit SusyCAF_PFTau(const edm::ParameterSet&);
 private: 
  void produce(edm::Event &, const edm::EventSetup & );

  typedef reco::Candidate::LorentzVector LorentzVector;
  const edm::InputTag inputTag;
  const std::string Prefix,Suffix;
};

template< typename T >
SusyCAF_PFTau<T>::SusyCAF_PFTau(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
  Prefix(iConfig.getParameter<std::string>("Prefix")),
  Suffix(iConfig.getParameter<std::string>("Suffix"))
{
  produces <std::vector<LorentzVector> > ( Prefix + "P4" + Suffix );
  produces <std::vector<int> > (  Prefix + "Charge" + Suffix);
  produces <std::vector<float> > (Prefix + "IsoPFGammaCandsEtSum" + Suffix);
  produces <std::vector<float> > (Prefix + "MaxHcalPFCluster" + Suffix);
  produces <std::vector<float> > ( Prefix + "IsoPFChargHadrCandsPtSum" + Suffix);
 
}

template< typename T >
void SusyCAF_PFTau<T>::

produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  std::auto_ptr<std::vector<LorentzVector> > p4 ( new std::vector<LorentzVector>() );
  std::auto_ptr<std::vector<int> >  charge   ( new std::vector<int>()  ) ;
  std::auto_ptr<std::vector<float> > isoPFChargeCands (new std::vector<float>() );
 std::auto_ptr<std::vector<float> > isoPFGammaCands (new std::vector<float>() );
 std::auto_ptr<std::vector<float> > maxHcalPFCluster (new std::vector<float>() );
 
  
  edm::Handle<std::vector<T> > collection;
  iEvent.getByLabel(inputTag,collection);

  
  for(typename std::vector<T>::const_iterator it = collection->begin(); it!=collection->end(); it++) {
   

    p4->push_back(it->p4());
    charge->push_back(it->charge());
    isoPFChargeCands->push_back(it->isolationPFChargedHadrCandsPtSum());
    isoPFGammaCands->push_back(it->isolationPFGammaCandsEtSum());
    maxHcalPFCluster->push_back(it->maximumHCALPFClusterEt());
 
     

  }
  
  iEvent.put( p4,  Prefix + "P4" + Suffix );
  iEvent.put( charge,  Prefix + "Charge" + Suffix );
  iEvent.put (isoPFChargeCands, Prefix + "IsoPFChargHadrCandsPtSum" + Suffix);
  iEvent.put (isoPFGammaCands, Prefix + "IsoPFGammaCandsEtSum" + Suffix);
  iEvent.put (maxHcalPFCluster, Prefix + "MaxHcalPFCluster" + Suffix);
 


}

#endif
