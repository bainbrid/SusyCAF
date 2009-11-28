import FWCore.ParameterSet.Config as cms

susycaftrack = cms.EDProducer ( "SusyCAF_Track"
                              , InputTag          = cms.InputTag('generalTracks')
                              , PrimaryVertexTag  = cms.InputTag('offlinePrimaryVertices')
                              , Prefix            = cms.string('tracks')
                              , Suffix            = cms.string('')
                              , MaxChi2           = cms.double(100)
                              , MaxD0             = cms.double(0.02)
                              , MinPT             = cms.double(0.3)
                              , MaxPT             = cms.double(500)
                              )

