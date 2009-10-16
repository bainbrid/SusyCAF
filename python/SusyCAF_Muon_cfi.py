import FWCore.ParameterSet.Config as cms

susycafmuon = cms.EDProducer("SusyCAF_RecoMuon",
                            InputTag = cms.InputTag('muons'),
                            Prefix = cms.string('muon'),
                            Suffix = cms.string('global')
                            )
