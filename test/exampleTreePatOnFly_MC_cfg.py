# Starting with a skeleton process which gets imported with the following line
from PhysicsTools.PatAlgos.patTemplate_cfg import *

#-- Message Logger ------------------------------------------------------------
#process.MessageLogger.categories.append('PATSummaryTables')
#process.MessageLogger.cerr.PATSummaryTables = cms.untracked.PSet(
#    limit = cms.untracked.int32(-1),
#    reportEvery = cms.untracked.int32(100)
#    )
#process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.load('Configuration.StandardSequences.Services_cff')
process.add_( cms.Service( "TFileService",
    fileName = cms.string( 'WJets_madgraph.root' ),
    closeFileFast = cms.untracked.bool(True) ) 
)

#-- Input Source --------------------------------------------------------------
process.source = cms.Source('PoolSource',
fileNames = cms.untracked.vstring('file:/tmp/jad/WJets-madgraph_test.root')
)

process.maxEvents.input = 1000

# Due to problem in production of LM samples: same event number appears multiple times
process.source.duplicateCheckMode = cms.untracked.string('noDuplicateCheck')


#-- Calibration tag -----------------------------------------------------------
# Should match input file's tag
# First Collision Data
#process.GlobalTag.globaltag = 'GR09_P_V6::All'
# MinBias MC STARTUP
process.GlobalTag.globaltag = 'MC_3XY_V15::All'


############################# START SUSYPAT specifics ####################################
from PhysicsTools.Configuration.SUSY_pattuple_cff import addDefaultSUSYPAT, getSUSY_pattuple_outputCommands
#Apply SUSYPAT: Parameters are: mcInfo, HLT menu, Jet energy corrections, MC version ('31x' or '31xReReco332')
addDefaultSUSYPAT(process,True,'HLT','Summer09_7TeV','31x')
SUSY_pattuple_outputCommands = getSUSY_pattuple_outputCommands( process )
############################## END SUSYPAT specifics ####################################

#-- Output module configuration -----------------------------------------------
process.out.fileName = 'SUSYPAT.root'       # <-- CHANGE THIS TO SUIT YOUR NEEDS

# Custom settings
process.out.splitLevel = cms.untracked.int32(99)  # Turn on split level (smaller files???)
process.out.overrideInputFileSplitLevels = cms.untracked.bool(True)
process.out.dropMetaData = cms.untracked.string('DROPPED')   # Get rid of metadata related to dropped collections
process.out.outputCommands = cms.untracked.vstring('drop *', *SUSY_pattuple_outputCommands )

# SusyCAF_nTuple
process.load('SUSYBSMAnalysis.SusyCAF.theBigNtuplePatOnFly_MC_cfi')

#-- Execution path ------------------------------------------------------------
# Full path
process.p = cms.Path( process.seqSUSYDefaultSequence * process.theBigNtuplePat)
if hasattr(process,"out"): # remove outpath 
    del process.out
    del process.outpath
