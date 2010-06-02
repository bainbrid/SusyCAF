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
from SUSYBSMAnalysis.SusyCAF.SusyCAF_EcalRecHit_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_PFRecHit_cfi import *
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
                                 susycaftrack + 
                                 susycafl1globaltrigger +  # to be dropped when all L1 triggers have names
                                 susycafL1triggers +       # susycafL1triggersP1 + susycafL1triggersM1 + # susycafL1triggersP2 + susycafL1triggersM2 +
   			         susycaftriggers +
                                 susycafbeamspot + susycafvertex + susycafhcalnoiserbx +
                                 susycafhcalnoisesummary +                                 
                                 susycafcalotowers)

nTupleAllTrackSequence = cms.Sequence( susycafalltracks)

nTuplePatSequence = cms.Sequence( susycafmetIC5 + susycafmetAK5 +  susycafmetAK5TypeII +  susycafmetPF + susycafmetTC + 
                                  susycafphoton + 
                                  susycafelectron + susycafpfelectron + 
                                  susycafmuon + susycafpfmuon +
                                  susycaftau + susycafpftau )

nTuplePatJetSequence = cms.Sequence(susycafic5calojet +
                                    susycafak5calojet + susycafak7calojet +
                                    susycafak5jptjet + 
				    susycafak5pfjet + susycafak5pf2patjet
                                    )

nTuplePatJetMatchedSequence = cms.Sequence(susycafic5calojetMatched +
                                           susycafak5calojetMatched + susycafak7calojetMatched +
                                           susycafak5jptjetMatched + 
					   susycafak5pfjetMatched + susycafak5pf2patjetMatched

                                           )

nTupleRecoMetSequence = cms.Sequence( susycafmet + susycafmetnohf )
nTupleRecoFlagSequence = cms.Sequence( susycafhbherechit +
                                       susycafhfrechit + 
                                       susycafhfrechitreflagged +
                                       susycafebrechit +
                                       susycafeerechit +
                                       susycafpfrechitecal +
                                       susycafpfrechithcal +
                                       susycafpfrechithfem +
                                       susycafpfrechithfhad +
                                       susycafpfrechitps )
#this sequence holds everything that needs reco event content and thaat should run in pat jobs with on-the-fly patification
nTupleRecoPatSequence = cms.Sequence( nTupleRecoMetSequence + nTupleRecoFlagSequence)

nTupleRecoSequence = cms.Sequence( nTupleRecoPatSequence +
                                   susycafic5calojetreco + 
                                   susycafak5calojetreco + susycafak7calojetreco + 
                                   susycafak5jptjetreco + susycafak5pfjetreco +
                                   susycafphotonreco +
                                   susycafelectronreco +                                    
                                   susycafmuonreco +
                                   susycafPFtau)

nTupleGenSequence = cms.Sequence( susycafgen )


nTupleDataSequence = cms.Sequence( susycafdqmflags +
                                   susycafdcsbits )
