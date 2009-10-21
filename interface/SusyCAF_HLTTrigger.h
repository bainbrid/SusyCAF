#ifndef SUSY_CAF_HLTTRIGGER
#define SUSY_CAF_HLTTRIGGER

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/TriggerNames.h"

class SusyCAF_HLTTrigger : public edm::EDProducer 
{
public: 
  explicit SusyCAF_HLTTrigger(const edm::ParameterSet&);
private: 
  void produce( edm::Event &, const edm::EventSetup & );

  edm::InputTag   hltresults_;
  edm::InputTag   inputTag;
  std::string     prefix,suffix;
  edm::TriggerNames triggerNames_;
  std::vector<std::string> hlNames_;
};

#endif
