#!/usr/bin/env python

import sys,ROOT as r

if len(sys.argv)<2 :
    print "Usage: %s root-file"%sys.argv[0]
    exit()
    
f = r.TFile(sys.argv[1])
tree = f.Get("susyTree/tree")

vars = ":".join(["run","lumiSection","event",
                 "electronP4Pat.fCoordinates.fPt",
                 "electronP4Pat.fCoordinates.fEta",
                 "electroneidTightPat","electroneidRobustTightPat",
                 "electroneidLoosePat","electroneidRobustLoosePat",
                 "electronIdPfevspiPat"
                 ])
format = "colsize=17 col="+":".join(["7d","5d","10d",
                                     "8.2f",
                                     "5.2f",
                                     "6.3f","6.3f",
                                     "6.3f","6.3f",
                                     "6.3f",
                                     ])
tree.Scan(vars, "", format)
f.Close()
