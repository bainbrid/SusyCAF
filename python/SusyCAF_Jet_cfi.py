import FWCore.ParameterSet.Config as cms

def patjets( calo = True, input = '', genInput = '', prefix = '', jetid = True, pf = False, jpt = False) :
    switches_on = int(calo) + int(pf) + int(jpt)
    if switches_on != 1 : raise NameError("Only one of Calo:PF:JPT!!")
    return cms.EDProducer( "SusyCAF_PatJet",
                           InputTag = cms.InputTag(input),
                           AllJets = cms.InputTag(input),
                           GenInputTag = cms.InputTag(genInput),
                           Prefix = cms.string(prefix),
                           Suffix = cms.string('Pat'),
                           Calo = cms.bool(calo),
                           JPT = cms.bool(jpt),
                           PF = cms.bool(pf),
                           JetID = cms.bool(jetid),
                           MPT = cms.bool(True),
                           GenInfo = cms.bool(False),
                           PrimaryVertexTag = cms.InputTag('offlinePrimaryVertices'),
                           MaxD0Trk = cms.double(0.02),
                           PtErrFracTrk = cms.double(0.2)
                           )

def jets( calo = True, input = '', genInput = '', prefix = '', pf = False, jpt = False) :
    switches_on = int(calo) + int(pf) + int(jpt)
    if switches_on != 1 : raise NameError("Only one of Calo:PF:JPT!!")
    jet_instance = ""
    if calo : jet_instance = "Calo"
    elif jpt : jet_instance = "JPT"
    elif pf : jet_instance = "PF"
    return cms.EDProducer( "SusyCAF_"+jet_instance+"Jet",
                           InputTag = cms.InputTag(input),
                           AllJets = cms.InputTag(input),
                           GenInputTag = cms.InputTag(genInput),
                           Prefix = cms.string(prefix),
                           Suffix = cms.string(jet_instance),
                           Calo = cms.bool(calo),
                           JPT = cms.bool(jpt),
                           PF = cms.bool(pf),
                           MPT = cms.bool(False),
                           JetID = cms.bool(False),
                           GenInfo = cms.bool(False),
                           )

# Without SusyPAT
susycafic5calojetreco = jets( input = 'iterativeCone5CaloJets',       prefix = 'ic5Jet',    genInput = 'iterativeCone5GenJets')
susycafak5calojetreco = jets( input = 'ak5CaloJets',                  prefix = 'ak5Jet',    genInput = 'ak5GenJets'  )
susycafak7calojetreco = jets( input = 'ak7CaloJets',                  prefix = 'ak7Jet',    genInput = 'ak7GenJets' )
susycafak5jptjetreco  = jets( input = 'JetPlusTrackZSPCorJetAntiKt5', prefix = 'ak5JetJPT', genInput = 'ak5GenJets', calo = False, jpt = True )
susycafic5pfjetreco  =  jets( input = 'iterativeCone5PFJets',         prefix = 'ic5Jet',    genInput = 'iterativeCone5GenJets' , calo = False, pf = True )
susycafak5pfjetreco  =  jets( input = 'ak5PFJets',                    prefix = 'ak5Jet',    genInput = 'ak5GenJets' , calo = False, pf = True )

# With SusyPAT
susycafic5calojet = patjets( input = 'cleanPatJetsIC5Calo', prefix = 'ic5Jet',    genInput = 'iterativeCone5GenJets' )
susycafak5calojet = patjets( input = 'cleanPatJetsAK5Calo', prefix = 'ak5Jet',    genInput = 'ak5GenJets' )
susycafak7calojet = patjets( input = 'cleanPatJetsAK7Calo', prefix = 'ak7Jet',    genInput = 'ak7GenJets' )
susycafak5jptjet =  patjets( input = 'cleanPatJetsAK5JPT',  prefix = 'ak5JetJPT', genInput = 'ak5GenJets', calo = False, jpt = True )
susycafak5pfjet = patjets(   input = 'cleanPatJetsAK5PF',   prefix = 'ak5JetPF',  genInput = 'ak5GenJets',  jetid = False, calo = False, pf = True )
susycafak5pf2patjet = patjets(   input = 'selectedPatJetsPF',   prefix = 'ak5JetPF2PAT',  genInput = 'ak5GenJets',jetid = False, calo = False , pf = True )

#matched collections
susycafic5calojetMatched = susycafic5calojet.clone( GenInfo = True )
susycafak5calojetMatched = susycafak5calojet.clone( GenInfo = True )
susycafak7calojetMatched = susycafak7calojet.clone( GenInfo = True )
susycafak5jptjetMatched = susycafak5jptjet.clone(   GenInfo = True )
susycafak5pfjetMatched = susycafak5pfjet.clone(     GenInfo = True )
susycafak5pf2patjetMatched = susycafak5pf2patjet.clone(     GenInfo = True )
