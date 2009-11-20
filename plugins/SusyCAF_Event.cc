#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_Event.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "FWCore/Framework/interface/Event.h"

SusyCAF_Event::SusyCAF_Event(const edm::ParameterSet& iConfig) : 
inputTag(iConfig.getParameter<edm::InputTag>("InputTag"))
{
  produces <unsigned int> ( "physdeclared");
  produces <unsigned int> ( "run"   );
  produces <unsigned int> ( "event" );
  produces <unsigned int> ( "bunch" );
  produces <unsigned int> ( "ls"    );
  produces <unsigned int> ( "orbit" );
  produces <double>       ( "time" );   
}

void SusyCAF_Event::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {

  std::auto_ptr<unsigned int >  run   ( new unsigned int(iEvent.id().run()        ) );
  std::auto_ptr<unsigned int >  event ( new unsigned int(iEvent.id().event()      ) );
  std::auto_ptr<unsigned int >  ls    ( new unsigned int(iEvent.luminosityBlock() ) );

  edm::Handle<L1GlobalTriggerReadoutRecord> l1GtReadoutRecord;
  iEvent.getByLabel(inputTag, l1GtReadoutRecord);

  L1GlobalTriggerReadoutRecord const* gtrr = l1GtReadoutRecord.product();
  L1GtFdlWord fdlWord 	                   = gtrr->gtFdlWord();
 
//  std::cout << " Physics declared " <<  fdlWord.physicsDeclared() << std::endl;
  
  double sec  = iEvent.time().value() >> 32 ;
  double usec = 0xFFFFFFFF & iEvent.time().value();
  double conv = 1e6;

  std::auto_ptr<unsigned int >  phys_declared ( new unsigned int(fdlWord.physicsDeclared()   ) );
  std::auto_ptr<unsigned int >  bunch         ( new unsigned int(iEvent.bunchCrossing()   ) );
  std::auto_ptr<unsigned int >  orbit 	      ( new unsigned int(iEvent.orbitNumber()     ) );
  std::auto_ptr<double >        time  	      ( new double(sec+usec/conv));

  iEvent.put( phys_declared,"physdeclared");
  iEvent.put( run,   "run"   );
  iEvent.put( event, "event" );
  iEvent.put( ls   , "ls"    );
  iEvent.put( bunch, "bunch" );
  iEvent.put( orbit, "orbit" );
  iEvent.put( time,  "time"  );
}
