import FWCore.ParameterSet.Config as cms

#default options

susycaf_calojet = cms.EDProducer("SusyCAF_CaloJet",
                                 InputTag = cms.InputTag(''),
                                 GenInputTag = cms.InputTag(''),
                                 Prefix = cms.string(''),
                                 Suffix = cms.string('Calo'),
                                 Calo = cms.bool(True),
                                 PF = cms.bool(False),
                                 JetID = cms.bool(False),
                                 MPT = cms.bool(False),
                                 )

susycaf_pfjet = cms.EDProducer("SusyCAF_PFJet",
                               InputTag = cms.InputTag(''),
                               GenInputTag = cms.InputTag(''),
                               Prefix = cms.string(''),
                               Suffix = cms.string('PF'),
                               Calo = cms.bool(False),
                               PF = cms.bool(True),
                               JetID = cms.bool(False),
                               MPT = cms.bool(False),
                               )

susycaf_patjet = cms.EDProducer("SusyCAF_PatJet",
                                InputTag = cms.InputTag(''),
                                GenInputTag = cms.InputTag(''),
                                Prefix = cms.string(''),
                                Suffix = cms.string('Pat'),
                                Calo = cms.bool(True),
                                PF = cms.bool(False),
                                JetID = cms.bool(True),
                                MPT = cms.bool(True),
                                GenInfo = cms.bool(True),
                                PrimaryVertexTag = cms.InputTag('offlinePrimaryVertices'),
                                MaxD0Trk = cms.double(0.02),
                                PtErrFracTrk = cms.double(0.2)
                                )

# Without SusyPAT
susycafic5calojetreco = susycaf_calojet.clone( InputTag = 'iterativeCone5CaloJets',       Prefix = 'ic5Jet' )
susycafsc5calojetreco = susycaf_calojet.clone( InputTag = 'sisCone5CaloJets',             Prefix = 'sc5Jet' )
susycafak5calojetreco = susycaf_calojet.clone( InputTag = 'ak5CaloJets',                  Prefix = 'ak5Jet' )
susycafak7calojetreco = susycaf_calojet.clone( InputTag = 'ak7CaloJets',                  Prefix = 'ak7Jet' )
susycafak5jptjetreco  = susycaf_calojet.clone( InputTag = 'JetPlusTrackZSPCorJetAntiKt5', Prefix = 'ak5JetJPT', JetID = False)
susycafic5pfjetreco = susycaf_pfjet.clone(     InputTag = 'iterativeCone5PFJets',         Prefix = 'ic5Jet' )
susycafak5pfjetreco = susycaf_pfjet.clone(     InputTag = 'ak5PFJets',                    Prefix = 'ak5Jet' )

# With SusyPAT
susycafic5calojet = susycaf_patjet.clone( InputTag = 'cleanLayer1JetsIC5', GenInputTag = 'iterativeCone5GenJets',  Prefix = 'ic5Jet'    )
susycafsc5calojet = susycaf_patjet.clone( InputTag = 'cleanLayer1JetsSC5', GenInputTag = 'sisCone5GenJets',   Prefix = 'sc5Jet'    )
susycafak5calojet = susycaf_patjet.clone( InputTag = 'cleanLayer1JetsAK5', GenInputTag = 'ak5GenJets',   Prefix = 'ak5Jet'    )
susycafak7calojet = susycaf_patjet.clone( InputTag = 'cleanLayer1JetsAK7', GenInputTag = 'ak7GenJets',   Prefix = 'ak7Jet'    )
susycafak5jptjet = susycaf_patjet.clone(  InputTag = 'cleanLayer1JetsAK5JPT', GenInputTag = 'ak5GenJets', Prefix = 'ak5JetJPT', JetID = False )
susycafic5pfjet = susycaf_patjet.clone(   InputTag = 'cleanLayer1JetsIC5PF', GenInputTag = 'iterativeCone5GenJets', Prefix = 'ic5JetPF', JetID = False, PF = True, Calo = False )
susycafak5pfjet = susycaf_patjet.clone(   InputTag = 'cleanLayer1JetsAK5PF', GenInputTag = 'ak5GenJets', Prefix = 'ak5JetPF', JetID = False, PF = True, Calo = False )


