import FWCore.ParameterSet.Config as cms
import SusyCAF_Drop_cfi

susycafModules = ['Event','Track', 'Triggers','L1Triggers',
                  'Gen','MET','Jet','Photon','Muon','Electron',
                  'BeamSpot','BeamHaloSummary','LogError','Vertex',
                  'HcalRecHit','EcalRecHit','PFRecHit','HcalDeadChannels','EcalDeadChannels',
                  'CaloTowers','PFTau','AllTracks','DQMFlags','DCSBits','LumiTreeMaker'
                  ] + ['HcalNoise%s'%s for s in ['Filter','RBX','Summary']]
for name in susycafModules :
    exec('from SUSYBSMAnalysis.SusyCAF.SusyCAF_%s_cfi import *'%name)


jettypes = ['ak5calo', 'ak5pf', 'ak5pf2pat', 'ak7calo', 'ak7pf','ak7pf2pat']
nEmpty = cms.Sequence()
def evalSequence(pattern, names) :
    return sum([eval(pattern%name) for name in names],nEmpty)
########################

susyTree = cms.EDAnalyzer("SusyTree",
                          outputCommands = cms.untracked.vstring(
    'drop *',
    'keep *_susycaf*_*_*',
    'keep double_susyScan*_*_*') + (
    ["drop %s"%s for s in (SusyCAF_Drop_cfi.reduce()+
                           SusyCAF_Drop_cfi.drop())]) )

susycafReducer = cms.EDProducer("ProductReducer",
                                selectionCommands = cms.untracked.vstring('drop *') +
                                ["keep %s"%s for s in SusyCAF_Drop_cfi.reduce()])

nCommon = cms.Sequence( evalSequence('susycafhcalnoise%s', ['rbx','summary','filter']) +
                        evalSequence('susycaf%s', ['event','L1triggers', 'triggers',
                                                   'beamspot','track', 'vertex','beamhalosummary', 'logerror','calotowers']) +
                        susycafmet + susycafmetnohf +
                        evalSequence('susycaf%sdeadchannels', ['ecal','hcal']) +
                        evalSequence('susycaf%srechit', [ 'hbhe', 'hf', 'eb', 'ee' ]) +
                        evalSequence('susycafpfrechitcluster%s', ['ecal','hcal','hfem','hfhad','ps']) +
                        evalSequence('susycafpfrechit%s',        ['ecal','hcal','hfem','hfhad','ps']) )

nPatJet =  cms.Sequence(evalSequence('susycaf%sjet', jettypes))              # without gen matching
nPatJetMatched = cms.Sequence(evalSequence('susycaf%sjetMatched', jettypes)) # with gen matching
nPat = cms.Sequence( evalSequence('susycafmet%s', ['AK5','AK5TypeII','PF','TC']) + 
                     evalSequence('susycaf%s',  ['electron','muon','tau','photon']) +
                     evalSequence('susycafpf%s',['electron','muon','tau']) )

nReco = cms.Sequence( susycafPFtau +
                      evalSequence('susycaf%sjetreco', filter(lambda x:"pf2pat" not in x, jettypes)) +
                      evalSequence('susycaf%sreco', ['photon','electron','muon']) )

nGen = cms.Sequence( susycafgen + evalSequence('susycafgenMet%s', ['Calo','CaloAndNonPrompt','True']))
nData = cms.Sequence( susycafdqmflags + susycafdcsbits )
