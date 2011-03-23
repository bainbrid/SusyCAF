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

def susycafCommon(isData) :
    return ( evalSequence('susycafhcalnoise%s', ['rbx','summary','filter']) +
             evalSequence('susycaf%s', ['event','L1triggers', 'triggers',
                                        'beamspot','track', 'vertex','beamhalosummary', 'logerror','calotowers']) +
             susycafmet + susycafmetnohf +
             evalSequence('susycaf%sdeadchannels', ['ecal','hcal']) +
             evalSequence('susycaf%srechit', [ 'hbhe', 'hf', 'eb', 'ee' ]) +
             evalSequence('susycafpfrechitcluster%s', ['ecal','hcal','hfem','hfhad','ps']) +
             evalSequence('susycafpfrechit%s',        ['ecal','hcal','hfem','hfhad','ps']) +
             
             [ (susycafgen + evalSequence('susycafgenMet%s', ['Calo','CaloAndNonPrompt','True'])), # Gen
               (susycafdqmflags + susycafdcsbits) # Data
               ][isData]
             )

def susycafPatJet(isData, jetTypes) :
    return ( evalSequence('susycaf%sjet'+['Matched',''][isData], jetTypes))

def susycafPat() :
    return ( evalSequence('susycafmet%s', ['AK5','AK5TypeII','PF','TypeIPF','TC']) + 
             evalSequence('susycaf%s',  ['electron','muon','tau','photon']) +
             evalSequence('susycafpf%s',['electron','muon','tau']) )

def susycafReco(jetTypes) :
    return ( susycafPFtau +
             evalSequence('susycaf%sjetreco', filter(lambda x:"pf2pat" not in x, jetTypes)) +
             evalSequence('susycaf%sreco', ['photon','electron','muon']) )
