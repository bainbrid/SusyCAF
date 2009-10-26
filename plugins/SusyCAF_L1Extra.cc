#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_L1Extra.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/L1Trigger/interface/L1EtMissParticle.h"
#include "DataFormats/L1Trigger/interface/L1EtMissParticleFwd.h"

SusyCAF_L1Extra::SusyCAF_L1Extra(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag"))
{
  produces <std::vector<double> > ( "l1ht"     );
  produces <std::vector<double> > ( "l1et"     );
  produces <std::vector<double> > ( "l1met"    );
  produces <std::vector<double> > ( "l1metphi" );
  produces <std::vector<double> > ( "l1mht"    );
  produces <std::vector<double> > ( "l1mhtphi" );
}

void SusyCAF_L1Extra::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  std::auto_ptr<std::vector<double> > l1ht      ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > l1et      ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > l1met     ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > l1metphi  ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > l1mht     ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > l1mhtphi  ( new std::vector<double>() );

  //todo (possibly):
  //include the rest of the extra collections (see UserCode/L1TriggerDPG)
  //use type instead of label to distinguish between ET and HT
  //use floats instead of doubles

  //MET
  edm::Handle<l1extra::L1EtMissParticleCollection> l1EtMisss;
  iEvent.getByLabel(inputTag.label(),"MET",l1EtMisss);
  for(l1extra::L1EtMissParticleCollection::const_iterator it = l1EtMisss->begin(); it != l1EtMisss->end(); ++it) {
    l1et->push_back(it->etTotal());
    l1met->push_back(it->et());
    l1metphi->push_back(it->phi());
  }
  
  //MHT
  edm::Handle<l1extra::L1EtMissParticleCollection> l1HtMisss;
  iEvent.getByLabel(inputTag.label(),"MHT",l1HtMisss);
  for(l1extra::L1EtMissParticleCollection::const_iterator it = l1HtMisss->begin(); it != l1HtMisss->end(); ++it) {
    l1ht->push_back(it->etTotal());
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
