#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_HcalNoiseFilter.h"
#include "FWCore/Framework/interface/Event.h"

SusyCAF_HcalNoiseFilter::SusyCAF_HcalNoiseFilter(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
  Prefix(iConfig.getParameter<std::string>("Prefix")),
  Suffix(iConfig.getParameter<std::string>("Suffix"))
{
  produces<bool>( Prefix + "HandleValid" + Suffix);
  produces<bool>( Prefix + "FilterResult" + Suffix);
}

void SusyCAF_HcalNoiseFilter::
produce( edm::Event& iEvent, const edm::EventSetup& iSetup ) {

  //declare
  std::auto_ptr<bool> handle( new bool() );
  std::auto_ptr<bool> result( new bool() );

  //assign
  edm::Handle<bool> hcalnoisefilter;
  iEvent.getByLabel(inputTag,hcalnoisefilter);
  
  *handle.get()=hcalnoisefilter.isValid();
  if (*handle) { *result.get()=*hcalnoisefilter; }

  //put
  iEvent.put( handle, Prefix + "HandleValid" + Suffix );
  iEvent.put( result, Prefix + "FilterResult" + Suffix );
}
