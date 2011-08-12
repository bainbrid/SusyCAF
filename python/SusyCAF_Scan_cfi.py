import FWCore.ParameterSet.Config as cms

scanFormats = {'T1' : r"# model T1_(\\d*\.\\d*)_(\\d*\.\\d*)_(\\d*\.\\d*)\\s",
               'T2' : r"# model T2_(\\d*\.\\d*)_(\\d*\.\\d*)\\s",
               'T1taunu' : r"# model T1taunu_(\\d*\.\\d*)_(\\d*\.\\d*)_(\\d*\.\\d*)\\s",
               'mSugra' : r"# model msugra_(\\d*)_(\\d*)_(m?\\d*)_(m?\\d*)_(m?\\d)\\s"}

ScanParameters = {"T1" : ['xCHI', 'mGL', 'mLSP'],
                  "T2" : [ 'mGL', 'mLSP'],
                  "T1taunu" : ['xCHI', 'mGL', 'mLSP'],
                  'mSugra' : ['M0', 'M12', 'tanbeta', 'A0', 'Mu']}

mode = "T1"
                  
def parseXSecFiles(path, regExpr, factor = 1.):
    from re import match
    result = []
    file = open(path, "r")
    lines = file.read().splitlines()
    file.close()
    for line in  lines:
        result.append(cms.PSet())
        if (match(regExpr,line) != None):
            rawParams = match(regExpr,line).groupdict()
            for key, value in rawParams.items():
                value = value.replace("m","-")
                setattr(result[-1], key, cms.double(factor * float(value)))
        else:
            print "WARNING: ignoring line '%s' in '%s'"%(line, path)
    return result

def exportAdditionParameters( basePath, outPath):
    xSecRegExpr = r".*msugra_(?P<M0>[0-9]*)_(?P<M12>[0-9]*)_(?P<tanbeta>m?[0-9]*)_(?P<A0>m?[0-9]*)_(?P<Mu>m?[0-9]*)\.slha[\w]*(?P<CrossSection>.*)"
    pSetList = []
    pSetList += parseXSecFiles(basePath + "goodModelNames_40_m500_1.txt", xSecRegExpr)
    pSetList += parseXSecFiles(basePath + "badModelNames_40_m500_1.txt", xSecRegExpr, -1.)
    template = """
import FWCore.ParameterSet.Config as cms
parameters = %s    
"""

    outFile = open(outPath,"w")
    outFile.write(template%(cms.VPSet(pSetList).dumpPython())[1:-1])
    outFile.close()

if __name__ == "__main__":
    from sys import argv
    assert len(argv) == 3, "usage: SusyCAF_Scan_cfi.py basePath outPath"
    exportAdditionParameters(argv[1], argv[2])

#generated running this file as __main__:
from xSecLO_Scan_40_m500_cff import parameters as xSecLO_Scan_40_m500_Parameters

susycafscan = cms.EDProducer( "SusyCAF_Scan",
                              InputTag  = cms.InputTag('source'),
                              Prefix    = cms.string('SimpModelScan'),
                              Suffix    = cms.string(''),
                              ScanFormat = cms.string(scanFormats[mode]),
                              ScanParameters = cms.vstring(*scanParameters[mode]),
                              Debug = cms.untracked.bool(False)
                              )

                              AdditionalParameters = xSecLO_Scan_40_m500_Parameters,
#For on the fly parsing: 
#                              AdditionalParameters = cms.VPSet( parseXSecFiles("goodModelNames_40_m500_1.txt", xSecRegExpr)
#                                                                +parseXSecFiles("badModelNames_40_m500_1.txt", xSecRegExpr, -1.)
#                                                               ),
                              AdditionalParameterDefaults = cms.PSet( CrossSection = cms.double(-10.0) ),
)


