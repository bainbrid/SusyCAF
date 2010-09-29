#ifndef SUSY_CAF_ECALRECHIT
#define SUSY_CAF_ECALRECHIT

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "CondFormats/EcalObjects/interface/EcalChannelStatus.h"
#include "CalibCalorimetry/EcalTPGTools/interface/EcalTPGScale.h"

class SusyCAF_EcalRecHit : public edm::EDProducer {
 public: 
  explicit SusyCAF_EcalRecHit(const edm::ParameterSet&);
 private: 
  void produce(edm::Event&,const edm::EventSetup&);
  const edm::InputTag inputTag;
  const std::string Prefix,Suffix;
	  
  EcalTPGScale ecalScale_;
};

#endif
