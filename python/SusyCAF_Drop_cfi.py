def reduce() :
    return ['double_susycaf*_*_*',
            'doubles_susycaf*_*_*',
            'doubleROOTMathPxPyPzE4DROOTMathLorentzVector*_susycaf*_*_*',
            'doubleROOTMathPtEtaPhiE4DROOTMathLorentzVector*_susycaf*_*_*',
            'doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathPositionVector3D*_susycaf*_*_*',
            'doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3D*_susycaf*_*_*'
            ]

def drop() :
    return [
        '*_susycaf*_CTECALEsumcalo*_*',
        '*_susycaf*_CTHCALEsumcalo*_*',
        '*_susycaf*_*MPTwithLooseTracks*_*',
        '*_susycaf*_*MPTwithAllTracks*_*',
        '*_susycaf*_*MPTwithEverything*_*',
        '*_susycaf*_hltL1Seeds*_*',
        ]
