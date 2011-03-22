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
