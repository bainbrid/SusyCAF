#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_PileupSummary.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h" 

SusyCAF_PileupSummary::SusyCAF_PileupSummary(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
  Prefix(iConfig.getParameter<std::string>("Prefix")),
  Suffix(iConfig.getParameter<std::string>("Suffix"))
{
  
  produces <bool>  ( Prefix + "HandleValid" + Suffix);
  produces <unsigned>(Prefix + "InteractionsBX0" + Suffix);
  produces <std::vector<unsigned> >(Prefix + "Interactions" + Suffix);
  produces <std::vector<int> >(Prefix + "BX" + Suffix);
}

void SusyCAF_PileupSummary::
produce(edm::Event& event, const edm::EventSetup& ) {
  std::auto_ptr<unsigned> interactionsBX0  (new unsigned());
  std::auto_ptr<std::vector<unsigned> > interactions ( new std::vector<unsigned>() );
  std::auto_ptr<std::vector<int> >      bx           ( new std::vector<int>() );

  typedef std::vector<PileupSummaryInfo> PIV;
  edm::Handle<PIV> pileup;
  event.getByLabel(inputTag,pileup);

  if (pileup.isValid()) {
    for(PIV::const_iterator pu = pileup->begin(); pu != pileup->end(); ++pu) {
      interactions->push_back(pu->getPU_NumInteractions());
      bx->push_back(pu->getBunchCrossing());
      if (!pu->getBunchCrossing()) 
	*interactionsBX0.get() = pu->getPU_NumInteractions();
    }
  }

  event.put( std::auto_ptr<bool>( new bool(pileup.isValid())), Prefix + "HandleValid" + Suffix );
  event.put( interactionsBX0, Prefix + "InteractionsBX0" + Suffix );
  event.put( interactions,    Prefix + "Interactions"    + Suffix );
  event.put( bx,              Prefix + "BX"              + Suffix );
  
}
