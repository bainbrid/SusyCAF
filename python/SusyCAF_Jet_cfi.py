import FWCore.ParameterSet.Config as cms

susycafic5calojet = cms.EDProducer("SusyCAF_CaloJet",
                            InputTag = cms.InputTag('iterativeCone5CaloJets'),
                            Prefix = cms.string('ic5Jet'),
                            Suffix = cms.string('Calo')
                            )

susycafkt4calojet = cms.EDProducer("SusyCAF_CaloJet",
                            InputTag = cms.InputTag('kt4CaloJets'),
                            Prefix = cms.string('kt4Jet'),
                            Suffix = cms.string('Calo')
                            )
