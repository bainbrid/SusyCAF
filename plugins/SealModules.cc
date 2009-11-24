#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Math/interface/Vector3D.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/PatCandidates/interface/Electron.h"


#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/TauReco/interface/PFTau.h"

#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"

DEFINE_SEAL_MODULE();

#include "SUSYBSMAnalysis/SusyCAF/interface/SusyTree.h"
#include "UserCode/ArloGB/ICFNtupliser/interface/ICFntup_Event.h"
#include "UserCode/ArloGB/ICFNtupliser/interface/ICFntup_Triggers.h"
#include "UserCode/ArloGB/ICFNtupliser/interface/ICFntup_L1Triggers.h"
#include "UserCode/ArloGB/ICFNtupliser/interface/ICFntup_MET.h"
#include "UserCode/ArloGB/ICFNtupliser/interface/ICFntup_Jet.h"
#include "UserCode/ArloGB/ICFNtupliser/interface/ICFntup_Photon.h"
#include "UserCode/ArloGB/ICFNtupliser/interface/ICFntup_Electron.h"
#include "UserCode/ArloGB/ICFNtupliser/interface/ICFntup_Muon.h"
#include "UserCode/ArloGB/ICFNtupliser/interface/ICFntup_BeamSpot.h"
#include "UserCode/ArloGB/ICFNtupliser/interface/ICFntup_Vertex.h"
#include "UserCode/ArloGB/ICFNtupliser/interface/ICFntup_L1GlobalTrigger.h"
#include "UserCode/ArloGB/ICFNtupliser/interface/ICFntup_L1CaloTrigger.h"
#include "UserCode/ArloGB/ICFNtupliser/interface/ICFntup_HLTTrigger.h"
#include "UserCode/ArloGB/ICFNtupliser/interface/ICFntup_L1Extra.h"
//#include "UserCode/ArloGB/ICFNtupliser/interface/ICFntup_HcalTrigPrim.h"
#include "UserCode/ArloGB/ICFNtupliser/interface/ICFntup_HcalRecHit.h"
#include "UserCode/ArloGB/ICFNtupliser/interface/ICFntup_CaloTowers.h"

<<<<<<< SealModules.cc
#include "UserCode/ArloGB/ICFNtupliser/interface/ICFntup_CaloTau.h"
#include "UserCode/ArloGB/ICFNtupliser/interface/ICFntup_PFTau.h"
=======
#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_PFTau.h"
>>>>>>> 1.16

typedef SusyCAF_MET<reco::CaloMET> SusyCAF_CaloMET;
typedef SusyCAF_MET<pat::MET> SusyCAF_PatMET;
typedef SusyCAF_Jet<reco::CaloJet> SusyCAF_CaloJet;
typedef SusyCAF_Jet<pat::Jet> SusyCAF_PatJet;
typedef SusyCAF_Photon<reco::Photon> SusyCAF_RecoPhoton;
typedef SusyCAF_Photon<pat::Photon> SusyCAF_PatPhoton;
typedef SusyCAF_Electron<reco::GsfElectron> SusyCAF_GsfElectron;
typedef SusyCAF_Electron<pat::Electron> SusyCAF_PatElectron;
typedef SusyCAF_Muon<reco::Muon> SusyCAF_RecoMuon;
typedef SusyCAF_Muon<pat::Muon> SusyCAF_PatMuon;


typedef SusyCAF_PFTau<reco::PFTau> SusyCAF_pfTau;
typedef SusyCAF_PFTau<pat::Tau> SusyCAF_PatTau;


typedef SusyCAF_HcalRecHit<HBHERecHitCollection> SusyCAF_HBHERecHitsSorted;
typedef SusyCAF_HcalRecHit<HFRecHitCollection> SusyCAF_HFRecHitsSorted;
typedef SusyCAF_HcalRecHit<HORecHitCollection> SusyCAF_HORecHitsSorted;
typedef SusyCAF_HcalRecHit<HFRecHitCollection> SusyCAF_HFRecHitsSorted;
typedef SusyCAF_CaloTowers<CaloTowerCollection> SusyCAF_CT;


DEFINE_ANOTHER_FWK_MODULE(SusyTree);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_Event);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_Triggers);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_L1Triggers);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_CaloMET);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_PatMET);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_CaloJet);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_PatJet);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_RecoPhoton);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_PatPhoton);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_GsfElectron);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_PatElectron);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_RecoMuon);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_PatMuon);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_BeamSpot);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_Vertex);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_L1GlobalTrigger);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_L1CaloTrigger);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_HLTTrigger);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_L1Extra);
//DEFINE_ANOTHER_FWK_MODULE(SusyCAF_HcalTrigPrim);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_HBHERecHitsSorted);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_HFRecHitsSorted);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_HORecHitsSorted);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_CT);


DEFINE_ANOTHER_FWK_MODULE(SusyCAF_PatTau);
DEFINE_ANOTHER_FWK_MODULE(SusyCAF_pfTau);


