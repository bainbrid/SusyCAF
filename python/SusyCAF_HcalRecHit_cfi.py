import FWCore.ParameterSet.Config as cms

susycafhbherechit = cms.EDProducer("SusyCAF_HBHERecHitsSorted",
                            InputTag = cms.InputTag('hbhereco'),
                            Prefix = cms.string('rechit'),
                            Suffix = cms.string('hbhe'),
                            SingleRbxThresholds = cms.vdouble(10.0), #GeV
                            SingleRmThresholds = cms.vdouble(5.0), #GeV
                            SingleChannelThreshold = cms.double(1.0), #GeV
                            )

susycafhfrechit = cms.EDProducer("SusyCAF_HFRecHitsSorted",
                            InputTag = cms.InputTag('hfreco'),
                            Prefix = cms.string('rechit'),
                            Suffix = cms.string('hf'),
                            SingleRbxThresholds = cms.vdouble(10.0), #GeV
                            SingleRmThresholds = cms.vdouble(5.0), #GeV
                            SingleChannelThreshold = cms.double(1.0), #GeV
                            )

susycafhorechit = cms.EDProducer("SusyCAF_HORecHitsSorted",
                            InputTag = cms.InputTag('horeco'),
                            Prefix = cms.string('rechit'),
                            Suffix = cms.string('ho'),
                            SingleRbxThresholds = cms.vdouble(10.0), #GeV
                            SingleRmThresholds = cms.vdouble(5.0), #GeV
                            SingleChannelThreshold = cms.double(1.0), #GeV
                            )

