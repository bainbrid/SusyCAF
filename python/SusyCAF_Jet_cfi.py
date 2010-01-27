import FWCore.ParameterSet.Config as cms

# reco::CaloJets for IC5, SC5, AK5, AK7

susycafic5calojetreco = cms.EDProducer(
    "SusyCAF_CaloJet",
    InputTag = cms.InputTag('iterativeCone5CaloJets'),
    Prefix = cms.string('ic5Jet'),
    Suffix = cms.string('Calo')
    )

susycafsc5calojetreco = cms.EDProducer(
    "SusyCAF_CaloJet",
    InputTag = cms.InputTag('sisCone5CaloJets'),
    Prefix = cms.string('sc5Jet'),
    Suffix = cms.string('Calo')
    )

susycafak5calojetreco = cms.EDProducer(
    "SusyCAF_CaloJet",
    InputTag = cms.InputTag('ak5CaloJets'),
    Prefix = cms.string('ak5Jet'),
    Suffix = cms.string('Calo')
    )

susycafak7calojetreco = cms.EDProducer(
    "SusyCAF_CaloJet",
    InputTag = cms.InputTag('ak7CaloJets'),
    Prefix = cms.string('ak7Jet'),
    Suffix = cms.string('Calo')
    )

# pat::Jets for IC5, SC5, AK5, AK7

susycafic5calojet = cms.EDProducer(
    "SusyCAF_PatJet",
    InputTag = cms.InputTag('cleanLayer1JetsIC5'),
    PrimaryVertexTag = cms.InputTag('offlinePrimaryVertices'),
    MaxD0Trk = cms.double(0.02),
    PtErrFracTrk = cms.double(0.2),
    Prefix = cms.string('ic5Jet'),
    Suffix = cms.string('Pat')
    )

susycafsc5calojet = cms.EDProducer(
    "SusyCAF_PatJet",
    InputTag = cms.InputTag('cleanLayer1JetsSC5'),
    PrimaryVertexTag = cms.InputTag('offlinePrimaryVertices'),
    MaxD0Trk = cms.double(0.02),
    PtErrFracTrk = cms.double(0.2),
    Prefix = cms.string('sc5Jet'),
    Suffix = cms.string('Pat')
    )

susycafak5calojet = cms.EDProducer(
    "SusyCAF_PatJet",
    InputTag = cms.InputTag('cleanLayer1JetsAK5'),
    PrimaryVertexTag = cms.InputTag('offlinePrimaryVertices'),
    MaxD0Trk = cms.double(0.02),
    PtErrFracTrk = cms.double(0.2),
    Prefix = cms.string('ak5Jet'),
    Suffix = cms.string('Pat')
                            )

susycafak7calojet = cms.EDProducer(
    "SusyCAF_PatJet",
    InputTag = cms.InputTag('cleanLayer1JetsAK7'),
    PrimaryVertexTag = cms.InputTag('offlinePrimaryVertices'),
    MaxD0Trk = cms.double(0.02),
    PtErrFracTrk = cms.double(0.2),
    Prefix = cms.string('ak7Jet'),
    Suffix = cms.string('Pat')
    )

# "JPT-corrected" reco::CaloJets and pat::Jets for AK5

susycafak5jptjetreco = cms.EDProducer(
    "SusyCAF_CaloJet",
    InputTag = cms.InputTag('JetPlusTrackZSPCorJetAntiKt5'),
    Prefix = cms.string('ak5JetJPT'),
    Suffix = cms.string('Calo')
    )

susycafak5jptjet = cms.EDProducer(
    "SusyCAF_PatJet",
    InputTag = cms.InputTag('cleanLayer1JetsAK5JPT'),
    PrimaryVertexTag = cms.InputTag('offlinePrimaryVertices'),
    MaxD0Trk = cms.double(0.02),
    PtErrFracTrk = cms.double(0.2),
    Prefix = cms.string('ak5JetJPT'),
    Suffix = cms.string('Pat')
    )
