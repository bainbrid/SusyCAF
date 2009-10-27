import FWCore.ParameterSet.Config as cms

from SUSYBSMAnalysis.SusyCAF.SusyCAF_Event_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_MET_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_Jet_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_Photon_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_Muon_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_Electron_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_BeamSpot_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_Vertex_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_L1GlobalTrigger_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_HLTTrigger_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_L1CaloTrigger_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_L1Extra_cfi import *
#from SUSYBSMAnalysis.SusyCAF.SusyCAF_HcalTrigPrim_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_HcalRecHit_cfi import *
from SUSYBSMAnalysis.SusyCAF.SusyCAF_CaloTowers_cfi import *

<<<<<<< theBigNtuple_cfi.py
from SUSYBSMAnalysis.SusyCAF.SusyCAF_CaloTau_cfi import *


=======
>>>>>>> 1.9
susyTree = cms.EDAnalyzer("SusyTree",
    outputCommands = cms.untracked.vstring(
    'drop *',
    'keep *_susycafevent_*_*',
    'keep *_susycafic5calojet_*_*',
    'keep *_susycafkt4calojet_*_*',
    'keep *_susycafmet_*_*',
    'keep *_susycafmetnohf_*_*',
    'keep *_susycafphoton_*_*',
    'keep *_susycafmuon_*_*',
    'keep *_susycafelectron_*_*',
    'keep *_susycafvertex_*_*',
    'keep *_susycafbeamspot_*_*',
    'keep *_susycafl1globaltrigger_*_*',
    'keep *_susycafhlttrigger_*_*',
    'keep *_susycafl1calotrigger_*_*',
    'keep *_susycafl1extra_*_*',
#    'keep *_susycafhcaltrigprim_*_*',
    'keep *_susycafhbherechit_*_*',
    'keep *_susycafhfrechit_*_*',
    'keep *_susycafhorechit_*_*',
    'keep *_susycafcalotowers_*_*',

    'keep *_susycafcalotau_*_*',
    ))

theBigNtuple = cms.Sequence( (susycafevent +
                               susycafl1globaltrigger +
<<<<<<< theBigNtuple_cfi.py
  		#	       susycafhlttrigger +
                              susycafmet +
=======
   			       susycafhlttrigger +
                               susycafmet +
>>>>>>> 1.9
                               susycafic5calojet +
                               susycafkt4calojet +
                               susycafphoton +
                               susycafmuon +
                               susycafbeamspot +
                               susycafvertex +
                               susycafelectron +
                            #   susycafcalotowers +
                              susycafcalotau) *
                               susyTree
                              )
