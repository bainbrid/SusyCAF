#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Math/interface/Vector3D.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"

#include "DataFormats/TauReco/interface/CaloTau.h"

DEFINE_SEAL_MODULE();

#include "SUSYBSMAnalysis/SusyCAF/interface/SusyTree.h"
#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_Event.h"
#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_MET.h"
#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_Jet.h"
#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_Photon.h"
#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_Electron.h"
#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_Muon.h"
#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_BeamSpot.h"
#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_Vertex.h"
#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_L1GlobalTrigger.h"
#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_L1CaloTrigger.h"
#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_L1Extra.h"
//#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_HcalTrigPrim.h"
#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_HcalRecHit.h"
#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_CaloTowers.h"

#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_CaloTau.h"

typedef SusyCAF_MET<reco::CaloMET> SusyCAF_CaloMET;
typedef SusyCAF_Jet<reco::CaloJet> SusyCAF_CaloJet;
typedef SusyCAF_Electron<reco::GsfElectron> SusyCAF_GsfElectron;
typedef SusyCAF_Muon<reco::Muon> SusyCAF_RecoMuon;
typedef SusyCAF_HcalRecHit<HBHERecHitCollection> SusyCAF_HBHERecHitsSorted;
typedef SusyCAF_HcalRecHit<HFRecHitCollection> SusyCAF_HFRecHitsSorted;
typedef SusyCAF_HcalRecHit<HORecHitCollection> SusyCAF_HORecHitsSorted;
typedef SusyCAF_HcalRecHit<HFRecHitCollection> SusyCAF_HFRecHitsSorted;
typedef SusyCAF_CaloTowers<CaloTowerCollection> SusyCAF_CT;

typedef SusyCAF_CaloTau<reco::CaloTau> SusyCAF_CalTau;

DEFINE_ANOTHER_FWK_MODULE(SusyTree);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_Event);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_CaloMET);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_CaloJet);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_Photon);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_GsfElectron);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_RecoMuon);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_BeamSpot);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_Vertex);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_L1GlobalTrigger);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_L1CaloTrigger);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_L1Extra);
//DEFINE_ANOTHER_FWK_MODULE(SusyCAF_HcalTrigPrim);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_HBHERecHitsSorted);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_HFRecHitsSorted);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_HORecHitsSorted);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_CT);

DEFINE_ANOTHER_FWK_MODULE(SusyCAF_CalTau);
