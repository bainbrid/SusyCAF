import FWCore.ParameterSet.Config as cms

susycafhbherechit = cms.EDProducer("SusyCAF_HBHERecHitsSorted",
                                   InputTag = cms.InputTag('hbhereco'),
                                   Prefix = cms.string('rechitCalo'),
                                   Suffix = cms.string('Hbhe'),
                                   SeverityLevelCut = cms.int32(11),
                                   ProduceExtraVariables = cms.bool(False),
                                   SingleRbxThresholds = cms.vdouble(10.0), #GeV
                                   SingleRmThresholds = cms.vdouble(5.0), #GeV
                                   SingleChannelThreshold = cms.double(1.0), #GeV
                                   )

susycafhfrechit = cms.EDProducer("SusyCAF_HFRecHitsSorted",
                                 InputTag = cms.InputTag('hfreco'),
                                 Prefix = cms.string('rechitCalo'),
                                 Suffix = cms.string('Hf'),
                                 SeverityLevelCut = cms.int32(11),
                                 ProduceExtraVariables = cms.bool(False),
                                 SingleRbxThresholds = cms.vdouble(10.0), #GeV
                                 SingleRmThresholds = cms.vdouble(5.0), #GeV
                                 SingleChannelThreshold = cms.double(1.0), #GeV
                                 )

susycafhorechit = cms.EDProducer("SusyCAF_HORecHitsSorted",
                                 InputTag = cms.InputTag('horeco'),
                                 Prefix = cms.string('rechitCalo'),
                                 Suffix = cms.string('Ho'),
                                 SeverityLevelCut = cms.int32(11),
                                 ProduceExtraVariables = cms.bool(False),
                                 SingleRbxThresholds = cms.vdouble(10.0), #GeV
                                 SingleRmThresholds = cms.vdouble(5.0), #GeV
                                 SingleChannelThreshold = cms.double(1.0), #GeV
                                 )

susycafhfrechitreflagged = susycafhfrechit.clone( InputTag = 'hfrecoReflagged', Suffix='HfReFlagged', SeverityLevelCut=11 )

def loadAndConfigureHcalSeverityLevelProducer(process,mcInfo) :
    process.load("RecoLocalCalo.HcalRecAlgos.hcalRecAlgoESProd_cfi")
    if not mcInfo :
        process.hcalRecAlgos.SeverityLevels[3].RecHitFlags.remove("HFDigiTime")
        process.hcalRecAlgos.SeverityLevels[4].RecHitFlags.append("HFDigiTime")

def makeAndScheduleHcalReFlaggingPath(process,schedule) :
    process.load("JetMETAnalysis/HcalReflagging/HFrechitreflaggerJETMET_cff")
    process.hfrecoReflagged = process.HFrechitreflaggerJETMETv2.clone()
    process.hcalReflaggingPath = cms.Path(process.hfrecoReflagged)
    schedule.append(process.hcalReflaggingPath)
