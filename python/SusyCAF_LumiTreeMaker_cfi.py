import FWCore.ParameterSet.Config as cms

lumiTree = cms.EDProducer("SusyCAF_LumiTreeMaker",
                          InputTag = cms.InputTag("lumiProducer")
)

