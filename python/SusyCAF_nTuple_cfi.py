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


jettypes = ['ak5calo', 'ak5pf', 'ak5jpt', 'ak5pf2pat', 'ic5calo', 'ak7calo', 'ak7pf', 'ak7jpt','ak7pf2pat'][:1]
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
                                                   'beamspot','track', 'vertex','beamhalosummary', 'logerror','calotowers']) )

nAllTrack = cms.Sequence( susycafalltracks) # optional

nPat = cms.Sequence( evalSequence('susycafmet%s', ['AK5','AK5TypeII','PF','TC']) + 
                     evalSequence('susycaf%s',  ['electron','muon','tau','photon']) +
                     evalSequence('susycafpf%s',['electron','muon','tau']) )

nPatJet =  cms.Sequence(evalSequence('susycaf%sjet', jettypes))              # without jen matching
nPatJetMatched = cms.Sequence(evalSequence('susycaf%sjetMatched', jettypes)) # with jen matching

def nRecoMet() : return susycafmet + susycafmetnohf 
def nRecoFlag() : return ( evalSequence('susycaf%sdeadchannels', ['ecal','hcal']) +
                           evalSequence('susycaf%srechit', [ 'hbhe', 'hf', 'eb', 'ee' ]) +
                           evalSequence('susycafpfrechitcluster%s', ['ecal','hcal','hfem','hfhad','ps']) +
                           evalSequence('susycafpfrechit%s',        ['ecal','hcal','hfem','hfhad','ps']) )
                          
nRecoPat = cms.Sequence( nRecoMet() + nRecoFlag()) #stuff needs reco content but runs in pat jobs with pat-on-the-fly
nReco = cms.Sequence( nRecoPat + susycafPFtau +
                      evalSequence('susycaf%sjetreco', jettypes) +
                      evalSequence('susycaf%sreco', ['photon','electron','muon']) )

nGen = cms.Sequence( susycafgen + evalSequence('susycafgenMet%s', ['Calo','CaloAndNonPrompt','True']))
nData = cms.Sequence( susycafdqmflags + susycafdcsbits )
