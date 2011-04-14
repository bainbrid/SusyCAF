import FWCore.ParameterSet.Config as cms

susycafphotonreco = cms.EDProducer( "SusyCAF_RecoPhoton"
                                  , InputTag  = cms.InputTag('photons')
                                  , Prefix    = cms.string('photon')
                                  , Suffix    = cms.string('Reco')
                                  , ProduceExtraIdVars = cms.bool(True)
                                  , ProduceExtraSpikeVars = cms.bool(True)
                                  , TrackTag = cms.InputTag("generalTracks")
                                  , EbRecHitCollection = cms.string('reducedEcalRecHitsEB')
                                  , EeRecHitCollection = cms.string('reducedEcalRecHitsEE')
                                  , HbheRecHitCollection = cms.string('hbhereco')
                                  )

susycafphoton     = cms.EDProducer( "SusyCAF_PatPhoton"
                                  , InputTag  = cms.InputTag('cleanPatPhotons')
                                  , Prefix    = cms.string('photon')
                                  , Suffix    = cms.string('Pat')
                                  , ProduceExtraIdVars = cms.bool(False)
                                  , ProduceExtraSpikeVars = cms.bool(True)
                                  , TrackTag = cms.InputTag("generalTracks")
                                  , EbRecHitCollection = cms.string('reducedEcalRecHitsEB')
                                  , EeRecHitCollection = cms.string('reducedEcalRecHitsEE')
                                  , HbheRecHitCollection = cms.string('hbhereco')
                                  )
