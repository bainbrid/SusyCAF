#
#  SUSY-PAT configuration fragment
#
#  PAT configuration for the SUSY group - 33X series
#  More information here:
#  https://twiki.cern.ch/twiki/bin/view/CMS/SusyPatLayer1DefV7


import FWCore.ParameterSet.Config as cms

def addDefaultSUSYPAT(process):
    loadPAT(process)
    addJetMET(process)
    loadPATTriggers(process)

    #-- Remove MC dependence ------------------------------------------------------
    from PhysicsTools.PatAlgos.tools.coreTools import removeMCMatching
    removeMCMatching(process, 'All')

    # Full path
    process.seqSUSYDefaultSequence = cms.Sequence( process.jpt * process.addTrackJets
                                                   *process.patDefaultSequence
                                                   * process.patTrigger*process.patTriggerEvent )

def loadPAT(process):
    #-- Missing ak5GenJets in 3.3.2 samples ---------------------------------------
    #from PhysicsTools.PatAlgos.tools.cmsswVersionTools import run33xOnReRecoMC
#    run33xOn31xMC(process, "ak5GenJets")
    #run33xOnReRecoMC( process, "ak5GenJets" )
    
    #-- PAT standard config -------------------------------------------------------
    process.load("PhysicsTools.PatAlgos.patSequences_cff")

    #-- Changes for electron and photon ID ----------------------------------------
    # Turn off photon-electron cleaning (i.e., flag only)
    process.cleanLayer1Photons.checkOverlaps.electrons.requireNoOverlaps = False

    # Remove embedding of superClusters, will keep entire superCluster collection
    process.allLayer1Electrons.embedSuperCluster = False
    process.allLayer1Photons.embedSuperCluster   = False
    
    #-- Tuning of Monte Carlo matching --------------------------------------------
    # Also match with leptons of opposite charge
    process.electronMatch.checkCharge = False
    process.muonMatch.checkCharge     = False
    process.tauMatch.checkCharge      = False

    #-- Jet corrections -----------------------------------------------------------
    process.jetCorrFactors.corrSample = 'Summer09_7TeV' ## 'Summer09' for 10TeV
    
def loadPATTriggers(process):
    #-- Trigger matching ----------------------------------------------------------
    from PhysicsTools.PatAlgos.tools.trigTools import switchOnTrigger
    switchOnTrigger( process )
    process.patTriggerSequence.remove( process.patTriggerMatcher )
    process.patTriggerEvent.patTriggerMatches  = ()
    # Fix for secondary datasets: skimming based on 8E29 menu...
    #process.patTrigger.processName = "HLT8E29"
    #process.patTriggerEvent.processName = "HLT8E29"

