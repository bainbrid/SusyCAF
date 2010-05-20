import FWCore.ParameterSet.Config as cms

susycafgen = cms.EDProducer("SusyCAF_GenParticle",
                        InputTag=cms.InputTag('genParticles'),
                        Prefix = cms.string('gen'),
                        Suffix = cms.string(''),
			GenStatus1PtCut = cms.double(5.0)
                        )
