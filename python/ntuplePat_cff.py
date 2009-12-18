import FWCore.ParameterSet.Config as cms

from SUSYBSMAnalysis.SusyCAF.theBigNtuplePat_cfi import *

#Schedule
ntuplize_step = cms.Path( theBigNtuplePat )
schedule = cms.Schedule( ntuplize_step )
