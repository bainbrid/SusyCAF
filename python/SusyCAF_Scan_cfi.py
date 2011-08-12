import FWCore.ParameterSet.Config as cms

scanFormats = {'T1' : r"# model T1_(\\d*\.\\d*)_(\\d*\.\\d*)_(\\d*\.\\d*)\\s",
               'T2' : r"# model T2_(\\d*\.\\d*)_(\\d*\.\\d*)\\s",
               'T1taunu' : r"# model T1taunu_(\\d*\.\\d*)_(\\d*\.\\d*)_(\\d*\.\\d*)\\s",
               'mSugra' : r"# model msugra_(\\d*)_(\\d*)_(m?\\d*)_(m?\\d*)_(m?\\d)\\s"}

scanParameters = {"T1" : ['xCHI', 'mGL', 'mLSP'],
                  "T2" : [ 'mGL', 'mLSP'],
                  "T1taunu" : ['xCHI', 'mGL', 'mLSP'],
                  'mSugra' : ['M0', 'M12', 'tanbeta', 'A0', 'Mu']}

mode = "T1"

susycafscan = cms.EDProducer( "SusyCAF_Scan",
                              InputTag  = cms.InputTag('source'),
                              Prefix    = cms.string('SimpModelScan'),
                              Suffix    = cms.string(''),
                              ScanFormat = cms.string(scanFormats[mode]),
                              ScanParameters = cms.vstring(*scanParameters[mode]),
                              )
