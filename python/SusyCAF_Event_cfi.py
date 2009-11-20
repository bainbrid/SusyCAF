import FWCore.ParameterSet.Config as cms

susycafevent = cms.EDProducer("SusyCAF_Event",
                                    InputTag = cms.InputTag('gtDigis'),
                                   )

