import FWCore.ParameterSet.Config as cms

susycafmet = cms.EDProducer("SusyCAF_CaloMET",
                            InputTag = cms.InputTag('met'),
                            Prefix = cms.string('met'),
                            Suffix = cms.string('Calo'),
                            ProduceSpecial = cms.bool(False)
                            )

susycafmetnohf = cms.EDProducer("SusyCAF_CaloMET",
                            InputTag = cms.InputTag('metNoHF'),
                            Prefix = cms.string('metnohf'),
                            Suffix = cms.string('Calo'),
                            ProduceSpecial = cms.bool(False)
                            )

susycafmetIC5 = cms.EDProducer("SusyCAF_PatMET",
                            InputTag = cms.InputTag('layer1METsIC5'),
                            Prefix = cms.string('met'),
                            Suffix = cms.string('IC5'),
                            ProduceSpecial = cms.bool(False)
                            )

susycafmetAK5 = cms.EDProducer("SusyCAF_PatMET",
                            InputTag = cms.InputTag('layer1METsAK5'),
                            Prefix = cms.string('met'),
                            Suffix = cms.string('AK5'),
                            ProduceSpecial = cms.bool(False)
                            )

susycafmetPF = cms.EDProducer("SusyCAF_PatMET",
                            InputTag = cms.InputTag('layer1METsPF'),
                            Prefix = cms.string('met'),
                            Suffix = cms.string('PF'),
                            ProduceSpecial = cms.bool(False)
                            )

susycafmetTC = cms.EDProducer("SusyCAF_PatMET",
                            InputTag = cms.InputTag('layer1METsTC'),
                            Prefix = cms.string('met'),
                            Suffix = cms.string('TC'),
                            ProduceSpecial = cms.bool(False)
                            )
