import FWCore.ParameterSet.Config as cms

susycafphotonreco = cms.EDProducer( "SusyCAF_RecoPhoton"
                                  , InputTag  = cms.InputTag('photons')
                                  , Prefix    = cms.string('photon')
                                  , Suffix    = cms.string('Reco')
                                  , ProduceExtraSpikeVars = cms.bool(True)
                                  , EbRecHitCollection = cms.string('reducedEcalRecHitsEB')
                                  , EeRecHitCollection = cms.string('reducedEcalRecHitsEE')
                                  , chIsoInputTag =  cms.InputTag('phoPFIso','chIsoForGsfEle')
                                  , phIsoInputTag = cms.InputTag("phoPFIso","phIsoForGsfEle")
                                  , nhIsoInputTag = cms.InputTag("phoPFIso","nhIsoForGsfEle")
                                  )

susycafphoton     = cms.EDProducer( "SusyCAF_PatPhoton"
                                  , InputTag  = cms.InputTag('cleanPatPhotons')
                                  , Prefix    = cms.string('photon')
                                  , Suffix    = cms.string('Pat')
                                  , ProduceExtraSpikeVars = cms.bool(True)
                                  , EbRecHitCollection = cms.string('reducedEcalRecHitsEB')
                                  , EeRecHitCollection = cms.string('reducedEcalRecHitsEE')
                                  , chIsoInputTag = cms.InputTag("phoPFIso","chIsoForGsfEle")
                                  , phIsoInputTag = cms.InputTag("phoPFIso","phIsoForGsfEle")
                                  , nhIsoInputTag = cms.InputTag("phoPFIso","nhIsoForGsfEle")
                                  )