def addJetMET(process):
    #-- Extra Jet/MET collections -------------------------------------------------
    # Add a few jet collections...
    from PhysicsTools.PatAlgos.tools.jetTools import addJetCollection
    
    #-- Jet plus tracks -----------------------------------------------------------
    process.load("PhysicsTools.PatAlgos.recoLayer0.jetPlusTrack_cff")
    process.jpt = cms.Sequence( process.jptCaloJets )
    #process.load('JetMETCorrections.Configuration.JetPlusTrackCorrections_cff')
	
    # CaloJets
    addJetCollection(process, cms.InputTag('iterativeCone5CaloJets'),
                     'IC5',
                     doJTA            = True,
                     doBTagging       = True,
                     jetCorrLabel     = ('IC5','Calo'),
                     doType1MET       = True,
                     doL1Cleaning     = True,
                     doL1Counters     = True,
                     jetIdLabel       = "ic5",
                     genJetCollection = cms.InputTag("iterativeCone5GenJets")
                     )
    addJetCollection(process,cms.InputTag('sisCone5CaloJets'),
                     'SC5',
                     doJTA        = True,
                     doBTagging   = True,
                     jetCorrLabel = ('SC5','Calo'),
                     doType1MET   = True,
                     doL1Cleaning = True,
                     doL1Counters = True,
                     jetIdLabel   = "sc5",
                     genJetCollection=cms.InputTag("sisCone5GenJets")
                     )
    # PF jets
    addJetCollection(process,cms.InputTag('ak5PFJets'),
                     'AK5PF',
                     doJTA        = True,
                     doBTagging   = True,
                     jetCorrLabel = None,
                     doType1MET   = True,
                     doL1Cleaning = True,
                     doL1Counters = True,
                     genJetCollection=cms.InputTag("ak5GenJets")
                     )
    addJetCollection(process,cms.InputTag('sisCone5PFJets'),
                     'SC5PF',
                     doJTA        = True,
                     doBTagging   = True,
                     jetCorrLabel = None,
                     doType1MET   = True,
                     doL1Cleaning = True,
                     doL1Counters = True,
                     genJetCollection=cms.InputTag("sisCone5GenJets")
                     )
    
    # JPT jets
    addJetCollection(process,cms.InputTag('JetPlusTrackZSPCorJetAntiKt5'),
                     'AK5JPT',
                     doJTA        = True,
                     doBTagging   = True,
                     jetCorrLabel = None,
                     doType1MET   = False,
                     doL1Cleaning = True,
                     doL1Counters = True,
                     genJetCollection = cms.InputTag("ak5GenJets")
                     )
    #Not needed in 33X since in RECO
    # Add latest HcalNoiseSummary
    #process.load("RecoMET.METProducers.hcalnoiseinfoproducer_cfi")
    #process.hcalnoise.refillRefVectors = True
    #process.hcalnoise.hcalNoiseRBXCollName = "hcalnoise" # This has changed in 33X
	
    #-- Track Jets ----------------------------------------------------------------
    # Select tracks for track jets
    process.load("PhysicsTools.RecoAlgos.TrackWithVertexSelector_cfi")
    process.trackWithVertexSelector.src              = cms.InputTag("generalTracks")
    process.trackWithVertexSelector.ptMax            = cms.double(500.0) 
    process.trackWithVertexSelector.normalizedChi2   = cms.double(100.0)
    process.trackWithVertexSelector.vertexTag        = cms.InputTag("offlinePrimaryVertices")
    process.trackWithVertexSelector.copyTrajectories = cms.untracked.bool(False)
    process.trackWithVertexSelector.vtxFallback      = cms.bool(False)
    process.trackWithVertexSelector.useVtx           = cms.bool(False)
    process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
    process.tracksForJets = cms.EDProducer("ConcreteChargedCandidateProducer",
                                           src = cms.InputTag("trackWithVertexSelector"),
                                           particleType = cms.string('pi+')
                                           )
	
    #add jet collections
    process.load('RecoJets.JetProducers.ak5TrackJets_cfi')
    process.addTrackJets = cms.Sequence(  process.trackWithVertexSelector
                                          * process.tracksForJets
                                          * process.ak5TrackJets )
    addJetCollection(process,cms.InputTag('ak5TrackJets'),
                     'AK5Track',
                     doJTA        = False,
                     doBTagging   = True,
                     jetCorrLabel = None,
                     doType1MET   = False,
                     doL1Cleaning = True,
                     doL1Counters = True,
                     genJetCollection = cms.InputTag("ak5GenJets")
                     )
    
    #-- Tune contents of jet collections  -----------------------------------------
    for jetName in ( '', 'IC5', 'SC5' , 'AK5PF', 'SC5PF', 'AK5JPT', 'AK5Track'):# , 'SC5JPT', 'SC5Track' ):
        module = getattr(process,'allLayer1Jets'+jetName)
        module.addTagInfos = False    # Remove tag infos
        module.addJetID    = False     # Do not add JetID variables since they are in AOD
        module.embedGenJetMatch = False # Only keep reference, since we anyway keep the genJet collections
   	## remove mc extra configs for jets
        module.addGenPartonMatch   = False
        module.embedGenPartonMatch = False
        module.genPartonMatch      = ''
        module.addGenJetMatch      = False
        module.genJetMatch         = ''
        module.getJetMCFlavour     = False
        module.JetPartonMapSource  = ''       
    process.patDefaultSequence.remove(process.jetPartonMatch)
    process.patDefaultSequence.remove(process.jetGenJetMatch)
    process.patDefaultSequence.remove(process.jetFlavourId)
    process.patDefaultSequence.remove(process.jetPartonMatchIC5)
    process.patDefaultSequence.remove(process.jetGenJetMatchIC5)
    process.patDefaultSequence.remove(process.jetPartonMatchSC5)
    process.patDefaultSequence.remove(process.jetGenJetMatchSC5)
    process.patDefaultSequence.remove(process.jetPartonMatchAK5PF)
    process.patDefaultSequence.remove(process.jetGenJetMatchAK5PF)
    process.patDefaultSequence.remove(process.jetPartonMatchSC5PF)
    process.patDefaultSequence.remove(process.jetGenJetMatchSC5PF)
    process.patDefaultSequence.remove(process.jetPartonMatchAK5JPT)
    process.patDefaultSequence.remove(process.jetGenJetMatchAK5JPT)
    process.patDefaultSequence.remove(process.jetPartonMatchAK5Track)
    process.patDefaultSequence.remove(process.jetGenJetMatchAK5Track)
        

    # Add tcMET and PFMET
    from PhysicsTools.PatAlgos.tools.metTools import addTcMET, addPfMET
    addTcMET(process,'TC')
    addPfMET(process,'PF')
   
    ## remove mc extra configs for met
    for MetName in ( '', 'IC5', 'SC5' , 'PF', 'TC'):# , 'SC5JPT', 'SC5Track' ):
        module = getattr(process, 'layer1METs'+MetName)        
        module.addGenMET           = False
        module.genMETSource        = ''

    # Rename default jet collection for uniformity
    process.cleanLayer1JetsAK5 = process.cleanLayer1Jets
    process.layer1METsAK5      = process.layer1METs

    # Modify subsequent modules
    process.cleanLayer1Hemispheres.patJets = process.cleanLayer1JetsAK5.label()
    process.countLayer1Jets.src            = process.cleanLayer1JetsAK5.label()

    # Modify counters' input
    process.allLayer1Summary.candidates.remove(cms.InputTag('layer1METs'))
    process.allLayer1Summary.candidates.append(cms.InputTag('layer1METsAK5'))
    process.cleanLayer1Summary.candidates.remove(cms.InputTag('cleanLayer1Jets'))
    process.cleanLayer1Summary.candidates.append(cms.InputTag('cleanLayer1JetsAK5'))
    # Add new jet collections to counters (MET done automatically)
    for jets in ( 'IC5', 'SC5', 'AK5PF', 'SC5PF', 'AK5JPT', 'AK5Track'):#, 'SC5JPT', 'SC5Track' ):
        process.allLayer1Summary.candidates.append(cms.InputTag('allLayer1Jets'+jets))
        process.selectedLayer1Summary.candidates.append(cms.InputTag('selectedLayer1Jets'+jets))
        process.cleanLayer1Summary.candidates.append(cms.InputTag('cleanLayer1Jets'+jets))
	

