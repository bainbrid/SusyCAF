#ifndef SUSY_CAF_TRIGGERS
#define SUSY_CAF_TRIGGERS

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

class SusyCAF_Triggers : public edm::EDProducer 
{
public: 
  explicit SusyCAF_Triggers(const edm::ParameterSet& conf)
    : inputTag(conf.getParameter<edm::InputTag>("InputTag"))
    {
      produces <bool> ( "hltHandleValid");
      produces <std::map<std::string,bool> > ("triggered");
      produces <std::map<std::string,int> >  ("prescaled");
    }

private: 
  const edm::InputTag   inputTag;
  HLTConfigProvider hltconfig;

  void produce( edm::Event& event, const edm::EventSetup& setup) {
    bool returnValueOfChanged=false;
    hltconfig.init(event, inputTag.process(), returnValueOfChanged);

    edm::Handle<edm::TriggerResults> results;  event.getByLabel(inputTag, results);
    
    std::auto_ptr<std::map<std::string,bool> > triggered(new std::map<std::string,bool>());
    std::auto_ptr<std::map<std::string,int> >  prescaled(new std::map<std::string,int>());
    
    if(results.isValid()) {
      const edm::TriggerNames& names = event.triggerNames(*results);
      for(unsigned i=0; i < results->size(); i++) {
	(*triggered)[names.triggerName(i)] = results->accept(i) ;
	(*prescaled)[names.triggerName(i)] = hltconfig.prescaleValue(event,setup,names.triggerName(i));
      }
    }
    
    event.put( triggered,"triggered");
    event.put( prescaled,"prescaled");
    event.put( std::auto_ptr<bool>(new bool(results.isValid())), "hltHandleValid");
  }
  
};

#endif
