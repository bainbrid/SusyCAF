import FWCore.ParameterSet.Config as cms

########################################################
############### MET CLEANING STARTS HERE ###############
########################################################

def addNoiseCleaning(process,schedule,mcInfo) :

    process.load("Configuration.StandardSequences.Reconstruction_cff")
    
    ##@@ Below are required, but already loaded in PhysicsTools/PatAlgos/python/patTemplate_cff
    #process.load("Configuration.StandardSequences.Geometry_cff")
    #process.load("Configuration.StandardSequences.MagneticField_cff")

    #is it MC or DATA
    isMC = mcInfo
    useHBHEcleaning = True
    useHBHEfilter = False
    
    HFPMTcleaningversion = 4   # version 1 = (loose), version 2 = (medium), version 3 = (tight)
    # VERSION 4 is the currently recommended version, as of 28 May 2010.
    
    if useHBHEfilter == True:
        process.load('CommonTools/RecoAlgos/HBHENoiseFilter_cfi')
        process.p = cms.Path(process.HBHENoiseFilter)
    
    # New SeverityLevelComputer that forces RecHits with UserDefinedBit0 set to be excluded from new rechit collection
    import JetMETAnalysis.HcalReflagging.RemoveAddSevLevel as RemoveAddSevLevel
    process.hcalRecAlgos=RemoveAddSevLevel.RemoveFlag(process.hcalRecAlgos,"HFLongShort")

    # UserDefinedBit0 is used by both the HF and HBHE reflaggers
    process.hcalRecAlgos=RemoveAddSevLevel.AddFlag(process.hcalRecAlgos,"UserDefinedBit0",10)

    # HF RecHit reflagger
    process.load("JetMETAnalysis/HcalReflagging/HFrechitreflaggerJETMET_cff")
    if HFPMTcleaningversion==1:
        process.hfrecoReflagged = process.HFrechitreflaggerJETMETv1.clone()
    elif HFPMTcleaningversion==2:
        process.hfrecoReflagged = process.HFrechitreflaggerJETMETv2.clone()
    elif HFPMTcleaningversion==3:
        process.hfrecoReflagged = process.HFrechitreflaggerJETMETv3.clone()
    elif HFPMTcleaningversion==4:
        if (isMC==False):
            process.hfrecoReflagged = process.HFrechitreflaggerJETMETv4.clone()
        else:
            process.hfrecoReflagged = process.HFrechitreflaggerJETMETv2.clone()
    elif HFPMTcleaningversion==5:     
        if (isMC==False):             
            process.hfrecoReflagged = process.HFrechitreflaggerJETMETv5.clone()
        else:
            process.hfrecoReflagged = process.HFrechitreflaggerJETMETv3.clone()
        
    # HBHE RecHit reflagger
    process.load("JetMETAnalysis/HcalReflagging/hbherechitreflaggerJETMET_cfi")
    process.hbherecoReflagged = process.hbherechitreflaggerJETMET.clone()
    process.hbherecoReflagged.debug=0

    # Use the reflagged HF RecHits to make the CaloTowers
    process.towerMaker.hfInput = "hfrecoReflagged"
    process.towerMakerWithHO.hfInput = "hfrecoReflagged"

    # Path and EndPath definitions
    
    if (useHBHEcleaning==False):
        process.reflagging_path = cms.Path(process.hfrecoReflagged)
    else:
        process.reflagging_path = cms.Path(process.hfrecoReflagged+process.hbherecoReflagged)
        # Need to specify that new HBHE collection should be fed to calotower maker
        process.towerMaker.hbheInput = "hbherecoReflagged"
        process.towerMakerWithHO.hbheInput = "hbherecoReflagged"

    # Instead of rejecting the event, add a flag indicating the HBHE noise 
    process.load('CommonTools/RecoAlgos/HBHENoiseFilterResultProducer_cfi')
    process.hbheflag = cms.Path(process.HBHENoiseFilterResultProducer)

    # Two lines below no longer needed!
    #process.metreco.remove(process.muonMETValueMapProducer) ##@@ this doesn't work with this recipe!
    #process.metreco.remove(process.corMetGlobalMuons) ##@@ this doesn't work with this recipe!

    process.rereco_step1 = cms.Path(
        process.caloTowersRec*
        (process.recoJets*
         process.recoJetIds+
         process.recoTrackJets)*
        process.recoJetAssociations*
        process.btagging*
        process.metreco
        ) 

    process.rereco_step2 = cms.Path(
    process.recoJetAssociations*
    process.btagging
    )

    schedule.append(process.reflagging_path)
    schedule.append(process.hbheflag)
    schedule.append(process.rereco_step1)
    schedule.append(process.rereco_step2)
    
########################################################
############### MET CLEANING STOPS HERE ################
########################################################

def addHbheNoiseFilterResult(process,schedule) :
    # Instead of rejecting the event, add a flag indicating the HBHE noise
    process.load('CommonTools/RecoAlgos/HBHENoiseFilterResultProducer_cfi')
    process.hbheflag = cms.Path(process.HBHENoiseFilterResultProducer)
    schedule.append(process.hbheflag)
