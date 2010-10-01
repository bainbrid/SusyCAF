import FWCore.ParameterSet.Config as cms

def addHbheNoiseFilterResult(process, schedule) :
    process.load('CommonTools/RecoAlgos/HBHENoiseFilterResultProducer_cfi')
    process.hbheflag = cms.Path(process.HBHENoiseFilterResultProducer)
    schedule.append(process.hbheflag)

def loadAndConfigureHcalSeverityLevelProducer(process, mcInfo) :
    process.load("RecoLocalCalo.HcalRecAlgos.hcalRecAlgoESProd_cfi")
    if not mcInfo :
        process.hcalRecAlgos.SeverityLevels[3].RecHitFlags.remove("HFDigiTime")
        process.hcalRecAlgos.SeverityLevels[4].RecHitFlags.append("HFDigiTime")

def addEcalUnpacking(process, mcInfo) :
    if mcInfo :
        process.load("Configuration.StandardSequences.RawToDigi_cff")
    else :
        process.load("Configuration.StandardSequences.RawToDigi_Data_cff")        

    process.load("SimCalorimetry.EcalTrigPrimProducers.ecalTriggerPrimitiveDigis_readDBOffline_cff")
    process.ecalTriggerPrimitiveDigis = process.simEcalTriggerPrimitiveDigis.clone(InstanceEB = 'ebDigis',
                                                                                   InstanceEE = 'eeDigis',
                                                                                   Label = 'ecalDigis'
                                                                                   )

def addTypeIIMet(process) :
    # Add reco::MET with Type II correction 
    from PhysicsTools.PatAlgos.recoLayer0.jetMETCorrections_cff import metJESCorAK5CaloJet
    process.metJESCorAK5CaloJetTypeII = metJESCorAK5CaloJet.clone()
    process.metJESCorAK5CaloJetTypeII.useTypeII = True
    process.metJESCorAK5CaloJetTypeII.hasMuonsCorr = False
    # Add muon corrections for above II reco::MET
    process.metJESCorAK5CaloJetMuonsTypeII = process.metJESCorAK5CaloJetMuons.clone(
        uncorMETInputTag = cms.InputTag('metJESCorAK5CaloJetTypeII')
        )
    # Add to recoLayer0 sequence
    process.patMETCorrections.replace(
        process.metJESCorAK5CaloJet,
        (process.metJESCorAK5CaloJetTypeII*
         process.metJESCorAK5CaloJetMuonsTypeII)+
        process.metJESCorAK5CaloJet
        )
    # Add pat::MET with Type II correction
    process.patMETsAK5CaloTypeII = process.patMETs.clone(
        metSource = cms.InputTag("metJESCorAK5CaloJetMuonsTypeII")
        )
    # Add to producersLayer1 sequence
    process.makePatMETs.replace(
        process.patMETs,
        process.patMETs+
        process.patMETsAK5CaloTypeII
        )
