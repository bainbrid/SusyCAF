# Starting with a skeleton process which gets imported with the following line
from PhysicsTools.PatAlgos.patTemplate_cfg import *
process.setName_("SUSYCAF")
schedule = cms.Schedule()

import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing ('standard')
vtype = VarParsing.VarParsing.varType
single = VarParsing.VarParsing.multiplicity.singleton
#options.files = "somefile.root" # will select example files automatically
options.output = "SusyCAF_Tree.root"
options.secondaryOutput = "" #switch PAT-tuple output off by default
options.maxEvents = 100
options.register(          'GlobalTag', "",         single, vtype.string, "GlobalTag to use")
options.register(     'jetCorrections',['L2Relative','L3Absolute'], VarParsing.VarParsing.multiplicity.list, vtype.string, "jet correction levels to apply")
options.register(     'JetCorrections', 'Spring10', single, vtype.string, "GlobalTag jet corrections to use, obsolete with SusyPAT for 3_8_6")
options.register(             'mcInfo', False,      single, vtype.int,    "process MonteCarlo data")
options.register(          'AllTracks', False,      single, vtype.int,    "include all tracks")
options.register(    'hbheNoiseFilter', True,       single, vtype.int,    "include hbhe noise filter result")
options.register('silentMessageLogger', True,       single, vtype.int,    "silence MessageLogger")
options.register(             'patify', True,       single, vtype.int,    "run SUSYPAT on the fly")
options.register(           'fromRECO', True,       single, vtype.int,    "process RECO data (else PAT is assumed)")
options.register(            'fromRAW', False,      single, vtype.int,    "process RAW data")
options.register(         'withoutJPT', False,      single, vtype.int,    "do not include JPT jets")
options.register(         'SourceName', "",         single, vtype.string, "'S:streamName' or 'DS:datasetName' to store HLT paths in that stream/dataset")
options.parseArguments()
options._tagOrder =[]
process.load('SUSYBSMAnalysis.SusyCAF.SusyCAF_nTuple_cfi')
process.susycaftriggers.SourceName  = options.SourceName
process.load('Configuration.StandardSequences.Services_cff')
process.add_( cms.Service( "TFileService", fileName = cms.string( options.output ), closeFileFast = cms.untracked.bool(True) ) )
if options.silentMessageLogger:
    process.MessageLogger.categories.append('PATSummaryTables')
    process.MessageLogger.cerr.PATSummaryTables = cms.untracked.PSet( limit = cms.untracked.int32(-1), reportEvery = cms.untracked.int32(1))

if len(options.jetCorrections) and type(options.jetCorrections[0]) is list :
    #hack around bug
    tmp = options.jetCorrections[0]
    options.clearList("jetCorrections")
    options.jetCorrections = tmp

#-- Input Source --------------------------------------------------------------
defaultGT,defaultFile = ([[( 'GR_R_37X_V6::All','error, no default file defined'),
                           (  'START37_V5::All','error, no default file defined')],
                          [('GR10_P_V11::All','/store/data/Run2010B/MultiJet/RECO/PromptReco-v2/000/149/294/08FCCA78-05E5-DF11-8925-0030487CD6B4.root'),
                           ( 'START38_V12::All','/store/relval/CMSSW_3_8_4/RelValTTbar/GEN-SIM-RECO/START38_V12-v1/0024/1A650A81-83C2-DF11-B355-002618FDA287.root')]
                          ])[options.fromRECO][options.mcInfo]
process.GlobalTag.globaltag = options.GlobalTag if options.GlobalTag else defaultGT
process.source = cms.Source('PoolSource', fileNames = cms.untracked.vstring(options.files if options.files else defaultFile) )
process.maxEvents.input = options.maxEvents


if options.patify and options.fromRECO:
    jetAlgoList = ['IC5Calo','AK7Calo','AK5PF','AK7PF']
    if not options.withoutJPT : jetAlgoList +=['AK5JPT'] #+['AK5Track']
    from PhysicsTools.Configuration.SUSY_pattuple_cff import addDefaultSUSYPAT
    addDefaultSUSYPAT(process,options.mcInfo,'HLT',options.jetCorrections,'',jetAlgoList)
    for algo in ['']+jetAlgoList :
        setattr( getattr( process, 'patJetGenJetMatch'+algo), 'maxDeltaR', cms.double(0.5) )
    process.susyPat = cms.Path(process.susyPatDefaultSequence)
    schedule.append(process.susyPat)

    #-- Output module configuration -----------------------------------------------
    process.out.fileName = options.secondaryOutput
    # Custom settings
    process.out.splitLevel = cms.untracked.int32(99)  # Turn on split level (smaller files?)
    process.out.overrideInputFileSplitLevels = cms.untracked.bool(True)
    process.out.dropMetaData = cms.untracked.string('DROPPED')   # Get rid of metadata related to dropped collections

    from PhysicsTools.Configuration.SUSY_pattuple_cff import getSUSY_pattuple_outputCommands
    SUSY_pattuple_outputCommands = getSUSY_pattuple_outputCommands( process )
    process.out.outputCommands = cms.untracked.vstring('drop *', *SUSY_pattuple_outputCommands )
    process.out.outputCommands.append('keep *_HBHENoiseFilterResultProducer_*_*')
    if options.secondaryOutput == ".root" and hasattr(process,"out"): # remove outpath 
        del process.out
        del process.outpath


import SUSYBSMAnalysis.SusyCAF.SusyCAF_ProcessAdjustments_cfi as adjust
adjust.addTypeIIMet(process)
adjust.loadAndConfigureHcalSeverityLevelProducer(process, options.mcInfo)
if options.hbheNoiseFilter : adjust.addHbheNoiseFilterResult(process, schedule)
if options.fromRAW : adjust.addEcalUnpacking(process, schedule, options.mcInfo)
if options.withoutJPT : adjust.removeJPT(process)

if options.patify or not options.fromRECO :
    from SUSYBSMAnalysis.SusyCAF.SusyCAF_Selection.default_cff import insertSelection
    insertSelection(process)
else : print "WARNING: selection (slimming) not applied for options patify(False) and fromRECO(True)."

process.lumiPath = cms.Path(process.lumiTree)
schedule.append(process.lumiPath)

process.nEmpty = cms.Sequence()
process.p = cms.Path(  (  process.nCommon +
                          ( process.nEmpty if not options.fromRECO else \
                            (  process.nReco if not options.patify else \
                               ( process.nRecoPat + process.nPat +
                                 ( process.nPatJetMatched if options.mcInfo else process.nPatJet )))) +
                          ( process.nAllTrack if options.AllTracks else process.nEmpty ) +
                          ( process.nGen if options.mcInfo else process.nData ) )
                       * process.susycafReducer
                       * process.susyTree )
schedule.append(process.p)

# write this config as a single file
file = open('SusyCAF_Tree_cfg.py','w')
file.write(str(process.dumpPython()))
file.close()
