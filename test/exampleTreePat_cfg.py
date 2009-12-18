import FWCore.ParameterSet.Config as cms

process = cms.Process('TEST')
process.load('SUSYBSMAnalysis.SusyCAF.ntuplePat_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.Services_cff')
process.add_( cms.Service( "TFileService",
                           fileName = cms.string( 'PatTree.root' ),
                           closeFileFast = cms.untracked.bool(True)  ) )


#-- Input Source --------------------------------------------------------------
# put PAT file here
process.source = cms.Source('PoolSource',
fileNames = cms.untracked.vstring('file:SUSYPAT.root')
)

process.GlobalTag.globaltag = 'STARTUP3X_V8D::All'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.MessageLogger = cms.Service("MessageLogger",
    default = cms.untracked.PSet(
        reportEvery = cms.untracked.int32(1)
    )
)


