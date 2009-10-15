import FWCore.ParameterSet.Config as cms

susycafl1globaltrigger = cms.EDProducer("SusyCAF_L1GlobalTrigger",
                            InputTag = cms.InputTag('gtDigis'),
                            NBxOutput = cms.int32(1) #support for either 1 or 3
                            )
