#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_HLTTrigger.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/TriggerResults.h"
using namespace edm;
using namespace std;
typedef std::pair<const char *, const edm::InputTag *> MissingCollectionInfo;
template <class T>
static inline
bool getCollection(const edm::Event & event, std::vector<MissingCollectionInfo> & missing, edm::Handle<T> & handle, const edm::InputTag & name, const char * description)
{
  event.getByLabel(name, handle);
  bool valid = handle.isValid();
  if (not valid) {
    missing.push_back( std::make_pair(description, & name) );
    handle.clear();
  }
  return valid;
}

SusyCAF_HLTTrigger::SusyCAF_HLTTrigger(const edm::ParameterSet& iConfig):
hltresults_(iConfig.getParameter<edm::InputTag>("hltresults")),
inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
prefix(iConfig.getParameter<std::string>("Prefix")),
suffix(iConfig.getParameter<std::string>("Suffix"))
{ 
  produces <unsigned int>(prefix+"HLTJet6U"+suffix);
}

void SusyCAF_HLTTrigger::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {

    std::auto_ptr<unsigned int>  hlt_jet6u  ( new unsigned int() );
    std::vector<MissingCollectionInfo> missing;    
 
   // HLT TRIGGERS  
    bool triggerExists = true;
  
    
    edm::Handle<edm::TriggerResults> hltresults;
    getCollection( iEvent, missing, hltresults,      hltresults_,        "HLT Results" );
    triggerNames_.init(*hltresults);  
    hlNames_ = triggerNames_.triggerNames();

    if (!hltresults.isValid()) {
     triggerExists = false;             
     return;      
    }
    else {  
    for(unsigned int i=0; i< hltresults->size(); i++) {
     
     //cout << " I AM GETTING IN THIS LOOP and names are " << hlNames_[i] << endl;
     if(hlNames_[i] == "HLT_L1Jet6U")  *hlt_jet6u.get() = (*hltresults)[i].accept();
          
     }
    }
     
    
    iEvent.put(hlt_jet6u,prefix+"HLTJet6U"+suffix);
   
}
