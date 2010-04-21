import FWCore.ParameterSet.Config as cms

from SUSYBSMAnalysis.SusyCAF.SusyCAF_Event_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_Track_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_Triggers_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_L1Triggers_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_L1GlobalTrigger_cfi import *
#from SUSYBSMAnalysis.SusyCAF.SusyCAF_L1CaloTrigger_cfi import *
#from SUSYBSMAnalysis.SusyCAF.SusyCAF_L1Extra_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_Gen_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_MET_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_Jet_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_Photon_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_Muon_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_Electron_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_BeamSpot_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_Vertex_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_HcalNoiseSummary_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_HcalNoiseRBX_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_HcalRecHit_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_CaloTowers_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_PFTau_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_AllTracks_cfi import *

from SUSYBSMAnalysis.SusyCAF.SusyCAF_DQMFlags_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_DCSBits_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_LumiTreeMaker_cfi import *

susyTree = cms.EDAnalyzer("SusyTree",
    outputCommands = cms.untracked.vstring(
    'drop *',
    'keep *_susycaf*_*_*'
    ))

nTupleCommonSequence = cms.Sequence( susycafevent +
                                 susycaftrack + # susycafalltracks +
                                 susycafl1globaltrigger +  # to be dropped when all L1 triggers have names
                                 susycafL1triggers +       # susycafL1triggersP1 + susycafL1triggersM1 + # susycafL1triggersP2 + susycafL1triggersM2 +
   			         susycaftriggers +
                                 susycafbeamspot + susycafvertex + susycafhcalnoiserbx +
                                 susycafhcalnoisesummary +                                 
                                 susycafcalotowers)

nTuplePatSequence = cms.Sequence( susycafmetIC5 + susycafmetAK5 +  susycafmetPF + susycafmetTC + 
                                  susycafphoton + 
                                  susycafelectron + #susycafpfelectron + #Remove until PF2PAT is ready in 35X
                                  susycafmuon + #susycafpfmuon +
                                  susycaftau)

nTuplePatJetSequence = cms.Sequence(susycafic5calojet + susycafsc5calojet +
                                    susycafak5calojet + susycafak7calojet +
                                    susycafak5jptjet + susycafic5pfjet + susycafak5pfjet
                                    )

nTuplePatJetMatchedSequence = cms.Sequence(susycafic5calojetMatched + susycafsc5calojetMatched +
                                           susycafak5calojetMatched + susycafak7calojetMatched +
                                           susycafak5jptjetMatched + susycafic5pfjetMatched + susycafak5pfjetMatched
                                           )

nTupleRecoMetSequence = cms.Sequence( susycafmet + susycafmetnohf )
nTupleRecoFlagSequence = cms.Sequence( susycafhbherechit + susycafhfrechitreflagged )

nTupleRecoSequence = cms.Sequence( nTupleRecoMetSequence +
                                   susycafic5calojetreco + susycafsc5calojetreco +
                                   susycafak5calojetreco + susycafak7calojetreco + 
                                   susycafak5jptjetreco + susycafic5pfjetreco + susycafak5pfjetreco +
                                   susycafphotonreco +
                                   susycafelectronreco +                                    
                                   susycafmuonreco +
                                   susycafPFtau)

nTupleGenSequence = cms.Sequence( susycafgen )


nTupleDataSequence = cms.Sequence( susycafdqmflags +
                                   susycafdcsbits )
