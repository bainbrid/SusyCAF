#ifndef SUSY_CAF_TRIGGERS
#define SUSY_CAF_TRIGGERS

#include <algorithm>

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
    : inputTag  (conf.getParameter<edm::InputTag>("InputTag"))
    , sourceName(conf.getParameter<std::string>  ("SourceName"))
    , sourceType(NOT_APPLICABLE)
  {
    // Source is either a stream or a dataset (mutually exclusive)
    if (sourceName.length() > 0) {
      if (sourceName.length() >= 2 && sourceName[0]=='S' && sourceName[1]==':') {
        sourceType      = STREAM;
        sourceName      = sourceName.substr(2);
      }
      else if (sourceName.length() >= 3 && sourceName[0]=='D' && sourceName[1]=='S' && sourceName[2]==':') {
        sourceType      = DATASET;
        sourceName      = sourceName.substr(3);
      }
      else throw edm::Exception(edm::errors::Configuration)
        << "Invalid SourceName = '" << sourceName 
        << "' -- must start with either 'S:' for streams or 'DS:' for datasets."
        << std::endl;
    }

    produces <bool> ( "hltHandleValid");
    produces <std::map<std::string,bool> >("triggered");
    produces <std::map<std::string,bool> >("parasiticTrigger");
    produces <std::map<std::string,int> > ("prescaled");
  }

private: 
  enum DataSource { NOT_APPLICABLE, STREAM, DATASET };
  const edm::InputTag   inputTag;
  std::string           sourceName;
  DataSource            sourceType;
  HLTConfigProvider     hltConfig;

  // Stored per run/lumisection to save time
  std::vector<std::string>    dataSource;

  virtual void beginRun(edm::Run& run, edm::EventSetup const& setup) {
    bool  hltChanged = false;
    if (!hltConfig.init(run, setup, inputTag.process(), hltChanged) ) {
      edm::LogError( "SusyCAF_Triggers" ) << "HLT config initialization error with process name \"" << inputTag.process() << "\".";
    } else if ( hltConfig.size() < 1 ) {
      edm::LogError( "SusyCAF_Triggers" ) << "HLT config has zero size.";
    }

    getDataSource();
  }

  void printNames(const std::vector<std::string>& names) {
    for (unsigned int i = 0; i < names.size(); ++i)
      edm::LogProblem( "SusyCAF_Triggers" ) << "  " << names[i] << std::endl;
  }

  void getDataSource() {
    dataSource.clear();
    if (sourceType == NOT_APPLICABLE) return;

    if (sourceType == STREAM) {
      unsigned int  index   = hltConfig.streamIndex(sourceName);
      if (index >= hltConfig.streamNames().size()) {
        edm::LogError( "SusyCAF_Triggers" ) << "Streams in '" << inputTag.process() << "' HLT menu:";
        printNames(hltConfig.streamNames());
        throw edm::Exception(edm::errors::Configuration) << "Stream with name '" << sourceName << "' does not exist." << std::endl;
      }
      dataSource    = hltConfig.streamContent(sourceName);
    }
    else {
      unsigned int  index   = hltConfig.datasetIndex(sourceName);
      if (index >= hltConfig.datasetNames().size()) {
        edm::LogError( "SusyCAF_Triggers" ) << "Datasets in '" << inputTag.process() << "' HLT menu:";
        printNames(hltConfig.datasetNames());
        throw edm::Exception(edm::errors::Configuration) << "Dataset with name '" << sourceName << "' does not exist." << std::endl;
      }
      dataSource    = hltConfig.datasetContent(sourceName);
    }
  }

  void produce( edm::Event& event, const edm::EventSetup& setup) {
    edm::Handle<edm::TriggerResults> results;  event.getByLabel(inputTag, results);

    std::auto_ptr<std::map<std::string,bool> > triggered(new std::map<std::string,bool>());
    std::auto_ptr<std::map<std::string,bool> > parasiticTrigger(new std::map<std::string,bool>());
    std::auto_ptr<std::map<std::string,int> >  prescaled(new std::map<std::string,int>());

    if(results.isValid()) {
      const edm::TriggerNames& names = event.triggerNames(*results);
      for(unsigned i=0; i < results->size(); i++) {
        (*prescaled)[names.triggerName(i)] = hltConfig.prescaleValue(event,setup,names.triggerName(i));

        if (dataSource.empty() || std::find(dataSource.begin(), dataSource.end(), names.triggerName(i)) != dataSource.end())
          (*triggered)[names.triggerName(i)] = results->accept(i) ;
        else
          (*parasiticTrigger)[names.triggerName(i)] = results->accept(i) ;
      }
    }

    std::auto_ptr<std::vector<std::string> >  source(new std::vector<std::string>(dataSource));

    event.put( triggered,"triggered");
    event.put( parasiticTrigger,"parasiticTrigger");
    event.put( prescaled,"prescaled");
    event.put( std::auto_ptr<bool>(new bool(results.isValid())), "hltHandleValid");
  }

};

#endif
