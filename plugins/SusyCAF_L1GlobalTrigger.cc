#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_L1GlobalTrigger.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"

SusyCAF_L1GlobalTrigger::SusyCAF_L1GlobalTrigger(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
  nBxOutput(iConfig.getParameter<int>         ("NBxOutput"))
{
  //details here: https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideL1TriggerFAQ

  produces <unsigned int>       ( "bx"         );
  produces <std::vector<bool> > ( "l1physbits" );
  produces <std::vector<bool> > ( "l1techbits" );

  if (nBxOutput==3) {
    produces <std::vector<bool> > ( "l1physbitsm1" );
    produces <std::vector<bool> > ( "l1techbitsm1" );
    produces <std::vector<bool> > ( "l1physbitsp1" );
    produces <std::vector<bool> > ( "l1techbitsp1" );
  }

}

void SusyCAF_L1GlobalTrigger::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  std::auto_ptr<unsigned int>       bx           ( new unsigned int() );
  std::auto_ptr<std::vector<bool> > l1physbits   ( new std::vector<bool>() );
  std::auto_ptr<std::vector<bool> > l1techbits   ( new std::vector<bool>() );
  std::auto_ptr<std::vector<bool> > l1physbitsm1 ( new std::vector<bool>() );
  std::auto_ptr<std::vector<bool> > l1techbitsm1 ( new std::vector<bool>() );
  std::auto_ptr<std::vector<bool> > l1physbitsp1 ( new std::vector<bool>() );
  std::auto_ptr<std::vector<bool> > l1techbitsp1 ( new std::vector<bool>() );

  //contains decision words before masks
  edm::Handle<L1GlobalTriggerReadoutRecord> l1GtReadoutRecord;
  iEvent.getByLabel(inputTag, l1GtReadoutRecord);

  *bx.get()=l1GtReadoutRecord->gtfeWord().bxNr();
  *l1physbits.get()=l1GtReadoutRecord->decisionWord();
  *l1techbits.get()=l1GtReadoutRecord->technicalTriggerWord();

  iEvent.put( bx,         "bx"         );
  iEvent.put( l1physbits, "l1physbits" );
  iEvent.put( l1techbits, "l1techbits" );
  
  if (nBxOutput==3 && l1GtReadoutRecord->gtFdlVector().size()>=3) {
    *l1physbitsm1.get()=l1GtReadoutRecord->decisionWord(-1);
    *l1techbitsm1.get()=l1GtReadoutRecord->technicalTriggerWord(-1);
    *l1physbitsp1.get()=l1GtReadoutRecord->decisionWord(1);
    *l1techbitsp1.get()=l1GtReadoutRecord->technicalTriggerWord(1);

    iEvent.put( l1physbitsm1, "l1physbitsm1" );
    iEvent.put( l1techbitsm1, "l1techbitsm1" );
    iEvent.put( l1physbitsp1, "l1physbitsp1" );
    iEvent.put( l1techbitsp1, "l1techbitsp1" );
  }

}
