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
susycafsc5calojetreco = cms.EDProducer("SusyCAF_CaloJet",
                            InputTag = cms.InputTag('sisCone5CaloJets'),
                            Prefix = cms.string('sc5Jet'),
                            Suffix = cms.string('Calo')
                            )



susycafic5calojet = cms.EDProducer("SusyCAF_PatJet",
                            InputTag = cms.InputTag('cleanLayer1JetsIC5'),
                            PrimaryVertexTag = cms.InputTag('offlinePrimaryVertices'),
                            MaxD0Trk = cms.double(0.02),
                            MinPtTrk = cms.double(0.3),
                            MaxPtTrk = cms.double(500),
                            MaxChi2Trk = cms.double(100.),
                            Prefix = cms.string('ic5Jet'),
                            Suffix = cms.string('Pat')
                            )

susycafak5calojet = cms.EDProducer("SusyCAF_PatJet",
                            InputTag = cms.InputTag('cleanLayer1JetsAK5'),
                            PrimaryVertexTag = cms.InputTag('offlinePrimaryVertices'),
                            MaxD0Trk = cms.double(0.02),
                            MinPtTrk = cms.double(0.3),
                            MaxPtTrk = cms.double(500),
                            MaxChi2Trk = cms.double(100),
                            Prefix = cms.string('ak5Jet'),
                            Suffix = cms.string('Pat')
                            )
susycafsc5calojet = cms.EDProducer("SusyCAF_PatJet",
                            InputTag = cms.InputTag('cleanLayer1JetsSC5'),
                            PrimaryVertexTag = cms.InputTag('offlinePrimaryVertices'),
                            MaxD0Trk = cms.double(0.02),
                            MinPtTrk = cms.double(0.3),
                            MaxPtTrk = cms.double(500),
                            MaxChi2Trk = cms.double(100),
                            Prefix = cms.string('sc5Jet'),
                            Suffix = cms.string('Pat')
                            )
