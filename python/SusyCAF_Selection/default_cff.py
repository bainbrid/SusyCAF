import FWCore.ParameterSet.Config as cms

def insertSelection(process):
#______________________ Event-Selection _____________________________
    from SUSYBSMAnalysis.SusyCAF.SusyCAF_Selection.selectors_cfi import hltFilter
    process.hltFilter = hltFilter.clone( HLTPaths = ['HLT_ZeroBias'] )
    #add more filters here

    process.eventSelectionSequence = cms.Sequence(process.hltFilter)

#______________________ Object-Selection _____________________________
    from SUSYBSMAnalysis.SusyCAF.SusyCAF_Selection.helpers import applySelection
    selectors = []
    from SUSYBSMAnalysis.SusyCAF.SusyCAF_Selection.selectors_cfi import patJetSelector
    for sequence in [process.nPatJet] :
        selectors.extend(applySelection(process, sequence, "pt > 10", patJetSelector))

    #NOTE: filter=True here kills all events with no jets with pt > 8 *and* phi > 0
    #to kill only events with phi > 0 and then select on pt switch the order of the two functioncalls
    #selectors.extend(applySelection(process, process.nTuplePatJetMatchedSequence,
    #                                "phi > 0", patJetSelector, filter=True))
    #PS: this is just to demonstrate that multipleselectors are possible. of course "pt > 8 && phi > 0" in one selector would be totally sufficient

    #add more selectors here...


    process.objectSelectionSequence = cms.Sequence( selectors[0] )#sigh sequences are a pain
    for selector in selectors[1:]:
        process.objectSelectionSequence += selector
    
#process.jetSelector)

#______________________     Insertion    _____________________________
    process.nCommon = cms.Sequence( #process.eventSelectionSequence + 
                                    process.objectSelectionSequence +
                                    process.nCommon)
    
