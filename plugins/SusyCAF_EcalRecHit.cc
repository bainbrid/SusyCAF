#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_EcalRecHit.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "CondFormats/DataRecord/interface/EcalChannelStatusRcd.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "RecoLocalCalo/EcalRecAlgos/interface/EcalSeverityLevelAlgo.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"

SusyCAF_EcalRecHit::SusyCAF_EcalRecHit(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
  Prefix(iConfig.getParameter<std::string>("Prefix")),
  Suffix(iConfig.getParameter<std::string>("Suffix"))
{
  typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<double> > PolarLorentzV;

  produces <bool>                        ( Prefix + "HandleValid"   + Suffix );
  produces <std::vector<PolarLorentzV> > ( Prefix + "P4"            + Suffix );
  produces <std::vector<float> >         ( Prefix + "Time"          + Suffix );
  produces <std::vector<unsigned> >      ( Prefix + "FlagWord"      + Suffix );
  produces <std::vector<int> >           ( Prefix + "SeverityLevel" + Suffix );
  produces <std::vector<unsigned> >      ( Prefix + "DBStatus"      + Suffix ); 
  produces <std::vector<float> >         ( Prefix + "TriggerPrimitiveEt"+Suffix);
}

void SusyCAF_EcalRecHit::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<double> > PolarLorentzV;

  std::auto_ptr<std::vector<PolarLorentzV> > p4(new std::vector<PolarLorentzV>() );
  std::auto_ptr<std::vector<float> >         time          (new std::vector<float>    () );
  std::auto_ptr<std::vector<unsigned> >      flagWord      (new std::vector<unsigned> () );
  std::auto_ptr<std::vector<int> >           severityLevel (new std::vector<int>      () );
  std::auto_ptr<std::vector<unsigned> >      dbStatus      (new std::vector<unsigned> () );
  std::auto_ptr<std::vector<float> >         triggerPrimitiveEt(new std::vector<float> ()  );

  //Examples:  https://twiki.cern.ch/twiki/bin/viewauth/CMS/EcalFirstBeam09Anomalous
  
  edm::Handle<EcalRecHitCollection> collection;  iEvent.getByLabel(inputTag, collection);
  if (collection.isValid()) {
    edm::Handle<EcalTrigPrimDigiCollection> tpDigis; iEvent.getByLabel("ecalDigis:EcalTriggerPrimitives", tpDigis);    
    edm::ESHandle<EcalChannelStatus> channelStatus;   iSetup.get<EcalChannelStatusRcd>().get(channelStatus);
    edm::ESHandle<CaloGeometry> caloGeometry;         iSetup.get<CaloGeometryRecord>().get(caloGeometry);

    for(EcalRecHitCollection::const_iterator it = collection->begin(); it != collection->end(); ++it) {
      const int theSeverityLevel = EcalSeverityLevelAlgo::severityLevel(it->detid(),*collection,*channelStatus);
      const unsigned theDbStatus = channelStatus->find(it->detid())->getStatusCode();

      if (theSeverityLevel >= EcalSeverityLevelAlgo::kWeird || theDbStatus==13 || theDbStatus==14) {
  
  	const GlobalPoint& point = caloGeometry->getPosition(it->detid());
    	const double eta(point.eta()), phi(point.phi()), energy(fabs(it->energy()));
  	
  	p4->push_back(PolarLorentzV(energy/cosh(eta),eta,phi,energy));
  	time->push_back(it->time());
  	flagWord->push_back(it->flags());
  	severityLevel->push_back(theSeverityLevel);
	dbStatus->push_back(theDbStatus);
	if (tpDigis.isValid()) {
	  EcalTrigPrimDigiCollection::const_iterator tp = tpDigis->find( EBDetId(it->detid()).tower() );
	  const float Et = (tp==tpDigis->end() ? -1 : ecalScale_.getTPGInGeV( *tp ) );
	  triggerPrimitiveEt->push_back(Et);
	}
      }  
    }
  }

  iEvent.put( std::auto_ptr<bool>(new bool(collection.isValid())),  Prefix + "HandleValid"   + Suffix );
  iEvent.put( p4,                 Prefix + "P4"                 + Suffix ); 
  iEvent.put( time,               Prefix + "Time"               + Suffix ); 
  iEvent.put( flagWord,           Prefix + "FlagWord"           + Suffix ); 
  iEvent.put( severityLevel,      Prefix + "SeverityLevel"      + Suffix ); 
  iEvent.put( dbStatus,           Prefix + "DBStatus"           + Suffix ); 
  iEvent.put( triggerPrimitiveEt, Prefix + "TriggerPrimitiveEt" + Suffix );
}
