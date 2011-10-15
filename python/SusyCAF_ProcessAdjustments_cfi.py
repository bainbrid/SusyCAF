import FWCore.ParameterSet.Config as cms

def loadAndConfigureHcalSeverityLevelProducer(process, isData) :
    process.load("RecoLocalCalo.HcalRecAlgos.hcalRecAlgoESProd_cfi")
    if isData :
        process.hcalRecAlgos.SeverityLevels[3].RecHitFlags.remove("HFDigiTime")
        process.hcalRecAlgos.SeverityLevels[4].RecHitFlags.append("HFDigiTime")

def loadAndConfigureEcalSeverityLevelProducer(process) :
    process.load("RecoLocalCalo.EcalRecAlgos.EcalSeverityLevelESProducer_cfi")

def messageLogger(process,quiet) :
    if quiet :
        process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
        for item in [process.MessageLogger.cerr.getParameter(name) for name in process.MessageLogger.cerr.parameterNames_()] :
            if type(item) is cms.PSet :
                item.reportEvery = cms.untracked.int32(1000)
    else :
        process.MessageLogger.categories.append('PATSummaryTables')
        process.MessageLogger.cerr.PATSummaryTables = cms.untracked.PSet( limit=cms.untracked.int32(-1), reportEvery=cms.untracked.int32(1))



def __patOutput__(process,fileName) :
    if fileName == ".root" and hasattr(process,"out"): # remove outpath 
        del process.out
        del process.outpath
    else :
        process.out.fileName = fileName
        process.out.splitLevel = cms.untracked.int32(99)
        process.out.overrideInputFileSplitLevels = cms.untracked.bool(True)
        process.out.dropMetaData = cms.untracked.string('DROPPED')   # Get rid of metadata related to dropped collections
        
        from PhysicsTools.Configuration.SUSY_pattuple_cff import getSUSY_pattuple_outputCommands
        SUSY_pattuple_outputCommands = getSUSY_pattuple_outputCommands( process )
        process.out.outputCommands = cms.untracked.vstring('drop *', *SUSY_pattuple_outputCommands )
        process.out.outputCommands.append('keep *_HBHENoiseFilterResultProducer_*_*')

def patAllElectronsPF(process) :
    from PhysicsTools.PatAlgos.producersLayer1.electronProducer_cfi import patElectrons
    process.patAllElectronsPF = patElectrons.clone( # override defaults
        pfElectronSource = "pfAllElectronsPF",
        useParticleFlow = True,
        genParticleMatch = "",
        addGenMatch = False,
        embedGenMatch = False,
        embedTrack = True
        )
    return process.patAllElectronsPF

def patAllMuonsPF(process) :
    from PhysicsTools.PatAlgos.producersLayer1.muonProducer_cfi import patMuons
    process.patAllMuonsPF = patMuons.clone( #override defaults
        pfMuonSource = "pfAllMuonsPF",
        useParticleFlow = True,
        addGenMatch = False,
        genParticleMatch = "",
        embedTrack = True,
        embedGenMatch = False,
        embedPickyMuon = False,
        embedTpfmsMuon = False,
        embedHighLevelSelection = False,
        embedCaloMETMuonCorrs = False,
        embedTcMETMuonCorrs = False
        )
    return process.patAllMuonsPF

def susyPat(process,options) :
    if not options.patify:
        if not options.quiet : print "WARNING: selection (slimming) not applied for options patify(False)."
        __patOutput__(process, options.secondaryOutput)
        return cms.Path()
    else:
        from PhysicsTools.Configuration.SUSY_pattuple_cff import addDefaultSUSYPAT
        jetAlgoList = filter(lambda s: s.lower() in options.jetCollections, ['AK7Calo','AK5PF','AK7PF'])
        addDefaultSUSYPAT(process, mcInfo = not options.isData, HLTMenu = 'HLT', jetMetCorrections = options.jetCorrections, theJetNames = jetAlgoList)
        for algo in ['']+jetAlgoList :
            setattr( getattr( process, 'patJetGenJetMatch'+algo), 'maxDeltaR', cms.double(0.7 if '7' in algo else 0.5) )
        __patOutput__(process, options.secondaryOutput)
        return cms.Path(process.susyPatDefaultSequence + patAllElectronsPF(process) + patAllMuonsPF(process))

def addHbheNoiseFilterResult(process, options) :
    process.load('CommonTools/RecoAlgos/HBHENoiseFilterResultProducer_cfi')
    if not options.hbheNoiseFilterDefaultIsoReq :
        process.HBHENoiseFilterResultProducer.minIsolatedNoiseSumE = 999999.0
        process.HBHENoiseFilterResultProducer.minNumIsolatedNoiseChannels = 999999
        process.HBHENoiseFilterResultProducer.minIsolatedNoiseSumEt = 999999.0
    process.hcalNoiseSummaryExists = cms.EDFilter('SusyCAF_HcalNoiseSummaryExists')
    return cms.Path(process.hcalNoiseSummaryExists + process.HBHENoiseFilterResultProducer)

def addEcalDeadCellFlag(process, options) :
    from JetMETAnalysis.ecalDeadCellTools.EcalDeadCellEventFilter_cfi import *
    process.ecaldeadcellfilterflag = EcalDeadCellEventFilter.clone(taggingMode = True)
    return cms.Path(process.ecaldeadcellfilterflag)

def addTrackingFailureFlag(process, options) :
    process.load('SandBox.Skims.vertex_cfi')
    from SandBox.Skims.trackingFailureFilter_cfi import trackingFailureFilter
    process.trackingfailurefilterflag = trackingFailureFilter.clone(taggingMode = True)
    return cms.Path( process.goodVerticesRA2 * process.trackingfailurefilterflag )

def lumiTree(process) :
    process.load('SUSYBSMAnalysis.SusyCAF.SusyCAF_LumiTreeMaker_cfi')
    return cms.Path(process.lumiTree)


