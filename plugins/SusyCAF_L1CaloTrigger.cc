#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_L1CaloTrigger.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/L1GlobalCaloTrigger/interface/L1GctCollections.h"

SusyCAF_L1CaloTrigger::SusyCAF_L1CaloTrigger(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag"))
{
  produces <std::vector<unsigned int> > ( "l1ht"     );
  produces <std::vector<unsigned int> > ( "l1et"     );
  produces <std::vector<unsigned int> > ( "l1met"    );
  produces <std::vector<unsigned int> > ( "l1metphi" );
  produces <std::vector<unsigned int> > ( "l1mht"    );
  produces <std::vector<unsigned int> > ( "l1mhtphi" );
}

void SusyCAF_L1CaloTrigger::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  std::auto_ptr<std::vector<unsigned int> > l1ht      ( new std::vector<unsigned int>() );
  std::auto_ptr<std::vector<unsigned int> > l1et      ( new std::vector<unsigned int>() );
  std::auto_ptr<std::vector<unsigned int> > l1met     ( new std::vector<unsigned int>() );
  std::auto_ptr<std::vector<unsigned int> > l1metphi  ( new std::vector<unsigned int>() );
  std::auto_ptr<std::vector<unsigned int> > l1mht     ( new std::vector<unsigned int>() );
  std::auto_ptr<std::vector<unsigned int> > l1mhtphi  ( new std::vector<unsigned int>() );

  //todo: l1 jets, electrons, extra particles

  //ET
  edm::Handle<L1GctEtTotalCollection> l1GctEtTotals;
  iEvent.getByLabel(inputTag,l1GctEtTotals);
  for(L1GctEtTotalCollection::const_iterator it = l1GctEtTotals->begin(); it != l1GctEtTotals->end(); ++it) {
    l1et->push_back(it->et());
  }
  
  //HT
  edm::Handle<L1GctEtHadCollection> l1GctEtHads;
  iEvent.getByLabel(inputTag,l1GctEtHads);
  for(L1GctEtHadCollection::const_iterator it = l1GctEtHads->begin(); it != l1GctEtHads->end(); ++it) {
    l1ht->push_back(it->et());
  }

  //MET
  edm::Handle<L1GctEtMissCollection> l1GctEtMisss;
  iEvent.getByLabel(inputTag,l1GctEtMisss);
  for(L1GctEtMissCollection::const_iterator it = l1GctEtMisss->begin(); it != l1GctEtMisss->end(); ++it) {
    l1met->push_back(it->et());
    l1metphi->push_back(it->phi());
  }

  //MHT
  edm::Handle<L1GctHtMissCollection> l1GctHtMisss;
  iEvent.getByLabel(inputTag,l1GctHtMisss);
  for(L1GctHtMissCollection::const_iterator it = l1GctHtMisss->begin(); it != l1GctHtMisss->end(); ++it) {
    l1mht->push_back(it->et());
    l1mhtphi->push_back(it->phi());
  }

  iEvent.put( l1ht,     "l1ht"     );
  iEvent.put( l1et,     "l1et"     );
  iEvent.put( l1met,    "l1met"    );
  iEvent.put( l1metphi, "l1metphi" );
  iEvent.put( l1mht,    "l1mht"    );
  iEvent.put( l1mhtphi, "l1mhtphi" );
  
}
