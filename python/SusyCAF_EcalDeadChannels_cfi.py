import FWCore.ParameterSet.Config as cms

susycafecaldeadchannels = cms.EDProducer("SusyCAF_EcalDeadChannels",
                                         #*Branch  :EcalTriggerPrimitiveDigisSorted_ecalDigis_EcalTriggerPrimitives_SUSYCAF. *
                                         InputTag = cms.InputTag("ecalDigis","EcalTriggerPrimitives"),
                                         MinStatus = cms.uint32(12)
                                         )
