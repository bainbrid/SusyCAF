import FWCore.ParameterSet.Config as cms

susycafrechit = cms.EDProducer("SusyCAF_HFRecHitsSorted",
                            InputTag = cms.InputTag('hfreco'),
                            Prefix = cms.string('rechit'),
                            Suffix = cms.string('hf')
                            )
