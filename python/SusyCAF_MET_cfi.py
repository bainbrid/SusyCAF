import FWCore.ParameterSet.Config as cms

def met(mettype, input, suf, pre='met', special=False, calo=True) :
    return cms.EDProducer("SusyCAF_%sMET"%mettype,
                          InputTag = cms.InputTag(input),
                          Prefix = cms.string(pre),
                          Suffix = cms.string(suf),
                          ProduceSpecial = cms.bool(special),
                          Calo = cms.bool(calo))

susycafmet          = met('Calo', 'met'                     , 'Calo'      ,           )
susycafmetnohf      = met('Calo', 'metNoHF'                 , 'Calo'      ,  'metnohf')
susycafmetIC5       = met('Pat' , 'patMETsIC5Calo'          , 'ICF'       ,           )
susycafmetAK5       = met('Pat' , 'patMETsAK5Calo'          , 'AK5'       ,           )
susycafmetAK5TypeI  = met('Pat' , 'caloType1CorrectedMet'   , 'AK5TypeI'  ,           ) #adding for testing
susycafmetAK5TypeII = met('Pat' , 'patMETsAK5CaloTypeII'    , 'AK5TypeII' ,           )
susycafmetPF        = met('Pat' , 'patMETsPF'               , 'PF'        , calo=False)
susycafmetTypeIPF   = met('PF'  , 'pfType1CorrectedMet'     , 'TypeIPF'   , calo=False)
susycafmetTypeIPFPat= met('Pat' , 'patType1CorrectedPFMetPF', 'TypeIPFPat', calo=False)
susycafmetTC        = met('Pat' , 'patMETsTC'               , 'TC'        , calo=False)


