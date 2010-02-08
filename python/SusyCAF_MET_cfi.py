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
                               InputTag = cms.InputTag('layer1METsIC5'),
                               Prefix = cms.string('met'),
                               Suffix = cms.string('IC5'),
                               ProduceSpecial = cms.bool(True),
                               Calo=cms.bool(True)
                              
                            )

susycafmetAK5 = cms.EDProducer("SusyCAF_PatMET",
                            InputTag = cms.InputTag('layer1METsAK5'),
                            Prefix = cms.string('met'),
                            Suffix = cms.string('AK5'),
                            ProduceSpecial = cms.bool(True),
                              Calo=cms.bool(True)
                            )

susycafmetPF = cms.EDProducer("SusyCAF_PatMET",
                            InputTag = cms.InputTag('pfLayer1METs'),
                            Prefix = cms.string('met'),
                            Suffix = cms.string('PF'),
                            ProduceSpecial = cms.bool(True),
                              Calo=cms.bool(False)
                             
                            )

susycafmetTC = cms.EDProducer("SusyCAF_PatMET",
                            InputTag = cms.InputTag('layer1METsTC'),
                            Prefix = cms.string('met'),
                            Suffix = cms.string('TC'),
                            ProduceSpecial = cms.bool(True),
                              Calo=cms.bool(False)
                              
                            )

