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
from SUSYBSMAnalysis.SusyCAF.SusyCAF_HcalNoiseFilter_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_HcalNoiseSummary_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_HcalNoiseRBX_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_HcalRecHit_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_EcalRecHit_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_EcalDeadChannels_cfi import *
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
    'keep *_susycaf*_*_*',
    'keep double_susyScan*_*_*' 
    ))

nCommon = cms.Sequence( susycafevent +
                        susycaftrack + 
                        susycafl1globaltrigger +  # to be dropped when all L1 triggers have names
                        susycafL1triggers +
                        susycaftriggers +
                        susycafbeamspot + susycafvertex + susycafhcalnoiserbx +
                        susycafhcalnoisesummary + susycafhcalnoisefilter +
                        susycafcalotowers)

nAllTrack = cms.Sequence( susycafalltracks)

nPat = cms.Sequence( susycafmetIC5 + susycafmetAK5 +  susycafmetAK5TypeII +  susycafmetPF + susycafmetTC + 
                     susycafphoton + 
                     susycafelectron + susycafpfelectron + 
                     susycafmuon + susycafpfmuon +
                     susycaftau + susycafpftau )

nPatJet = cms.Sequence(susycafic5calojet   +
                       susycafak5calojet   + susycafak7calojet +
                       susycafak5jptjet    + #susycafak7jptjet  +
                       susycafak5pfjet     + susycafak7pfjet   +
                       susycafak5pf2patjet + susycafak7pf2patjet
                       )

nPatJetMatched = cms.Sequence(susycafic5calojetMatched   +
                              susycafak5calojetMatched   + susycafak7calojetMatched +
                              susycafak5jptjetMatched    + #susycafak7jptjetMatched  +
                              susycafak5pfjetMatched     + susycafak7pfjetMatched   +
                              susycafak5pf2patjetMatched + susycafak7pf2patjetMatched
                              )

nRecoMet = cms.Sequence( susycafmet + susycafmetnohf )
nRecoFlag = cms.Sequence( susycafhbherechit +
                          susycafhfrechit + 
                          susycafebrechit +
                          susycafeerechit +
                          susycafpfrechitclusterecal +
                          susycafpfrechitclusterhcal +
                          susycafpfrechitclusterhfem +
                          susycafpfrechitclusterhfhad +
                          susycafpfrechitclusterps +
                          susycafpfrechitecal +
                          susycafpfrechithcal +
                          susycafpfrechithfem +
                          susycafpfrechithfhad +
                          susycafpfrechitps +
                          susycafecaldeadchannels)
#this sequence holds everything that needs reco event content and that should run in pat jobs with on-the-fly patification
nRecoPat = cms.Sequence( nRecoMet + nRecoFlag)

nReco = cms.Sequence( nRecoPat +
                      susycafic5calojetreco + 
                      susycafak5calojetreco + susycafak7calojetreco + 
                      susycafak5jptjetreco  + #susycafak7jptjetreco +
                      susycafak5pfjetreco   + susycafak7pfjetreco +
                      susycafphotonreco +
                      susycafelectronreco +                                    
                      susycafmuonreco +
                      susycafPFtau
                      )

nGen = cms.Sequence( susycafgen )
nData = cms.Sequence( susycafdqmflags + susycafdcsbits )
