#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_Muon.h"


// init method in case of RECO data
template<>
void SusyCAF_Muon<reco::Muon>::initTemplate() { initRECO(); }

// init method in case of PAT data
template<>
void SusyCAF_Muon<pat::Muon>::initTemplate()  { initRECO(); initPAT(); }

// produce method in case of RECO data
template<>
void SusyCAF_Muon<reco::Muon>::produceTemplate(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<reco::Muon> >& collection)
{
  produceRECO(iEvent, iSetup, collection);
}

// produce method in case of PAT data
template<>
void SusyCAF_Muon<pat::Muon>::produceTemplate(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<pat::Muon> >& collection)
{
  produceRECO(iEvent, iSetup, collection);
  producePAT(iEvent, iSetup, collection);
}