def getSUSY_pattuple_outputCommands( process ):
    return [ # PAT Objects
        'keep *_cleanLayer1Photons_*_*',
        'keep *_cleanLayer1Electrons_*_*',
        'keep *_cleanLayer1Muons_*_*',
        'keep *_cleanLayer1Taus_*_*',
        'keep *_cleanLayer1Jets*_*_*',       # All Jets
        'keep *_layer1METs*_*_*',            # All METs
        'keep *_cleanLayer1Hemispheres_*_*',
        'keep *_cleanLayer1PFParticles_*_*',
        # Generator information
        'keep GenEventInfoProduct_generator_*_*',
        'keep GenRunInfoProduct_generator_*_*',
        # Generator particles/jets/MET
        'keep recoGenParticles_genParticles_*_*',
        'keep recoGenJets_iterativeCone5GenJets_*_*',
        'keep recoGenJets_sisCone5GenJets_*_*',
        'keep recoGenJets_ak5GenJets_*_*',
        'keep recoGenMETs_*_*_*',
        # Trigger information
        'keep edmTriggerResults_TriggerResults_*_HLT',
        'keep *_hltTriggerSummaryAOD_*_*',
        'keep L1GlobalTriggerObjectMapRecord_*_*_*',
        'keep L1GlobalTriggerReadoutRecord_*_*_*',
        # Others
        'keep *_muon*METValueMapProducer_*_*',   # Muon corrections to MET
        'keep *_offlinePrimaryVertices_*_*',
        'keep *_offlineBeamSpot_*_*',
        'keep *_towerMaker_*_*',                 # Keep CaloTowers for cross-cleaning
        'keep recoTracks_generalTracks_*_*',
        'keep recoSuperClusters_corrected*_*_*',
        'keep recoConversions_conversions_*_*',
        'keep recoTracks_*onversions_*_*',
        'keep HcalNoiseSummary_*_*_'+process.name_(), # Only keep the one we create
        'keep recoPFCandidates_particleFlow_*_*'
        ] 


