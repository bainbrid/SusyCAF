from PhysicsTools.PatAlgos.patTemplate_cfg import process
process.setName_("SUSYCAF")
from SUSYBSMAnalysis.SusyCAF.SusyCAF_options_cff import options
options = options()

process.maxEvents.input = options.maxEvents
process.GlobalTag.globaltag = options.GlobalTag
process.source = cms.Source('PoolSource', fileNames = cms.untracked.vstring(options.files) )
process.add_( cms.Service( "TFileService", fileName = cms.string( options.output ), closeFileFast = cms.untracked.bool(True) ) )

process.load('SUSYBSMAnalysis.SusyCAF.SusyCAF_nTuple_cfi')
process.susycaftriggers.SourceName  = options.SourceName
from SUSYBSMAnalysis.SusyCAF.SusyCAF_nTuple_cfi import susycafCommon,susycafReco,susycafPat,susycafPatJet
process.nCommon = cms.Sequence(susycafCommon(options.isData))
process.nPatJet = cms.Sequence(susycafPatJet(options.isData,options.jetCollections))

# This is nasty
if options.patify : 
    from SUSYBSMAnalysis.SusyCAF.SusyCAF_Selection.default_cff import insertSelection
    insertSelection(process)
# End nasty

import SUSYBSMAnalysis.SusyCAF.SusyCAF_ProcessAdjustments_cfi as adjust
adjust.messageLogger(process,options.quiet)
adjust.loadAndConfigureHcalSeverityLevelProducer(process, options.isData)

process.p_susyPat  = adjust.susyPat(process,options)
process.p_hbheFlag = adjust.addHbheNoiseFilterResult(process)
process.p_lumi     = adjust.lumiTree(process)
process.p_susyCAF = cms.Path( ( process.nCommon +
                                [ susycafReco(options.jetCollections),
                                  susycafPat() + process.nPatJet][options.patify] +
                                [process.nEmpty,process.susycafalltracks][options.AllTracks] )
                              * process.susycafReducer
                              * process.susyTree )

schedule = cms.Schedule( process.p_susyPat,
                         process.p_hbheFlag,
                         process.p_lumi,
                         process.p_susyCAF )

# write this config as a single file
file = open(options.output.replace('.root','_cfg.py'),'w')
file.write(str(process.dumpPython()))
file.close()
