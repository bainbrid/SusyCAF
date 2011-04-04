import FWCore.ParameterSet.Config as cms

susycafelectronreco = cms.EDProducer("SusyCAF_GsfElectron",
                                     InputTag = cms.InputTag('gsfElectrons'),
                                     SelectedElectrons = cms.InputTag(''),
                                     Prefix = cms.string('electron'),
                                     Suffix = cms.string('Gsf'),
                                     StoreConversionInfo = cms.bool(True)
                                     )

susycafelectron = cms.EDProducer("SusyCAF_PatElectron",
                                 InputTag = cms.InputTag('cleanPatElectrons'),
                                 SelectedElectrons = cms.InputTag(''),
                                 Prefix = cms.string('electron'),
                                 Suffix = cms.string('Pat'),
                                 StoreConversionInfo = cms.bool(True)
                                 )

susycafpfelectron = cms.EDProducer("SusyCAF_PatElectron",
                                   InputTag = cms.InputTag('patAllElectronsPF'),
                                   SelectedElectrons = cms.InputTag('selectedPatElectronsPF'),
                                   Prefix = cms.string('electron'),
                                   Suffix = cms.string('PF'),
                                   StoreConversionInfo = cms.bool(True)
                                   )

