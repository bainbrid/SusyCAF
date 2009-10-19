#ifndef SUSY_CAF_PHOTON
#define SUSY_CAF_PHOTON

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

class SusyCAF_Photon : public edm::EDProducer 
{
public: 
  explicit SusyCAF_Photon(const edm::ParameterSet&);
private: 
  void produce( edm::Event &, const edm::EventSetup & );

  const edm::InputTag   inputTag;
  const std::string     prefix,suffix;
};

#endif
