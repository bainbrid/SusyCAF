import FWCore.ParameterSet.Config as cms

susycafgen = cms.EDProducer("SusyCAF_GenParticle",
                            InputTag=cms.InputTag('genParticles'),
                            JetCollections=cms.VInputTag('iterativeCone5GenJets','ak5GenJets','ak7GenJets'),
                            Prefix = cms.string('gen'),
                            Suffix = cms.string(''),
                            GenStatus1PtCut = cms.double(5.0)
                        )
