import FWCore.ParameterSet.Config as cms

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

basePath = "/.automount/home/home__home4/institut_1b/edelhoff/superSymmetry/CMSSW_4_2_5/src/SUSYBSMAnalysis/SusyCAF/"
xSecRegExpr = r".*msugra_(?P<M0>[0-9]*)_(?P<M12>[0-9]*)_(?P<tanbeta>m?[0-9]*)_(?P<A0>m?[0-9]*)_(?P<Mu>m?[0-9]*)\.slha[\w]*(?P<Crosssection>.*)"

susycafscan = cms.EDProducer( "SusyCAF_Scan",
                              InputTag  = cms.InputTag('source'),
                              Prefix    = cms.string('susyScan'),
                              Suffix    = cms.string(''),
                              ScanFormat = cms.string(r"# model msugra_(\\d*)_(\\d*)_(m?\\d*)_(m?\\d*)_(m?\\d)\\s"),
                              ScanParameters = cms.vstring('M0', 'M12', 'tanbeta', 'A0', 'Mu'),

#                              AdditionalParameters = cms.VPSet( parseXSecFiles(basePath + "goodModelNames_40_m500_1.txt", xSecRegExpr)
#                                                                parseXSecFiles(basePath + "badModelNames_40_m500_1.txt", xSecRegExpr, -1.)
#                                                               ),
#                              AdditionalParameterDefaults = cms.PSet( Crosssection = cms.double(-10.0) ),
)
