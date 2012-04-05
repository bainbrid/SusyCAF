#!/usr/bin/env python

import ROOT as r

f = r.TFile("SusyCAF_Tree.root")
tree = f.Get("susyTree/tree")
vars = "run:lumiSection:event:ak5JetCorrectedP4Pat.fCoordinates.fPt:ak5JetCorrectedP4Pat.fCoordinates.fEta:ak5JetJetIDFHPDPat:ak5JetJetIDResEMFPat:ak5JetJetIDloosePat"
format = "colsize=17 col=7d:5d:10d:8.2f:5.2f:6.3f:6.3f:2d"
tree.Scan(vars, "", format)
f.Close()
