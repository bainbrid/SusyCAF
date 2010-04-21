import FWCore.ParameterSet.Config as cms

susycafpfrechitecal = cms.EDProducer("SusyCAF_PFRecHit",
                                     InputTag = cms.InputTag("particleFlowClusterECAL","Cleaned"),
                                     Prefix = cms.string('rechitPF'),
                                     Suffix = cms.string('Ecal'),
                                     )

susycafpfrechithcal = cms.EDProducer("SusyCAF_PFRecHit",
                                     InputTag = cms.InputTag("particleFlowClusterHCAL","Cleaned"),
                                     Prefix = cms.string('rechitPF'),
                                     Suffix = cms.string('Hcal'),
                                     )

susycafpfrechithfem = cms.EDProducer("SusyCAF_PFRecHit",
                                     InputTag = cms.InputTag("particleFlowClusterHFEM","Cleaned"),
                                     Prefix = cms.string('rechitPF'),
                                     Suffix = cms.string('Hfem'),
                                     )

susycafpfrechithfhad = cms.EDProducer("SusyCAF_PFRecHit",
                                      InputTag = cms.InputTag("particleFlowClusterHFHAD","Cleaned"),
                                      Prefix = cms.string('rechitPF'),
                                      Suffix = cms.string('Hfhad'),
                                      )

susycafpfrechitps = cms.EDProducer("SusyCAF_PFRecHit",
                                   InputTag = cms.InputTag("particleFlowClusterPS","Cleaned"),
                                   Prefix = cms.string('rechitPF'),
                                   Suffix = cms.string('Ps'),
                                   )
