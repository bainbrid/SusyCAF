import FWCore.ParameterSet.Config as cms

process = cms.Process('TEST')
process.load('SUSYBSMAnalysis.SusyCAF.ntuple_cff')

process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.Services_cff')
process.add_( cms.Service( "TFileService",
                           fileName = cms.string( 'recoTree.root' ),
                           closeFileFast = cms.untracked.bool(True)  ) )


process.load("SUSYBSMAnalysis.SusyCAF.dataSamples.MinBias_Summer09_STARTUP3X_V8D_900GeV_v1_GEN_SIM_RECO_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.MessageLogger = cms.Service("MessageLogger",
    default = cms.untracked.PSet(
        reportEvery = cms.untracked.int32(1)
    )
)
