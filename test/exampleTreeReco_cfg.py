import FWCore.ParameterSet.Config as cms

process = cms.Process('TEST')
process.load('SUSYBSMAnalysis.SusyCAF.ntuple_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.Services_cff')
process.add_( cms.Service( "TFileService",
                           fileName = cms.string( 'recoTree.root' ),
                           closeFileFast = cms.untracked.bool(True)  ) )

process.load("SUSYBSMAnalysis.SusyCAF.dataSamples.MinBias-Summer09-STARTUP3X_V8D_900GeV-v1-GEN-SIM-RECO_cff")
process.GlobalTag.globaltag = 'STARTUP3X_V8D::All'


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.MessageLogger = cms.Service("MessageLogger",
    default = cms.untracked.PSet(
        reportEvery = cms.untracked.int32(1)
    )
)
