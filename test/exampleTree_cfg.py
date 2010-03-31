# Starting with a skeleton process which gets imported with the following line
from PhysicsTools.PatAlgos.patTemplate_cfg import *
process.setName_("SUSYCAF")


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
options.register('JetCorrections', '900GeV', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "GlobalTaget corrections to use")
options.register('mcInfo', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "process MonteCarlo data")
options.register('silentMessageLogger', True, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "silence MessageLogger")
options.register('patify', True, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "run SUSYPAT on the fly")
options.register('fromRECO', True, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "process RECO data (else PAT is assumed)")

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
            if options.GlobalTag == "": options.GlobalTag = 'START3X_V24::All'
	        #first file in /MinBias/Summer09-STARTUP3X_V8P_900GeV-v1/GEN-SIM-RECO
            options.files = '/store/relval/CMSSW_3_5_2/RelValMinBias/GEN-SIM-RECO/START3X_V21-v1/0016/98DDB99F-3B1E-DF11-B244-001731AF66AD.root'
	        # Due to problem in production of LM samples: same event number appears multiple times
            process.source.duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
        else:
            if options.GlobalTag == "": options.GlobalTag = 'GR09_R_35X_V3::All'
	        #first file of run 124230 in /MinimumBias/BeamCommissioning09-SD_AllMinBias-Jan23Skim-v1/RAW-RECO
            options.files = '/store/data/BeamCommissioning09/MinimumBias/RECO/18thFebPreProd_351p1-v3/0000/FAE46E07-C51D-DF11-A7E6-00237DA12CA0.root'
    else:
        if options.mcInfo:
            if options.GlobalTag == "": options.GlobalTag = 'START3X_V24::All'
            options.files = 'rfio://castorcms/?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/edelhoff/SusyCAF/examplePAT/RelValMinBias_10k_V00-09-01_SUSYPAT.root'
            process.source.duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
        else:
            if options.GlobalTag == "": options.GlobalTag = 'GR09_R_35X_V3::All'
            options.files = 'rfio://castorcms/?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/edelhoff/SusyCAF/examplePAT/BeamCommissioning09_MinimumBias_Jan23Skim_V00-05-10.root'

process.source = cms.Source('PoolSource', fileNames = cms.untracked.vstring(options.files) )
process.maxEvents.input = options.maxEvents

#-- Calibration tag -----------------------------------------------------------
process.GlobalTag.globaltag = options.GlobalTag

schedule = cms.Schedule()
if options.patify and options.fromRECO:
    from PhysicsTools.Configuration.SUSY_pattuple_cff import addDefaultSUSYPAT, getSUSY_pattuple_outputCommands
    #Apply SUSYPAT: Parameters are: mcInfo, HLT menu, Jet energy corrections, MC version ('31x' or '31xReReco332')
    addDefaultSUSYPAT(process,options.mcInfo,'HLT',options.JetCorrections,['IC5Calo','SC5Calo','AK7Calo','KT4Calo','AK5PF','AK7PF','IC5PF','AK5JPT','AK5Track']) 
    process.patJetGenJetMatch.maxDeltaR  = cms.double(0.5) #default AK5 jet
    process.patJetGenJetMatchAK7Calo.maxDeltaR  = cms.double(0.5)
    process.patJetGenJetMatchSC5Calo.maxDeltaR  = cms.double(0.5) 
    process.patJetGenJetMatchIC5Calo.maxDeltaR  = cms.double(0.5)
    process.patJetGenJetMatchKT4Calo.maxDeltaR  = cms.double(0.5)
    process.patJetGenJetMatchAK5PF.maxDeltaR  = cms.double(0.5) 
    process.patJetGenJetMatchAK7PF.maxDeltaR  = cms.double(0.5)
    process.patJetGenJetMatchAK5JPT.maxDeltaR  = cms.double(0.5)
    process.patJetGenJetMatchAK5Track.maxDeltaR  = cms.double(0.5) 
    process.susyPat = cms.Path(process.seqSUSYDefaultSequence)
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

process.load('SUSYBSMAnalysis.SusyCAF.SusyCAF_nTuple_cfi')
# choose your event and object pre-selection     v------| there 
from SUSYBSMAnalysis.SusyCAF.SusyCAF_Selection.default_cff import insertSelection
insertSelection(process)

process.p = cms.Path( (process.nTupleCommonSequence) * process.susyTree)
process.lumiPath = cms.Path(process.lumiTree)
if options.mcInfo:
    process.p.replace( process.nTupleCommonSequence, process.nTupleCommonSequence + process.nTupleGenSequence )
else:
    process.p.replace( process.nTupleCommonSequence, process.nTupleCommonSequence + process.nTupleDataSequence )


if options.fromRECO and not options.patify:
    process.p.replace( process.nTupleCommonSequence, process.nTupleCommonSequence + process.nTupleRecoSequence )
else:
    if  options.patify:
        #little havyhanded: want too have met values which are not in SUSYPAT in those trees
         process.p.replace( process.nTupleCommonSequence, process.nTupleCommonSequence + process.nTupleRecoMetSequence )
    if options.mcInfo:
        process.p.replace( process.nTupleCommonSequence, process.nTupleCommonSequence + process.nTuplePatSequence + process.nTuplePatJetMatchedSequence)
    else:
        process.p.replace( process.nTupleCommonSequence, process.nTupleCommonSequence + process.nTuplePatSequence + process.nTuplePatJetSequence)

schedule.append(process.p)
schedule.append(process.lumiPath)

file = open('SusyCAF_Tree_cfg.py','w')
file.write(str(process.dumpPython()))
file.close()