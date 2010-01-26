# Starting with a skeleton process which gets imported with the following line
from PhysicsTools.PatAlgos.patTemplate_cfg import *
process.setName_("SUSYCAF")

class options:
    outputSUSYPAT = False
    GlobalTag = None #set later on while loading the dataset
    mcInfo = True
    silentMessageLogger = False
    onTheFlySUSYPAT = False
    fromRECO = True

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
    fileName = cms.string( 'exampleTree_nTuple.root' ),
    closeFileFast = cms.untracked.bool(True) ) 
)

#-- Input Source --------------------------------------------------------------
process.source = cms.Source('PoolSource', fileNames = cms.untracked.vstring() )
if options.fromRECO:
    if options.mcInfo:
        if options.GlobalTag == None: options.GlobalTag = 'MC_3XY_V14::All'
        process.source.fileNames = ['rfio://?svcclass=cmscafuser&path=/castor/cern.ch/user/n/nmohr/QCDDiJet_Pt380to470_MC_31X_V9_ReReco332.root']
        # Due to problem in production of LM samples: same event number appears multiple times
        process.source.duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
    else:
        if options.GlobalTag == None: options.GlobalTag = 'GR09_R_34X_V3::All'
        process.source.fileNames = ['/store/data/BeamCommissioning09/MinimumBias/RECO/Jan21stPreProd_336p3_v1/0007/EC38C57D-0507-DF11-82E3-0024E8768CA5.root']
else:
    if options.mcInfo:
        if options.GlobalTag == None: options.GlobalTag = 'MC_3XY_V14::All'
        process.source.fileNames = ['rfio://?svcclass=cmscafuser&path=/castor/cern.ch/user/n/nmohr/V7production/QCDDiJet_Pt380to470_SUSYPAT-V00-05-06.root']
    else:
        raise StandardError, "no PAT-ified data available yet. Perhaps try running on the fly!"

process.maxEvents.input = 100

#-- Calibration tag -----------------------------------------------------------
process.GlobalTag.globaltag = options.GlobalTag

schedule = cms.Schedule()
if options.onTheFlySUSYPAT and options.fromRECO:
    from PhysicsTools.Configuration.SUSY_pattuple_cff import addDefaultSUSYPAT, getSUSY_pattuple_outputCommands
    #Apply SUSYPAT: Parameters are: mcInfo, HLT menu, Jet energy corrections, MC version ('31x' or '31xReReco332')
    addDefaultSUSYPAT(process,options.mcInfo,'HLT','Summer09_7TeV_ReReco332','31xReReco332') 
    process.susyPat = cms.Path(process.seqSUSYDefaultSequence)
    schedule.append(process.susyPat)
    SUSY_pattuple_outputCommands = getSUSY_pattuple_outputCommands( process )

    #-- Output module configuration -----------------------------------------------
    process.out.fileName = 'exampleTree_SUSYPAT.root'       # <-- CHANGE THIS TO SUIT YOUR NEEDS
    # Custom settings
    process.out.splitLevel = cms.untracked.int32(99)  # Turn on split level (smaller files???)
    process.out.overrideInputFileSplitLevels = cms.untracked.bool(True)
    process.out.dropMetaData = cms.untracked.string('DROPPED')   # Get rid of metadata related to dropped collections

    process.out.outputCommands = cms.untracked.vstring('drop *', *SUSY_pattuple_outputCommands )
    if not options.outputSUSYPAT and hasattr(process,"out"): # remove outpath 
        del process.out
        del process.outpath

process.load('SUSYBSMAnalysis.SusyCAF.SusyCAF_nTuple_cfi')
process.p = cms.Path( (process.nTupleCommonSequence) * process.susyTree)

if options.mcInfo:
    process.p.replace( process.nTupleCommonSequence, process.nTupleCommonSequence + process.nTupleGenSequence )

if options.fromRECO and not options.onTheFlySUSYPAT:
    process.p.replace( process.nTupleCommonSequence, process.nTupleCommonSequence + process.nTupleRecoSequence )
else:
    if  options.onTheFlySUSYPAT:
        #little havyhanded: want too have met values which are not in SUSYPAT in those trees
        process.p.replace( process.nTupleCommonSequence, process.nTupleCommonSequence + process.nTupleRecoMetSequence )
    process.p.replace( process.nTupleCommonSequence, process.nTupleCommonSequence + process.nTuplePatSequence )

schedule.append(process.p)


