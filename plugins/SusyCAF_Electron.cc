#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_Electron.h"


// init method in case of RECO data
template<>
void SusyCAF_Electron<reco::GsfElectron>::initTemplate() { initRECO(); }

// init method in case of PAT data
template<>
void SusyCAF_Electron<pat::Electron>::initTemplate() { initRECO(); initPAT(); }

// produce method in case of RECO data
template<>
void SusyCAF_Electron<reco::GsfElectron>::produceTemplate(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<reco::GsfElectron> >& collection)
{
  produceRECO(iEvent, iSetup, collection);
}

// produce method in case of PAT data
template<>
void SusyCAF_Electron<pat::Electron>::produceTemplate(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<pat::Electron> >& collection)
{
  produceRECO(iEvent, iSetup, collection);
  producePAT(iEvent, iSetup, collection);
}
