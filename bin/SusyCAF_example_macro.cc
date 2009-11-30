// root -b -q SusyCAF_example_macro.cc+ 
// scram b ; cmsenv ; SusyCaf_example_macro;

#include "SusyCAFLinkDef.h"
//#include "SUSYBSMAnalysis/SusyCAF/interface/TTREE_FOREACH_ENTRY.hh"
#include "../interface/TTREE_FOREACH_ENTRY.hh"
#include <iostream>

#include "TH1F.h"
#include "TCanvas.h"
#include "TChain.h"

LorentzV MHT(std::vector<LorentzV>&);
void drawSame(TH1*, TH1*, const char*);
TChain* getChain();


void SusyCAF_example_macro() {
  TH1F* met = new TH1F("met","", 100,0,25);
  TH1F* mht = new TH1F("mht","", 100,0,25);  
  TH1F* mht_uncorr = new TH1F("mht_uncorr","", 100,0,25);  
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
      met->Fill( metP4Calo->pt());
      mht->Fill( MHT(clean_jets).pt() );
      mht_uncorr->Fill( MHT(clean_jets_uncorr).pt() );
    }
  }
  drawSame(met, mht, "met_mht.eps");
  drawSame(met, mht_uncorr, "met_mht_uncorr.eps");
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


int main() {
  SusyCAF_example_macro();
}
