#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_L1CaloTrigger.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/L1GlobalCaloTrigger/interface/L1GctCollections.h"

SusyCAF_L1CaloTrigger::SusyCAF_L1CaloTrigger(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag"))
{
  produces <std::vector<unsigned int> > ( "l1hthw"     );
  produces <std::vector<unsigned int> > ( "l1ethw"     );
  produces <std::vector<unsigned int> > ( "l1methw"    );
  produces <std::vector<unsigned int> > ( "l1metphihw" );
  produces <std::vector<unsigned int> > ( "l1mhthw"    );
  produces <std::vector<unsigned int> > ( "l1mhtphihw" );
}

void SusyCAF_L1CaloTrigger::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  std::auto_ptr<std::vector<unsigned int> > l1hthw      ( new std::vector<unsigned int>() );
  std::auto_ptr<std::vector<unsigned int> > l1ethw      ( new std::vector<unsigned int>() );
  std::auto_ptr<std::vector<unsigned int> > l1methw     ( new std::vector<unsigned int>() );
  std::auto_ptr<std::vector<unsigned int> > l1metphihw  ( new std::vector<unsigned int>() );
  std::auto_ptr<std::vector<unsigned int> > l1mhthw     ( new std::vector<unsigned int>() );
  std::auto_ptr<std::vector<unsigned int> > l1mhtphihw  ( new std::vector<unsigned int>() );

  //todo: l1 jets, electrons, extra particles

  //ET
  edm::Handle<L1GctEtTotalCollection> l1GctEtTotals;
  iEvent.getByLabel(inputTag,l1GctEtTotals);
  for(L1GctEtTotalCollection::const_iterator it = l1GctEtTotals->begin(); it != l1GctEtTotals->end(); ++it) {
    l1ethw->push_back(it->et());
  }
  
  //HT
  edm::Handle<L1GctEtHadCollection> l1GctEtHads;
  iEvent.getByLabel(inputTag,l1GctEtHads);
  for(L1GctEtHadCollection::const_iterator it = l1GctEtHads->begin(); it != l1GctEtHads->end(); ++it) {
    l1hthw->push_back(it->et());
  }

  //MET
  edm::Handle<L1GctEtMissCollection> l1GctEtMisss;
  iEvent.getByLabel(inputTag,l1GctEtMisss);
  for(L1GctEtMissCollection::const_iterator it = l1GctEtMisss->begin(); it != l1GctEtMisss->end(); ++it) {
    l1methw->push_back(it->et());
    l1metphihw->push_back(it->phi());
  }

  //MHT
  edm::Handle<L1GctHtMissCollection> l1GctHtMisss;
  iEvent.getByLabel(inputTag,l1GctHtMisss);
  for(L1GctHtMissCollection::const_iterator it = l1GctHtMisss->begin(); it != l1GctHtMisss->end(); ++it) {
    l1mhthw->push_back(it->et());
    l1mhtphihw->push_back(it->phi());
  }

  iEvent.put( l1hthw,     "l1hthw"     );
  iEvent.put( l1ethw,     "l1ethw"     );
  iEvent.put( l1methw,    "l1methw"    );
  iEvent.put( l1metphihw, "l1metphihw" );
  iEvent.put( l1mhthw,    "l1mhthw"    );
  iEvent.put( l1mhtphihw, "l1mhtphihw" );
  
}
