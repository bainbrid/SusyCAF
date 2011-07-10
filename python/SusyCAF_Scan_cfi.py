import FWCore.ParameterSet.Config as cms

susycafscan = cms.EDProducer( "SusyCAF_Scan",
                              InputTag  = cms.InputTag('source'),
                              Prefix    = cms.string('susyScan'),
                              Suffix    = cms.string(''),
                              ScanFormat = cms.string(r"# model msugra_(\\d*)_(\\d*)_(\\d*)_(\\d*)_(-?\\d)\\s"),
                              ScanParameters = cms.vstring('M0', 'M12', 'A0', 'tanbeta', 'Mu')
                              )
