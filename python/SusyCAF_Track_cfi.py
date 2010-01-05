import FWCore.ParameterSet.Config as cms

susycaftrack = cms.EDProducer ( "SusyCAF_Track"
                              , InputTag          = cms.InputTag('generalTracks')
                              , PrimaryVertexTag  = cms.InputTag('offlinePrimaryVertices')
                              , Prefix            = cms.string('tracks')
                              , Suffix            = cms.string('')
                              , PTErrFrac         = cms.double(0.2)
                              , MaxD0             = cms.double(-9)
                             #, MaxD0             = cms.double(0.02)
                              )

