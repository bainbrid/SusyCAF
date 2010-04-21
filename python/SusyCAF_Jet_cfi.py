import FWCore.ParameterSet.Config as cms

def patjets( calo = True, input = '', genInput = '', prefix = '', jetid = True) :
    return cms.EDProducer( "SusyCAF_PatJet",
                           InputTag = cms.InputTag(input),
                           AllJets = cms.InputTag(input),
                           GenInputTag = cms.InputTag(genInput),
                           Prefix = cms.string(prefix),
                           Suffix = cms.string('Pat'),
                           Calo = cms.bool(calo),
                           PF = cms.bool(not calo),
                           JetID = cms.bool(jetid),
                           MPT = cms.bool(True),
                           GenInfo = cms.bool(False),
                           PrimaryVertexTag = cms.InputTag('offlinePrimaryVertices'),
                           MaxD0Trk = cms.double(0.02),
                           PtErrFracTrk = cms.double(0.2)
                           )

def jets( calo = True, input = '', genInput = '', prefix = '') :
    return cms.EDProducer( "SusyCAF_CaloJet" if calo else "SusyCAF_PFJet" ,
                           InputTag = cms.InputTag(input),
                           AllJets = cms.InputTag(input),
                           GenInputTag = cms.InputTag(genInput),
                           Prefix = cms.string(prefix),
                           Suffix = cms.string( 'Calo' if calo else 'PF'),
                           Calo = cms.bool(calo),
                           PF = cms.bool(not calo),
                           MPT = cms.bool(False),
                           JetID = cms.bool(False),
                           GenInfo = cms.bool(False),
                           )

# Without SusyPAT
susycafic5calojetreco = jets( input = 'iterativeCone5CaloJets',       prefix = 'ic5Jet',    genInput = 'iterativeCone5GenJets')
susycafsc5calojetreco = jets( input = 'sisCone5CaloJets',             prefix = 'sc5Jet',    genInput = 'sisCone5GenJets' )
susycafak5calojetreco = jets( input = 'ak5CaloJets',                  prefix = 'ak5Jet',    genInput = 'ak5GenJets'  )
susycafak7calojetreco = jets( input = 'ak7CaloJets',                  prefix = 'ak7Jet',    genInput = 'ak7GenJets' )
susycafak5jptjetreco  = jets( input = 'JetPlusTrackZSPCorJetAntiKt5', prefix = 'ak5JetJPT', genInput = 'ak5GenJets' )
susycafic5pfjetreco  =  jets( input = 'iterativeCone5PFJets',         prefix = 'ic5Jet',    genInput = 'iterativeCone5GenJets' , calo = False )
susycafak5pfjetreco  =  jets( input = 'ak5PFJets',                    prefix = 'ak5Jet',    genInput = 'ak5GenJets' , calo = False )

# With SusyPAT
susycafic5calojet = patjets( input = 'cleanPatJetsIC5Calo', prefix = 'ic5Jet',    genInput = 'iterativeCone5GenJets' )
susycafsc5calojet = patjets( input = 'cleanPatJetsSC5Calo', prefix = 'sc5Jet',    genInput = 'sisCone5GenJets' )
susycafak5calojet = patjets( input = 'cleanPatJetsAK5Calo', prefix = 'ak5Jet',    genInput = 'ak5GenJets' )
susycafak7calojet = patjets( input = 'cleanPatJetsAK7Calo', prefix = 'ak7Jet',    genInput = 'ak7GenJets' )
susycafak5jptjet =  patjets( input = 'cleanPatJetsAK5JPT',  prefix = 'ak5JetJPT', genInput = 'ak5GenJets' )
susycafic5pfjet =  patjets(  input = 'cleanPatJetsIC5PF',   prefix = 'ic5JetPF',  genInput = 'iterativeCone5GenJets',  jetid = False, calo = False )
susycafak5pfjet = patjets(   input = 'cleanPatJetsAK5PF',   prefix = 'ak5JetPF',  genInput = 'ak5GenJets',             jetid = False, calo = False )

#matched collections
susycafic5calojetMatched = susycafic5calojet.clone( GenInfo = True )
susycafsc5calojetMatched = susycafsc5calojet.clone( GenInfo = True )
susycafak5calojetMatched = susycafak5calojet.clone( GenInfo = True )
susycafak7calojetMatched = susycafak7calojet.clone( GenInfo = True )
susycafak5jptjetMatched = susycafak5jptjet.clone(   GenInfo = True )
susycafic5pfjetMatched = susycafic5pfjet.clone(     GenInfo = True )
susycafak5pfjetMatched = susycafak5pfjet.clone(     GenInfo = True )
