import FWCore.ParameterSet.Config as cms

susycafPFtau = cms.EDProducer("SusyCAF_pfTau",
                            InputTag = cms.InputTag('fixedConePFTauProducer'), #new name in CMSSW 3x (was pfRecoTauProducer in 22x)
                            Prefix = cms.string('tau'),
                            Suffix = cms.string('PF')
                            )
