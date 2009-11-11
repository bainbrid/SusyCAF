import FWCore.ParameterSet.Config as cms

susycafic5calojet = cms.EDProducer("SusyCAF_CaloJet",
                            InputTag = cms.InputTag('iterativeCone5CaloJets'),
                            Prefix = cms.string('ic5Jet'),
                            Suffix = cms.string('Calo')
                            )

susycafak5calojet = cms.EDProducer("SusyCAF_CaloJet",
                            InputTag = cms.InputTag('antikt5CaloJets'),
                            Prefix = cms.string('ak5Jet'),
                            Suffix = cms.string('Calo')
                            )
