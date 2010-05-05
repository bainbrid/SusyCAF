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

SusyCAF_EcalRecHit::SusyCAF_EcalRecHit(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
  Prefix(iConfig.getParameter<std::string>("Prefix")),
  Suffix(iConfig.getParameter<std::string>("Suffix"))
{
  produces <bool>                                         ( Prefix + "HandleValid"   + Suffix );
  produces <std::vector<float> >                          ( Prefix + "Time"          + Suffix );
  produces <std::vector<unsigned> >                       ( Prefix + "FlagWord"      + Suffix );
  produces <std::vector<int> >                            ( Prefix + "SeverityLevel" + Suffix );
  produces <std::vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<double> > > > ( Prefix + "P4" + Suffix );
}

void SusyCAF_EcalRecHit::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  std::auto_ptr<std::vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<double> > > > p4(new std::vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<double> > >() );
  std::auto_ptr<std::vector<float> >                          time          (new std::vector<float>    () );
  std::auto_ptr<std::vector<unsigned> >                       flagWord      (new std::vector<unsigned> () );
  std::auto_ptr<std::vector<int> >                            severityLevel (new std::vector<int>      () );

  ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<double> > thisP4(0.0,0.0,0.0,0.0);  

  //followed this example
  //https://twiki.cern.ch/twiki/bin/viewauth/CMS/EcalFirstBeam09Anomalous
  
  //get rechits
  edm::Handle<EcalRecHitCollection> collection;
  iEvent.getByLabel(inputTag, collection);
  
  std::auto_ptr<bool> isHandleValid ( new bool(collection.isValid()) );
  if (collection.isValid()) {
    const EcalRecHitCollection* ecalRecHits=collection.product();
    
    edm::ESHandle<EcalChannelStatus> channelStatusHandle;
    iSetup.get<EcalChannelStatusRcd>().get(channelStatusHandle);
    const EcalChannelStatus* channelStatus = channelStatusHandle.product();
    
    edm::ESHandle<CaloGeometry> caloGeometryHandle;
    iSetup.get<CaloGeometryRecord>().get(caloGeometryHandle);
    const CaloGeometry* caloGeometry = caloGeometryHandle.product();
    
    //loop over rechits
    for(EcalRecHitCollection::const_iterator it = collection->begin(); it != collection->end(); ++it) {
      int theSeverityLevel=EcalSeverityLevelAlgo::severityLevel(it->detid(),*ecalRecHits,*channelStatus);
      if (theSeverityLevel>=EcalSeverityLevelAlgo::kWeird) {
  
  	const GlobalPoint& point=caloGeometry->getPosition(it->detid());
  	//std::cout << point << std::endl;
  	double eta=point.eta();
  	double phi=point.phi();
  	double energy=fabs(it->energy());//absolute value
  	
  	thisP4.SetCoordinates(energy/cosh(eta),eta,phi,energy);
  	//std::cout 
	//  << "pT:  " << energy/cosh(eta) << " " << thisP4.pt()  << std::endl
	//  << "eta: " << eta     << " " << thisP4.eta() << std::endl
	//  << "phi: " << phi     << " " << thisP4.phi() << std::endl
	//  << "e:   " << energy  << " " << thisP4.e()   << std::endl;
  	p4->push_back(thisP4);
  	time->push_back(it->time());
  	flagWord->push_back(it->flags());
  	severityLevel->push_back(theSeverityLevel);
      }
  
    } //end loop over rechits
  }//end if handle valid

  iEvent.put( isHandleValid,  Prefix + "HandleValid"   + Suffix );
  iEvent.put( p4,             Prefix + "P4"            + Suffix ); 
  iEvent.put( time,           Prefix + "Time"          + Suffix ); 
  iEvent.put( flagWord,       Prefix + "FlagWord"      + Suffix ); 
  iEvent.put( severityLevel,  Prefix + "SeverityLevel" + Suffix ); 
}
