#!/usr/bin/env python

import ROOT as r

f = r.TFile("SusyCAF_Tree.root")
tree = f.Get("susyTree/tree")
tree.Scan("run:lumiSection:event:ak5JetCorrectedP4Pat.fCoordinates.fPt:ak5JetCorrectedP4Pat.fCoordinates.fEta:ak5JetJetIDFHPDPat:ak5JetJetIDResEMFPat", "", "colsize=17")
f.Close()
