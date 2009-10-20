import FWCore.ParameterSet.Config as cms

susycafic5calojet = cms.EDProducer("SusyCAF_CaloJet",
                            InputTag = cms.InputTag('iterativeCone5CaloJets'),
                            Prefix = cms.string('ic5jet'),
                            Suffix = cms.string('calo')
                            )

susycafkt4calojet = cms.EDProducer("SusyCAF_CaloJet",
                            InputTag = cms.InputTag('kt4CaloJets'),
                            Prefix = cms.string('kt4jet'),
                            Suffix = cms.string('calo')
                            )
