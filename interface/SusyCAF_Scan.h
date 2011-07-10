#ifndef SUSY_CAF_SCAN
#define SUSY_CAF_SCAN

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "boost/regex.hpp"

class SusyCAF_Scan : public edm::EDProducer {
 public: 
  explicit SusyCAF_Scan(const edm::ParameterSet&);
  double convert(std::string);
 private: 
  void produce( edm::Event &, const edm::EventSetup & );
  const edm::InputTag inputTag;
  const std::string Prefix,Suffix;
  const boost::regex scanFormat;
  const std::vector<std::string> scanPars;
  const bool debug;
};

#endif
