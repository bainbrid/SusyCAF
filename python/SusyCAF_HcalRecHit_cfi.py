import FWCore.ParameterSet.Config as cms

susycafhbherechit = cms.EDProducer("SusyCAF_HBHERecHitsSorted",
                                   InputTag = cms.InputTag('hbhereco'),
                                   Prefix = cms.string('rechit'),
                                   Suffix = cms.string('Hbhe'),
                                   SeverityLevelCut = cms.int32(50),
                                   ProduceExtraVariables = cms.bool(False),
                                   SingleRbxThresholds = cms.vdouble(10.0), #GeV
                                   SingleRmThresholds = cms.vdouble(5.0), #GeV
                                   SingleChannelThreshold = cms.double(1.0), #GeV
                                   )

susycafhfrechit = cms.EDProducer("SusyCAF_HFRecHitsSorted",
                                 InputTag = cms.InputTag('hfreco'),
                                 Prefix = cms.string('rechit'),
                                 Suffix = cms.string('Hf'),
                                 SeverityLevelCut = cms.int32(50),
                                 ProduceExtraVariables = cms.bool(False),
                                 SingleRbxThresholds = cms.vdouble(10.0), #GeV
                                 SingleRmThresholds = cms.vdouble(5.0), #GeV
                                 SingleChannelThreshold = cms.double(1.0), #GeV
                                 )

susycafhorechit = cms.EDProducer("SusyCAF_HORecHitsSorted",
                                 InputTag = cms.InputTag('horeco'),
                                 Prefix = cms.string('rechit'),
                                 Suffix = cms.string('Ho'),
                                 SeverityLevelCut = cms.int32(50),
                                 ProduceExtraVariables = cms.bool(False),
                                 SingleRbxThresholds = cms.vdouble(10.0), #GeV
                                 SingleRmThresholds = cms.vdouble(5.0), #GeV
                                 SingleChannelThreshold = cms.double(1.0), #GeV
                                 )

susycafhfrechitreflagged = susycafhfrechit.clone( InputTag = 'hfrecoReflagged' )
