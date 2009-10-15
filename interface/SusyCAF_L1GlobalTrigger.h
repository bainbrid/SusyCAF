#ifndef SUSY_CAF_L1GLOBALTRIGGER
#define SUSY_CAF_L1GLOBALTRIGGER

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

class SusyCAF_L1GlobalTrigger : public edm::EDProducer {
 public: 
  explicit SusyCAF_L1GlobalTrigger(const edm::ParameterSet&);
 private: 
  void produce( edm::Event &, const edm::EventSetup & );

  const edm::InputTag inputTag;
  int nBxOutput;
};

#endif
