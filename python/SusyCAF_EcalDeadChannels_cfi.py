import FWCore.ParameterSet.Config as cms

susycafecaldeadchannels = cms.EDProducer("SusyCAF_EcalDeadChannels",
                                         InputTag = cms.InputTag("ecalTriggerPrimitiveDigis"),
                                         MinStatus = cms.uint32(12)
                                         )
