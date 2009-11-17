#ifndef SUSY_CAF_L1TRIGGERS
#define SUSY_CAF_L1TRIGGERS

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "boost/lexical_cast.hpp"

class SusyCAF_L1Triggers : public edm::EDProducer 
{
public: 
  explicit SusyCAF_L1Triggers(const edm::ParameterSet& conf) : 
    nBx(conf.getParameter<int>("NBx")),
    inputTag(conf.getParameter<edm::InputTag>("InputTag")),
    outputName("L1triggered" + (nBx==0? "" : ( nBx<0 ? "M" : "P") + boost::lexical_cast<std::string>(abs(nBx)) ) )
      {
	produces <std::map<std::string,bool> > ( outputName );
      }

private: 
  const int nBx;
  const edm::InputTag inputTag;
  const std::string outputName;

  void produce( edm::Event& event, const edm::EventSetup& setup) {
    edm::Handle<L1GlobalTriggerReadoutRecord> L1record;  event.getByLabel(inputTag, L1record);
    edm::ESHandle<L1GtTriggerMenu> L1menu;               setup.get<L1GtTriggerMenuRcd>().get(L1menu) ;

    std::auto_ptr<std::map<std::string,bool> > triggered(new std::map<std::string,bool>());

    record( triggered, L1record->decisionWord(nBx),         L1menu->gtAlgorithmMap() );
    record( triggered, L1record->technicalTriggerWord(nBx), L1menu->gtTechnicalTriggerMap() );

    event.put( triggered, outputName );
    
  }

  void record(std::auto_ptr<std::map<std::string,bool> >& mapSb, std::vector<bool> vbool, const AlgorithmMap& algoMap) const {
    for( AlgorithmMap::const_iterator it = algoMap.begin(); it != algoMap.end(); ++it)
      (*mapSb)[it->first] = vbool.at(it->second.algoBitNumber());
  }

};

#endif
