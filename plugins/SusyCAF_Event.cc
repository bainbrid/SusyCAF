#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_Event.h"
#include "FWCore/Framework/interface/Event.h"

SusyCAF_Event::SusyCAF_Event(const edm::ParameterSet& iConfig) {
  produces <unsigned int> ( "run"   );
  produces <unsigned int> ( "event" );
  produces <unsigned int> ( "ls"    );
}

void SusyCAF_Event::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  std::auto_ptr<unsigned int >  run   ( new unsigned int(iEvent.id().run()        ) );
  std::auto_ptr<unsigned int >  event ( new unsigned int(iEvent.id().event()      ) );
  std::auto_ptr<unsigned int >  ls    ( new unsigned int(iEvent.luminosityBlock() ) );

  iEvent.put( run,   "run"   );
  iEvent.put( event, "event" );
  iEvent.put( ls   , "ls"    );
}
