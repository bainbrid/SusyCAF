import FWCore.ParameterSet.Config as cms

scanFormats = {'T1' : r"# model T1_(\\d*\.\\d*)_(\\d*\.\\d*)_(\\d*\.\\d*)\\s",
               'T2' : r"# model T2_(\\d*\.\\d*)_(\\d*\.\\d*)\\s",
               'T1bbbb' : r"# model T1bbbb_(\\d*\.\\d*)_(\\d*\.\\d*)_(\\d*\.\\d*)\\s",
               'T2bb' : r"# model T2bb_(\\d*\.\\d*)_(\\d*\.\\d*)\\s",
               'T3w' : r"# model T3w_(\\d*\.\\d*)_(\\d*\.\\d*)_(\\d*\.\\d*)\\s",
               'T3wb' : r"# model T3wb_(\\d*\.\\d*)_(\\d*\.\\d*)_(\\d*\.\\d*)\\s",
               'T1taunu' : r"# model T1taunu_(\\d*\.\\d*)_(\\d*\.\\d*)_(\\d*\.\\d*)\\s",
               'mSugra' : r"# model msugra_(\\d*)_(\\d*)_(m?\\d*)_(m?\\d*)_(m?\\d)\\s"}

scanParameters = {"T1" : ['xCHI', 'mGL', 'mLSP'],
                  "T2" : [ 'mGL', 'mLSP'],
                  "T1bbbb" : ['xCHI', 'mGL', 'mLSP'],
                  "T2bb" : ['mGL', 'mLSP'],
                  "T3w" : ['xCHI', 'mGL', 'mLSP'],
                  "T3wb" : ['xCHI', 'mGL', 'mLSP'],
                  "T1taunu" : ['xCHI', 'mGL', 'mLSP'],
                  'mSugra' : ['M0', 'M12', 'tanbeta', 'A0', 'Mu']}

mode = "T1taunu"

susycafscan = cms.EDProducer( "SusyCAF_Scan",
                              InputTag  = cms.InputTag('source'),
                              Prefix    = cms.string('SimpModelScan'),
                              Suffix    = cms.string(''),
                              ScanFormat = cms.string(scanFormats[mode]),
                              ScanParameters = cms.vstring(*scanParameters[mode]),
                              )
