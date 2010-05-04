import FWCore.ParameterSet.Config as cms

susycafebrechit = cms.EDProducer("SusyCAF_EcalRecHit",
                                 InputTag = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
                                 #InputTag = cms.InputTag("reducedEcalRecHitsEB"),
                                 Prefix = cms.string('rechitCalo'),
                                 Suffix = cms.string('Eb'),
                                 )

susycafeerechit = cms.EDProducer("SusyCAF_EcalRecHit",
                                 InputTag = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
                                 #InputTag = cms.InputTag("reducedEcalRecHitsEE"),
                                 Prefix = cms.string('rechitCalo'),
                                 Suffix = cms.string('Ee'),
                                 )
