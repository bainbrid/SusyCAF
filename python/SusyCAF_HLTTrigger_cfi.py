import FWCore.ParameterSet.Config as cms

susycafhlttrigger = cms.EDProducer("SusyCAF_HLTTrigger"
                              , hltresults = cms.InputTag('TriggerResults::HLT')
			      , InputTag   = cms.InputTag('gtDigis')
                              , Prefix     = cms.string('hlt')
                              , Suffix     = cms.string('')
                              )
