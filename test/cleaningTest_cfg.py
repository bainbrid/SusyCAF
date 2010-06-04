import FWCore.ParameterSet.Config as cms

process = cms.Process("CLEAN")

process.source = cms.Source(
    'PoolSource',
    fileNames = cms.untracked.vstring(
    '/store/data/BeamCommissioning09/MinimumBias/RECO/18thFebPreProd_351p1-v3/0000/FAE46E07-C51D-DF11-A7E6-00237DA12CA0.root'
    )
    )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('GR_R_36X_V9::All')

process.options = cms.untracked.PSet(
    SkipEvent = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(False) 
    )

process.out = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('clean.root'),
    outputCommands = cms.untracked.vstring('keep *') 
    )
process.outpath = cms.EndPath(process.out)

from SUSYBSMAnalysis.SusyCAF.cleaning_cff import addNoiseCleaning
schedule = cms.Schedule()
addNoiseCleaning(process,schedule,False)

#process.dump = cms.EDAnalyzer("EventContentAnalyzer")
#process.p = cms.Path(process.dump)
#schedule.append(process.p)
