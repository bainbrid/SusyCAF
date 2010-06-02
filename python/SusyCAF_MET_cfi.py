import FWCore.ParameterSet.Config as cms

susycafmet = cms.EDProducer("SusyCAF_CaloMET",
                            InputTag = cms.InputTag('met'),
                            Prefix = cms.string('met'),
                            Suffix = cms.string('Calo'),
                            ProduceSpecial = cms.bool(True),
                            Calo = cms.bool(True)
                            
                            )

susycafmetnohf = cms.EDProducer("SusyCAF_CaloMET",
                                InputTag = cms.InputTag('metNoHF'),
                                Prefix = cms.string('metnohf'),
                                Suffix = cms.string('Calo'),
                                ProduceSpecial = cms.bool(True),
                                Calo=cms.bool(True)
                               
                                )

susycafmetIC5 = cms.EDProducer("SusyCAF_PatMET",
                               InputTag = cms.InputTag('patMETsIC5Calo'),
                               Prefix = cms.string('met'),
                               Suffix = cms.string('IC5'),
                               ProduceSpecial = cms.bool(True),
                               Calo=cms.bool(True)
                              
                            )

susycafmetAK5 = cms.EDProducer("SusyCAF_PatMET",
                            InputTag = cms.InputTag('patMETsAK5Calo'),
                            Prefix = cms.string('met'),
                            Suffix = cms.string('AK5'),
                            ProduceSpecial = cms.bool(True),
                              Calo=cms.bool(True)
                            )

susycafmetAK5TypeII = cms.EDProducer("SusyCAF_PatMET",
                            InputTag = cms.InputTag('patMETsAK5CaloTypeII'),
                            Prefix = cms.string('met'),
                            Suffix = cms.string('AK5TypeII'),
                            ProduceSpecial = cms.bool(True),
                              Calo=cms.bool(True)
                            )

susycafmetPF = cms.EDProducer("SusyCAF_PatMET",
                            InputTag = cms.InputTag('patMETsPF'),
                            Prefix = cms.string('met'),
                            Suffix = cms.string('PF'),
                            ProduceSpecial = cms.bool(True),
                              Calo=cms.bool(False)
                             
                            )

susycafmetTC = cms.EDProducer("SusyCAF_PatMET",
                            InputTag = cms.InputTag('patMETsTC'),
                            Prefix = cms.string('met'),
                            Suffix = cms.string('TC'),
                            ProduceSpecial = cms.bool(True),
                              Calo=cms.bool(False)
                              
                            )

