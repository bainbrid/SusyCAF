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
options.register('JetCorrections', 'Spring10', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "GlobalTaget corrections to use")
options.register('mcInfo', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "process MonteCarlo data")
options.register('AllTracks', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "include all tracks")
options.register('silentMessageLogger', True, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "silence MessageLogger")
options.register('patify', True, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "run SUSYPAT on the fly")
options.register('fromRECO', True, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "process RECO data (else PAT is assumed)")
options.register('SourceName', "", VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "'S:streamName' or 'DS:datasetName' to store HLT paths in that stream/dataset")

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
            if options.GlobalTag == "": options.GlobalTag = 'START38_V12::All'
            options.files = '/store/relval/CMSSW_3_8_4/RelValTTbar/GEN-SIM-RECO/START38_V12-v1/0024/1A650A81-83C2-DF11-B355-002618FDA287.root'
        else:
            if options.GlobalTag == "": options.GlobalTag = 'GR_R_38X_V13::All'
            options.files = '/store/relval/CMSSW_3_8_4/MinimumBias/RECO/GR_R_38X_V13_RelVal_col_10-v1/0000/043C99EA-60C2-DF11-B6C3-0018F3D0970C.root'
    else:
        if options.mcInfo:
            if options.GlobalTag == "": options.GlobalTag = 'START37_V5::All'
            options.files = 'rfio://castorcms/?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/edelhoff/SusyCAF/examplePAT/RelValMinBias_10k_V00-09-01_SUSYPAT.root'
            process.source.duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
        else:
            if options.GlobalTag == "": options.GlobalTag = 'GR_R_37X_V6::All'
            options.files = 'rfio://castorcms/?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/edelhoff/SusyCAF/examplePAT/BeamCommissioning09_MinimumBias_Jan23Skim_V00-05-10.root'

process.source = cms.Source('PoolSource', fileNames = cms.untracked.vstring(options.files) )
process.maxEvents.input = options.maxEvents

#-- Calibration tag -----------------------------------------------------------
process.GlobalTag.globaltag = options.GlobalTag

schedule = cms.Schedule()

if options.patify and options.fromRECO:
    from PhysicsTools.Configuration.SUSY_pattuple_cff import addDefaultSUSYPAT, getSUSY_pattuple_outputCommands
    #Apply SUSYPAT: Parameters are: mcInfo, HLT menu, Jet energy corrections, MC version ('31x' or '31xReReco332')
    addDefaultSUSYPAT(process,options.mcInfo,'HLT',options.JetCorrections,'',['IC5Calo','AK7Calo','AK5PF','AK7PF','AK5JPT','AK5Track'])
    process.patJetGenJetMatch.maxDeltaR  = cms.double(0.5) #default AK5 jet
    process.patJetGenJetMatchAK7Calo.maxDeltaR  = cms.double(0.5)
    process.patJetGenJetMatchIC5Calo.maxDeltaR  = cms.double(0.5)
    process.patJetGenJetMatchAK5PF.maxDeltaR  = cms.double(0.5)
    process.patJetGenJetMatchAK7PF.maxDeltaR  = cms.double(0.5) 
    process.patJetGenJetMatchAK5JPT.maxDeltaR  = cms.double(0.5)
    #process.patJetGenJetMatchAK7JPT.maxDeltaR  = cms.double(0.5)
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
    process.out.outputCommands.append('keep *_HBHENoiseFilterResultProducer_*_*')
    if options.secondaryOutput == ".root" and hasattr(process,"out"): # remove outpath 
        del process.out
        del process.outpath

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

from SUSYBSMAnalysis.SusyCAF.SusyCAF_HcalRecHit_cfi import loadAndConfigureHcalSeverityLevelProducer
loadAndConfigureHcalSeverityLevelProducer(process,options.mcInfo)
from SUSYBSMAnalysis.SusyCAF.cleaning_cff import addHbheNoiseFilterResult
addHbheNoiseFilterResult(process,schedule)

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
        #little heavyhanded: want to have met values which are not in SUSYPAT in those trees
         process.p.replace( process.nTupleCommonSequence, process.nTupleCommonSequence + process.nTupleRecoPatSequence )
    if options.mcInfo:
        process.p.replace( process.nTupleCommonSequence, process.nTupleCommonSequence + process.nTuplePatSequence + process.nTuplePatJetMatchedSequence)
    else:
        process.p.replace( process.nTupleCommonSequence, process.nTupleCommonSequence + process.nTuplePatSequence + process.nTuplePatJetSequence)

process.susycaftriggers.SourceName  = options.SourceName

schedule.append(process.p)
schedule.append(process.lumiPath)

file = open('SusyCAF_Tree_cfg.py','w')
file.write(str(process.dumpPython()))
file.close()
