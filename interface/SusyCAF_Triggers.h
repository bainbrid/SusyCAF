#ifndef SUSY_CAF_TRIGGERS
#define SUSY_CAF_TRIGGERS

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/TriggerResults.h"
//#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/Framework/interface/TriggerNames.h"

class SusyCAF_Triggers : public edm::EDProducer 
{
public: 
  explicit SusyCAF_Triggers(const edm::ParameterSet& conf)
    : inputTag(conf.getParameter<edm::InputTag>("InputTag"))
    {
      produces <std::map<std::string,bool> >  ("triggered");
    }

private: 
  const edm::InputTag   inputTag;

  void produce( edm::Event& event, const edm::EventSetup& ) {
    edm::Handle<edm::TriggerResults> results;  event.getByLabel(inputTag, results);
    /* edm::TriggerNames& names = event.triggerNames(); */   edm::TriggerNames names; names.init(*results);  
    
    std::auto_ptr<std::map<std::string,bool> > triggered(new std::map<std::string,bool>());
    for(unsigned i=0; i < results->size(); i++)
      (*triggered)[names.triggerName(i)] = results->accept(i) ;
    event.put( triggered,"triggered");
  }

};

#endif
