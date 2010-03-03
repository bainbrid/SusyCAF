import FWCore.ParameterSet.Config as cms

susycafmuonreco = cms.EDProducer("SusyCAF_RecoMuon",
                            InputTag = cms.InputTag('muons'),
                            Prefix = cms.string('muon'),
                            Suffix = cms.string('Global')
                            )

susycafmuon = cms.EDProducer("SusyCAF_PatMuon",
                            InputTag = cms.InputTag('cleanPatMuons'),
                            Prefix = cms.string('muon'),
                            Suffix = cms.string('Pat')
                            )


susycafpfmuon = cms.EDProducer("SusyCAF_PatMuon",
                               InputTag = cms.InputTag('pfLayer1Muons'),
                               Prefix = cms.string('muon'),
                               Suffix = cms.string('PF'),
                               )
