import FWCore.ParameterSet.Config as cms

susycafelectronreco = cms.EDProducer("SusyCAF_GsfElectron",
                            InputTag = cms.InputTag('gsfElectrons'),
                            Prefix = cms.string('electron'),
                            Suffix = cms.string('Gsf')
                            )

susycafelectron = cms.EDProducer("SusyCAF_PatElectron",
                            InputTag = cms.InputTag('cleanLayer1Electrons'),
                            Prefix = cms.string('electron'),
                            Suffix = cms.string('Pat')
                            )

susycafpfelectron = cms.EDProducer("SusyCAF_PatElectron",
                                   InputTag = cms.InputTag('pfLayer1Electrons'),
                                   Prefix = cms.string('electron'),
                                   Suffix = cms.string('PF')
                                   )
