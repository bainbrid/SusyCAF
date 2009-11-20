import FWCore.ParameterSet.Config as cms

process = cms.Process('TEST')
process.load('SUSYBSMAnalysis.SusyCAF.ntuple_cff')

process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.Services_cff')
process.add_( cms.Service( "TFileService",
                           fileName = cms.string( 'testTree.root' ),
                           closeFileFast = cms.untracked.bool(True)  ) )

baseLocation="/store/data/Commissioning09/Calo/RECO/v8/000/116/736"

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source (
    "PoolSource",
     fileNames = cms.untracked.vstring((baseLocation+"/04A68558-83B4-DE11-B565-001D09F29533.root")),

     secondaryFileNames = cms.untracked.vstring()
    
  )

process.MessageLogger = cms.Service("MessageLogger",
    default = cms.untracked.PSet(
        reportEvery = cms.untracked.int32(100)
    )
)
