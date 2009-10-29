#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_L1Extra.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/L1Trigger/interface/L1EtMissParticle.h"
#include "DataFormats/L1Trigger/interface/L1EtMissParticleFwd.h"

SusyCAF_L1Extra::SusyCAF_L1Extra(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
  Prefix(iConfig.getParameter<std::string>("Prefix")),
  Suffix(iConfig.getParameter<std::string>("Suffix"))
{
  produces <std::vector<double> > ( Prefix + "ht"         + Suffix);
  produces <std::vector<double> > ( Prefix + "et"         + Suffix);
  produces <std::vector<double> > ( Prefix + "met"        + Suffix);
  produces <std::vector<double> > ( Prefix + "metphi"     + Suffix);
  produces <std::vector<double> > ( Prefix + "mht"        + Suffix);
  produces <std::vector<double> > ( Prefix + "mhtphi"     + Suffix);
}

void SusyCAF_L1Extra::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  std::auto_ptr<std::vector<double> > ht      ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > et      ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > met     ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > metphi  ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > mht     ( new std::vector<double>() );
  std::auto_ptr<std::vector<double> > mhtphi  ( new std::vector<double>() );

  //todo (possibly):
  //include the rest of the extra collections (see UserCode/L1TriggerDPG)
  //use type instead of label to distinguish between ET and HT
  //use floats instead of doubles

  //MET
  edm::Handle<l1extra::L1EtMissParticleCollection> l1EtMisss;
  iEvent.getByLabel(inputTag.label(),"MET",l1EtMisss);
  for(l1extra::L1EtMissParticleCollection::const_iterator it = l1EtMisss->begin(); it != l1EtMisss->end(); ++it) {
    et->push_back(it->etTotal());
    met->push_back(it->et());
    metphi->push_back(it->phi());
  }
  
  //MHT
  edm::Handle<l1extra::L1EtMissParticleCollection> l1HtMisss;
  iEvent.getByLabel(inputTag.label(),"MHT",l1HtMisss);
  for(l1extra::L1EtMissParticleCollection::const_iterator it = l1HtMisss->begin(); it != l1HtMisss->end(); ++it) {
    ht->push_back(it->etTotal());
    mht->push_back(it->et());
    mhtphi->push_back(it->phi());
  }

  iEvent.put( ht,     Prefix + "ht"         + Suffix);
  iEvent.put( et,     Prefix + "et"         + Suffix);
  iEvent.put( met,    Prefix + "met"        + Suffix);
  iEvent.put( metphi, Prefix + "metphi"     + Suffix);
  iEvent.put( mht,    Prefix + "mht"        + Suffix);
  iEvent.put( mhtphi, Prefix + "mhtphi"     + Suffix);
  
}
