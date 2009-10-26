import FWCore.ParameterSet.Config as cms

susycafhbherechit = cms.EDProducer("SusyCAF_HBHERecHitsSorted",
                            InputTag = cms.InputTag('hbhereco'),
                            Prefix = cms.string('rechit'),
                            Suffix = cms.string('hbhe'),
                            OutputAllRecHits = cms.bool(False) #slightly misleading name
                            )

susycafhfrechit = cms.EDProducer("SusyCAF_HFRecHitsSorted",
                            InputTag = cms.InputTag('hfreco'),
                            Prefix = cms.string('rechit'),
                            Suffix = cms.string('hf'),
                            OutputAllRecHits = cms.bool(False) #slightly misleading name
                            )

susycafhorechit = cms.EDProducer("SusyCAF_HORecHitsSorted",
                            InputTag = cms.InputTag('horeco'),
                            Prefix = cms.string('rechit'),
                            Suffix = cms.string('ho'),
                            OutputAllRecHits = cms.bool(False) #slightly misleading name
                            )

