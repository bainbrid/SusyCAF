#Needed for SUSYPAT recipe
from PhysicsTools.PatAlgos.patTemplate_cfg import *

process.MessageLogger.categories.append('PATSummaryTables')
process.MessageLogger.cerr.PATSummaryTables = cms.untracked.PSet(
    limit = cms.untracked.int32(-1),
    reportEvery = cms.untracked.int32(1)
    )
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.load('Configuration.StandardSequences.Services_cff')
process.add_( cms.Service( "TFileService",
    fileName = cms.string( 'patTree.root' ),
    closeFileFast = cms.untracked.bool(True) ) 
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

#-- Input Source --------------------------------------------------------------
process.source.fileNames = [
    'file:/disk1/user/nmohr/PYTHIA6_SUSY_LM0_sftsht_10TeV_cff_py_RAW2DIGI_RECO_1.root'
]

process.maxEvents.input = -1
# Due to problem in production of LM samples: same event number appears multiple times
process.source.duplicateCheckMode = cms.untracked.string('noDuplicateCheck')

############################# START SUSYPAT specifics ####################################
process.load("SUSYBSMAnalysis.SusyCAF.SUSY_pattuple_cff")

from SUSYBSMAnalysis.SusyCAF.SUSY_pattuple_cff import addSUSYCollections
addSUSYCollections( process )
############################## END SUSYPAT specifics ####################################

# SusyCAF_nTuple
process.load('SUSYBSMAnalysis.SusyCAF.theBigNtuplePat_cfi')

process.p = cms.Path( process.seqSUSY_pattuple*process.theBigNtuplePat)
process.schedule = cms.Schedule(process.p)
