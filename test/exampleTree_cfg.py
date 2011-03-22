def hack_ListVarparsingBug(options,item) :
    val = getattr(options,item)
    if len(val) and type(val[0]) is list :
        tmp = val[0]
        options.clearList(item)
        setattr(options,item, tmp)

# Starting with a skeleton process which gets imported with the following line
from PhysicsTools.PatAlgos.patTemplate_cfg import *
process.setName_("SUSYCAF")
schedule = cms.Schedule()

import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing ('standard')
vtype = VarParsing.VarParsing.varType
mtype = VarParsing.VarParsing.multiplicity
options.output = "SusyCAF_Tree.root"
options.secondaryOutput = "" #switch PAT-tuple output off by default
options.maxEvents = 100
options.register(     'jetCorrections',['L2Relative','L3Absolute'], mtype.list, vtype.string, "jet correction levels to apply")
options.register(          'GlobalTag', "",     mtype.singleton, vtype.string, "GlobalTag to use")
options.register(             'mcInfo', False,  mtype.singleton, vtype.int,    "process MonteCarlo data")
options.register(          'AllTracks', False,  mtype.singleton, vtype.int,    "include all tracks")
options.register(    'hbheNoiseFilter', True,   mtype.singleton, vtype.int,    "include hbhe noise filter result")
options.register('silentMessageLogger', True,   mtype.singleton, vtype.int,    "silence MessageLogger")
options.register(             'patify', True,   mtype.singleton, vtype.int,    "run SUSYPAT on the fly")
options.register(         'SourceName', "",     mtype.singleton, vtype.string, "'S:stream' or 'DS:dataset' to store those HLT paths")
options.parseArguments()
options._tagOrder =[] # weird option, but something to do with options.output
hack_ListVarparsingBug( options, 'jetCorrections')

process.load('Configuration.StandardSequences.Services_cff')
process.add_( cms.Service( "TFileService", fileName = cms.string( options.output ), closeFileFast = cms.untracked.bool(True) ) )
if options.silentMessageLogger:
    process.MessageLogger.categories.append('PATSummaryTables')
    process.MessageLogger.cerr.PATSummaryTables = cms.untracked.PSet( limit = cms.untracked.int32(-1), reportEvery = cms.untracked.int32(1))

process.load('SUSYBSMAnalysis.SusyCAF.SusyCAF_nTuple_cfi')
process.susycaftriggers.SourceName  = options.SourceName


#-- Input Source --------------------------------------------------------------
defaultGT,defaultFile = ([('GR_P_V14::All','file:///afs/cern.ch/user/e/elaird/public/susypvt/32_test_file_41_prompt_reco/D810D5DD-374F-E011-BE08-0030487CF41E.root'),
                          ( 'START311_V2::All','/store/relval/CMSSW_4_1_2/RelValTTbar_Tauola/GEN-SIM-RECO/START311_V2_PU_E7TeV_AVE_2_BX156-v1/0028/104008AF-9846-E011-A794-0026189438EB.root')]
                         )[options.mcInfo]
process.GlobalTag.globaltag = options.GlobalTag if options.GlobalTag else defaultGT
process.source = cms.Source('PoolSource', fileNames = cms.untracked.vstring(options.files if options.files else defaultFile) )
process.maxEvents.input = options.maxEvents


if not options.patify:
    print "WARNING: selection (slimming) not applied for options patify(False)."
else:
    jetAlgoList = ['AK7Calo','AK5PF','AK7PF']
    from PhysicsTools.Configuration.SUSY_pattuple_cff import addDefaultSUSYPAT
    addDefaultSUSYPAT(process, mcInfo = options.mcInfo, HLTMenu = 'HLT', jetMetCorrections = options.jetCorrections, theJetNames = jetAlgoList)
    for algo in ['']+jetAlgoList :
        setattr( getattr( process, 'patJetGenJetMatch'+algo), 'maxDeltaR', cms.double(0.5) )
    process.susyPat = cms.Path(process.susyPatDefaultSequence)
    schedule.append(process.susyPat)

    from SUSYBSMAnalysis.SusyCAF.SusyCAF_Selection.default_cff import insertSelection
    insertSelection(process)

    if options.secondaryOutput == ".root" and hasattr(process,"out"): # remove outpath 
        del process.out
        del process.outpath
    else :
        process.out.fileName = options.secondaryOutput
        process.out.splitLevel = cms.untracked.int32(99)  # Turn on split level (smaller files?)
        process.out.overrideInputFileSplitLevels = cms.untracked.bool(True)
        process.out.dropMetaData = cms.untracked.string('DROPPED')   # Get rid of metadata related to dropped collections
        
        from PhysicsTools.Configuration.SUSY_pattuple_cff import getSUSY_pattuple_outputCommands
        SUSY_pattuple_outputCommands = getSUSY_pattuple_outputCommands( process )
        process.out.outputCommands = cms.untracked.vstring('drop *', *SUSY_pattuple_outputCommands )
        process.out.outputCommands.append('keep *_HBHENoiseFilterResultProducer_*_*')


import SUSYBSMAnalysis.SusyCAF.SusyCAF_ProcessAdjustments_cfi as adjust
adjust.loadAndConfigureHcalSeverityLevelProducer(process, options.mcInfo)
if options.hbheNoiseFilter : adjust.addHbheNoiseFilterResult(process, schedule)

process.lumiPath = cms.Path(process.lumiTree)
schedule.append(process.lumiPath)

process.p = cms.Path( ( process.nCommon +
                        ( process.nReco if not options.patify else \
                          ( process.nPat + ( process.nPatJetMatched if options.mcInfo else process.nPatJet )))) +
                       ( process.susycafalltracks if options.AllTracks else process.nEmpty ) +
                       ( process.nGen if options.mcInfo else process.nData ) 
                       * process.susycafReducer
                       * process.susyTree )
schedule.append(process.p)

# write this config as a single file
file = open('SusyCAF_Tree_cfg.py','w')
file.write(str(process.dumpPython()))
file.close()
