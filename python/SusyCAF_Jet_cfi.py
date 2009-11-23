import FWCore.ParameterSet.Config as cms

susycafic5calojetreco = cms.EDProducer("SusyCAF_CaloJet",
                            InputTag = cms.InputTag('iterativeCone5CaloJets'),
                            Prefix = cms.string('ic5Jet'),
                            Suffix = cms.string('Calo')
                            )

susycafak5calojetreco = cms.EDProducer("SusyCAF_CaloJet",
                            InputTag = cms.InputTag('ak5CaloJets'),
                            Prefix = cms.string('ak5Jet'),
                            Suffix = cms.string('Calo')
                            )

susycafic5calojet = cms.EDProducer("SusyCAF_PatJet",
                            InputTag = cms.InputTag('cleanLayer1JetsIC5'),
                            Prefix = cms.string('ic5Jet'),
                            Suffix = cms.string('Pat')
                            )

susycafak5calojet = cms.EDProducer("SusyCAF_PatJet",
                            InputTag = cms.InputTag('cleanLayer1JetsAK5'),
                            Prefix = cms.string('ak5Jet'),
                            Suffix = cms.string('Pat')
                            )
