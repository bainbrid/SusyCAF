import FWCore.ParameterSet.Config as cms

def kargs() :
    return {
        "StoreConversionInfo": cms.bool(True),
        #"IdFlagsOldStyle": cms.vstring("eidTight", "eidRobustTight", "eidLoose", "eidRobustLoose"),
        "IdFlagsOldStyle": cms.vstring(),

        #http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/EGamma/EGammaAnalysisTools/test/run_exampleCuts_cfg.py?revision=1.1&view=markup
        "conversionsInputTag": cms.InputTag("allConversions"),
        "beamSpotInputTag": cms.InputTag("offlineBeamSpot"),
        "rhoIsoInputTag": cms.InputTag("kt6PFJetsForIsolation", "rho"),
        "primaryVertexInputTag": cms.InputTag("offlinePrimaryVertices"),
        "isoValInputTags": cms.VInputTag(cms.InputTag('elPFIsoValueCharged03PFIdPFIso'),
                                         cms.InputTag('elPFIsoValueGamma03PFIdPFIso'),
                                         cms.InputTag('elPFIsoValueNeutral03PFIdPFIso')
                                         ),
        }
                                     
        
susycafelectronreco = cms.EDProducer("SusyCAF_GsfElectron",
                                     InputTag = cms.InputTag('gsfElectrons'),
                                     SelectedElectrons = cms.InputTag(''),
                                     Prefix = cms.string('electron'),
                                     Suffix = cms.string('Gsf'),
                                     **kargs()
                                     )

susycafelectron = cms.EDProducer("SusyCAF_PatElectron",
                                 InputTag = cms.InputTag('cleanPatElectrons'),
                                 SelectedElectrons = cms.InputTag(''),
                                 Prefix = cms.string('electron'),
                                 Suffix = cms.string('Pat'),
                                 **kargs()
                                 )

susycafpfelectron = cms.EDProducer("SusyCAF_PatElectron",
                                   InputTag = cms.InputTag('patAllElectronsPF'),
                                   SelectedElectrons = cms.InputTag('selectedPatElectronsPF'),
                                   Prefix = cms.string('electron'),
                                   Suffix = cms.string('PF'),
                                   **kargs()
                                   )

