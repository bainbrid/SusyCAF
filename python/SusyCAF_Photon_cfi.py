import FWCore.ParameterSet.Config as cms

susycafphoton = cms.EDProducer( "SusyCAF_Photon"
                              , InputTag  = cms.InputTag('photons')
                              , Prefix    = cms.string('photon')
                              , Suffix    = cms.string('')
                              )
