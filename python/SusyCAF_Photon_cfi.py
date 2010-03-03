import FWCore.ParameterSet.Config as cms

susycafphotonreco = cms.EDProducer( "SusyCAF_RecoPhoton"
                                  , InputTag  = cms.InputTag('photons')
                                  , Prefix    = cms.string('photon')
                                  , Suffix    = cms.string('Reco')
                                  )

susycafphoton     = cms.EDProducer( "SusyCAF_PatPhoton"
                                  , InputTag  = cms.InputTag('cleanPatPhotons')
                                  , Prefix    = cms.string('photon')
                                  , Suffix    = cms.string('Pat')
                                  )
