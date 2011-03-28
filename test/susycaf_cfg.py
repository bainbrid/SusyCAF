import FWCore.ParameterSet.Config as cms

from PhysicsTools.PatAlgos.patTemplate_cfg import process
process.setName_("SUSYCAF")
from SUSYBSMAnalysis.SusyCAF.SusyCAF_options_cff import options
options = options()

process.maxEvents.input = options.maxEvents
process.GlobalTag.globaltag = options.GlobalTag
process.source = cms.Source('PoolSource', fileNames = cms.untracked.vstring(options.files) )
process.add_( cms.Service( "TFileService", fileName = cms.string( options.output ), closeFileFast = cms.untracked.bool(True) ) )

from SUSYBSMAnalysis.SusyCAF.SusyCAF_nTuple_cfi import SusyCAF
susycaf = SusyCAF(process,options)
process.nCommon = cms.Sequence(susycaf.common())
process.nPatJet = cms.Sequence(susycaf.patJet())

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
                                [ susycaf.reco(),  susycaf.pat() + process.nPatJet][options.patify] +
                                susycaf.allTracks() )
                              * susycaf.reducer()
                              * susycaf.tree() )

schedule = cms.Schedule( process.p_susyPat,
                         process.p_hbheFlag,
                         process.p_lumi,
                         process.p_susyCAF )

# write this config as a single file
file = open(options.output.replace('.root','_cfg.py'),'w')
file.write(str(process.dumpPython()))
file.close()
