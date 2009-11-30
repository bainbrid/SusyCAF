/* From SUSYBSMAnalysis/SusyCAF/
 * > scram b
 * > cmsenv
 * > cmsRun test/treeDataPat_cfg.py
 * > SusyCaf_example_macro_with_Book
 */

#include "SusyCAFLinkDef.h"
#include "SUSYBSMAnalysis/SusyCAF/interface/TTREE_FOREACH_ENTRY.hh"
#include "SUSYBSMAnalysis/SusyCAF/interface/Book.h"
#include <iostream>

#include "TH1F.h"
#include "TCanvas.h"
#include "TChain.h"

LorentzV MHT(std::vector<LorentzV>&);
void drawSame(TH1*, TH1*, const char*);
TChain* getChain();

int main() {
  Book book;
  TTREE_FOREACH_ENTRY(getChain(),
		      std::vector<LorentzV>* LEAF(ic5JetCorrectedP4Pat)
		      LorentzV*              LEAF(metP4Calo)
		      trigger_t*             LEAF(triggered)
		      std::vector<double>*   LEAF(ic5JetResEMFPat)
		      std::vector<double>*   LEAF(ic5JetCorrFactorPat)
		      ) {

    std::vector<LorentzV> clean_jets;
    std::vector<LorentzV> clean_jets_uncorr;
    for(unsigned i = 0; i<ic5JetCorrectedP4Pat->size(); i++) {
      if((*ic5JetResEMFPat)[i] > 0.01) {
	clean_jets.push_back( (*ic5JetCorrectedP4Pat)[i] );
	clean_jets_uncorr.push_back( (*ic5JetCorrectedP4Pat)[i] / (*ic5JetCorrFactorPat)[i] );
      }
    }

    if( (*triggered)["HLT_HcalNZS_8E29"] && clean_jets.size() ) {
      book.fill( metP4Calo->pt(),             "met",       100,0,25);
      book.fill( MHT(clean_jets).pt(),        "mht",       100,0,25);
      book.fill( MHT(clean_jets_uncorr).pt(), "mht_uncorr",100,0,25);
    }
  }
  drawSame(book["met"], book["mht"],        "met_mht.eps");
  drawSame(book["met"], book["mht_uncorr"], "met_mht_uncorr.eps");
}


TChain* getChain() {
  std::string fileName = "./patTree.root";
  std::string treeName = "/susyTree/tree";
  TChain * chain = new TChain("chain");
  chain->Add((fileName+treeName).c_str());
  return chain;
}


LorentzV MHT(std::vector<LorentzV>& fourVs) {
  LorentzV sum;
  for( unsigned i=0; i<fourVs.size(); i++)
    sum += fourVs[i];
  return -sum;
}


void drawSame(TH1* h1, TH1* h2, const char* filename) {
  TCanvas * c = new TCanvas("c","",800,600);

  double max = std::max(h1->GetMaximum(),h2->GetMaximum());
  h1->SetMaximum(1.1*max);
  h2->SetMaximum(1.1*max);

  h1->SetLineWidth(2);
  h2->SetFillColor(17);

  h1->Draw();
  h2->Draw("same");
  h1->Draw("same");
  c->SaveAs(filename);
  delete c;
}


