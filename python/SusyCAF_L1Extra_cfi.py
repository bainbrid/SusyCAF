import FWCore.ParameterSet.Config as cms

susycafl1extra = cms.EDProducer("SusyCAF_L1Extra",
                            InputTag = cms.InputTag('l1extraParticles'),
                            Prefix = cms.string('l1'),
                            Suffix = cms.string(''),
                            )
