import FWCore.ParameterSet.Config as cms

#______________________ Event-Selection _____________________________

from HLTrigger.HLTfilters.hltHighLevel_cfi import hltHighLevel
hltFilter = hltHighLevel.clone(
    andOr = True, ## choose logical OR between Triggerbits
    HLTPaths = ['HLT_ZeroBias'],
    throw = False # tolerate triggers stated above, but not available
    )

#______________________ Object-Selection ____________________________
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import selectedLayer1Jets
patJetSelector = selectedLayer1Jets.clone( filter = cms.bool(False), src = "", cut = "")

candStringSelector = cms.EDFilter("CandViewSelector",
    filter = cms.bool(False),
    src = cms.InputTag(""),
    cut = cms.string("")
)


