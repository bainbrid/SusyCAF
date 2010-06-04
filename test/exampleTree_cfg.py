# Starting with a skeleton process which gets imported with the following line
from PhysicsTools.PatAlgos.patTemplate_cfg import *
process.setName_("SUSYCAF")

process.options = cms.untracked.PSet(
    SkipEvent = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(False) 
    )

import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing ('standard')

#---set defaults
#  for standard options
#options.files = "somefile.root" # will select example files automatically
options.output = "SusyCAF_Tree.root"
options.secondaryOutput = "" #switch PAT-tuple output off by default
options.maxEvents = 100
#  for SusyCaf specifics
options.register('GlobalTag', "", VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "GlobalTag to use")
options.register('JetCorrections', 'Spring10', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "GlobalTaget corrections to use")
options.register('mcInfo', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "process MonteCarlo data")
options.register('AllTracks', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "include all tracks")
options.register('silentMessageLogger', True, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "silence MessageLogger")
options.register('patify', True, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "run SUSYPAT on the fly")
options.register('fromRECO', True, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "process RECO data (else PAT is assumed)")
options.register('NoiseCleaning', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "JetMETRecommendedReflaggingAndReReco")

#---parse user input
options.parseArguments()
options._tagOrder =[]

#-- Message Logger ------------------------------------------------------------
if options.silentMessageLogger:
    process.MessageLogger.categories.append('PATSummaryTables')
    process.MessageLogger.cerr.PATSummaryTables = cms.untracked.PSet(
            limit = cms.untracked.int32(-1),
            reportEvery = cms.untracked.int32(100)
    )
    process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.load('Configuration.StandardSequences.Services_cff')
process.add_( cms.Service( "TFileService",
    fileName = cms.string( options.output ),
    closeFileFast = cms.untracked.bool(True) ) 
)

#-- Input Source --------------------------------------------------------------
if options.files == []:
    if options.fromRECO:
        if options.mcInfo:
            if options.GlobalTag == "": options.GlobalTag = 'START36_V7::All'
	        #first file in /MinBias/Summer09-STARTUP3X_V8P_900GeV-v1/GEN-SIM-RECO
            options.files = '/store/relval/CMSSW_3_5_2/RelValMinBias/GEN-SIM-RECO/START3X_V21-v1/0016/98DDB99F-3B1E-DF11-B244-001731AF66AD.root'
	        # Due to problem in production of LM samples: same event number appears multiple times
            process.source.duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
        else:
            if options.GlobalTag == "": options.GlobalTag = 'GR_R_36X_V9::All'
	        #first file of run 124230 in /MinimumBias/BeamCommissioning09-SD_AllMinBias-Jan23Skim-v1/RAW-RECO
            options.files = '/store/data/BeamCommissioning09/MinimumBias/RECO/18thFebPreProd_351p1-v3/0000/FAE46E07-C51D-DF11-A7E6-00237DA12CA0.root'
    else:
        if options.mcInfo:
            if options.GlobalTag == "": options.GlobalTag = 'START36_V7::All'
            options.files = 'rfio://castorcms/?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/edelhoff/SusyCAF/examplePAT/RelValMinBias_10k_V00-09-01_SUSYPAT.root'
            process.source.duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
        else:
            if options.GlobalTag == "": options.GlobalTag = 'GR_R_36X_V9::All'
            options.files = 'rfio://castorcms/?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/edelhoff/SusyCAF/examplePAT/BeamCommissioning09_MinimumBias_Jan23Skim_V00-05-10.root'

process.source = cms.Source('PoolSource', fileNames = cms.untracked.vstring(options.files) )
process.maxEvents.input = options.maxEvents

#-- Calibration tag -----------------------------------------------------------
process.GlobalTag.globaltag = options.GlobalTag

schedule = cms.Schedule()

# Noise cleaning
if bool(options.NoiseCleaning) :
    from SUSYBSMAnalysis.SusyCAF.cleaning_cff import addNoiseCleaning
    addNoiseCleaning(process,schedule,options.mcInfo)

