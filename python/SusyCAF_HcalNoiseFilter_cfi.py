import FWCore.ParameterSet.Config as cms

susycafhcalnoisefilter = cms.EDProducer(
    "SusyCAF_HcalNoiseFilter",
    InputTag = cms.InputTag('HBHENoiseFilterResultProducer:HBHENoiseFilterResult'),
    Prefix = cms.string('hbheNoise'),
    Suffix = cms.string(''),
    )
