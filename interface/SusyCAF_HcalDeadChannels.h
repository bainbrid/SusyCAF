#ifndef SUSYCAF_HCALDEADCHANNELS
#define SUSYCAF_HCALDEADCHANNELS

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "DataFormats/Candidate/interface/Candidate.h"

class SusyCAF_HcalDeadChannels : public edm::EDProducer {
 public: 
  explicit SusyCAF_HcalDeadChannels(const edm::ParameterSet&);
 private: 
  void produce(edm::Event&,const edm::EventSetup&);
  typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<double> > PolarLorentzV;
  const uint32_t statusMask;
};

#endif