theJetNames = ['IC5Calo','AK7Calo','AK5PF','AK5JPT','AK5Track']
if options.patify and options.fromRECO:
    from PhysicsTools.Configuration.SUSY_pattuple_cff import addDefaultSUSYPAT, getSUSY_pattuple_outputCommands
    #Apply SUSYPAT: Parameters are: mcInfo, HLT menu, Jet energy corrections, MC version ('31x' or '31xReReco332')
    addDefaultSUSYPAT(process,options.mcInfo,'HLT',options.JetCorrections,'35x',theJetNames) 
    process.patJetGenJetMatch.maxDeltaR  = cms.double(0.5) #default AK5 jet
    process.patJetGenJetMatchAK7Calo.maxDeltaR  = cms.double(0.5)
    process.patJetGenJetMatchIC5Calo.maxDeltaR  = cms.double(0.5)
    process.patJetGenJetMatchAK5PF.maxDeltaR  = cms.double(0.5) 
    process.patJetGenJetMatchAK5JPT.maxDeltaR  = cms.double(0.5)
    process.patJetGenJetMatchAK5Track.maxDeltaR  = cms.double(0.5) 
    process.susyPat = cms.Path(process.susyPatDefaultSequence)
    schedule.append(process.susyPat)
    SUSY_pattuple_outputCommands = getSUSY_pattuple_outputCommands( process )

    #-- Output module configuration -----------------------------------------------
    process.out.fileName = options.secondaryOutput
    # Custom settings
    process.out.splitLevel = cms.untracked.int32(99)  # Turn on split level (smaller files???)
    process.out.overrideInputFileSplitLevels = cms.untracked.bool(True)
    process.out.dropMetaData = cms.untracked.string('DROPPED')   # Get rid of metadata related to dropped collections

    process.out.outputCommands = cms.untracked.vstring('drop *', *SUSY_pattuple_outputCommands )
    if options.secondaryOutput == ".root" and hasattr(process,"out"): # remove outpath 
        del process.out
        del process.outpath

##@@ Temporary hack as BTag discriminators not compatible with noise cleaning recipe
if bool(options.NoiseCleaning) :
    theJetNames.append('')
    for jetName in theJetNames:
        module = getattr(process,'patJets'+jetName)
        module.addDiscriminators = False 

# Add reco::MET with Type II correction 
from PhysicsTools.PatAlgos.recoLayer0.jetMETCorrections_cff import *
process.metJESCorAK5CaloJetTypeII = metJESCorAK5CaloJet.clone()
process.metJESCorAK5CaloJetTypeII.useTypeII = True
process.metJESCorAK5CaloJetTypeII.hasMuonsCorr = False
# Add muon corrections for above II reco::MET
process.metJESCorAK5CaloJetMuonsTypeII = process.metJESCorAK5CaloJetMuons.clone(
    uncorMETInputTag = cms.InputTag('metJESCorAK5CaloJetTypeII')
    )
# Add to recoLayer0 sequence
process.patMETCorrections.replace(
    process.metJESCorAK5CaloJet,
    (process.metJESCorAK5CaloJetTypeII*
     process.metJESCorAK5CaloJetMuonsTypeII)+
    process.metJESCorAK5CaloJet
    )
# Add pat::MET with Type II correction
process.patMETsAK5CaloTypeII = process.patMETs.clone(
    metSource = cms.InputTag("metJESCorAK5CaloJetMuonsTypeII")
    )
# Add to producersLayer1 sequence
process.makePatMETs.replace(
    process.patMETs,
    process.patMETs+
    process.patMETsAK5CaloTypeII
    )

process.load('SUSYBSMAnalysis.SusyCAF.SusyCAF_nTuple_cfi')
# choose your event and object pre-selection     v------| there 

from SUSYBSMAnalysis.SusyCAF.SusyCAF_Selection.default_cff import insertSelection
if options.fromRECO and not options.patify:
    print "WARNING selection not implemented for use from RECO"
else:
    insertSelection(process)

if not options.NoiseCleaning :
    from SUSYBSMAnalysis.SusyCAF.SusyCAF_HcalRecHit_cfi import loadAndConfigureHcalSeverityLevelProducer,makeAndScheduleHcalReFlaggingPath
    loadAndConfigureHcalSeverityLevelProducer(process)
    #will not be needed for long ---v
    makeAndScheduleHcalReFlaggingPath(process,schedule)

process.p = cms.Path( (process.nTupleCommonSequence) * process.susyTree)
process.lumiPath = cms.Path(process.lumiTree)
if options.mcInfo:
    process.p.replace( process.nTupleCommonSequence, process.nTupleCommonSequence + process.nTupleGenSequence )
else:
    process.p.replace( process.nTupleCommonSequence, process.nTupleCommonSequence + process.nTupleDataSequence )

if options.AllTracks:
    process.p.replace(process.nTupleCommonSequence, process.nTupleCommonSequence + process.nTupleAllTrackSequence)

if options.fromRECO and not options.patify:
    process.p.replace( process.nTupleCommonSequence, process.nTupleCommonSequence + process.nTupleRecoSequence )
else:
    if  options.patify:
        #little havyhanded: want too have met values which are not in SUSYPAT in those trees
         process.p.replace( process.nTupleCommonSequence, process.nTupleCommonSequence + process.nTupleRecoPatSequence )
    if options.mcInfo:
        process.p.replace( process.nTupleCommonSequence, process.nTupleCommonSequence + process.nTuplePatSequence + process.nTuplePatJetMatchedSequence)
    else:
        process.p.replace( process.nTupleCommonSequence, process.nTupleCommonSequence + process.nTuplePatSequence + process.nTuplePatJetSequence)

schedule.append(process.p)
schedule.append(process.lumiPath)

file = open('SusyCAF_Tree_cfg.py','w')
file.write(str(process.dumpPython()))
file.close()
