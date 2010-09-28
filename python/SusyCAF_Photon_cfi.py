import FWCore.ParameterSet.Config as cms

susycafphotonreco = cms.EDProducer( "SusyCAF_RecoPhoton"
                                  , InputTag  = cms.InputTag('photons')
                                  , Prefix    = cms.string('photon')
                                  , Suffix    = cms.string('Reco')
                                  , ProduceExtraVars = cms.bool(True)
                                  , TrackTag = cms.InputTag("generalTracks")
                                  , EcalRecHitProducer = cms.string('ecalRecHit')
                                  , EbRecHitCollection = cms.string('EcalRecHitsEB')
                                  , EeRecHitCollection = cms.string('EcalRecHitsEE')
                                  , HbheRecHitCollection = cms.string('hbhereco')
                                  )

susycafphoton     = cms.EDProducer( "SusyCAF_PatPhoton"
                                  , InputTag  = cms.InputTag('cleanPatPhotons')
                                  , Prefix    = cms.string('photon')
                                  , Suffix    = cms.string('Pat')
                                  , ProduceExtraVars = cms.bool(True)
                                  , TrackTag = cms.InputTag("generalTracks")
                                  , EcalRecHitProducer = cms.string('ecalRecHit')
                                  , EbRecHitCollection = cms.string('EcalRecHitsEB')
                                  , EeRecHitCollection = cms.string('EcalRecHitsEE')
                                  , HbheRecHitCollection = cms.string('hbhereco')
                                  )
