#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_HcalDeadChannels.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"

#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"

#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "CondFormats/HcalObjects/interface/HcalChannelQuality.h"
#include "CondFormats/DataRecord/interface/HcalChannelQualityRcd.h"

SusyCAF_HcalDeadChannels::SusyCAF_HcalDeadChannels(const edm::ParameterSet& conf) :
  statusMask(conf.getParameter<uint32_t>("StatusMask"))
{
  produces <std::vector<PolarLorentzV> > ("hcalDeadChannelP4");
  produces <std::vector<unsigned> >      ("hcalDeadChannelStatus");
}

void SusyCAF_HcalDeadChannels::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  std::auto_ptr <std::vector<PolarLorentzV> > p4(new std::vector<PolarLorentzV>());
  std::auto_ptr <std::vector<unsigned> >  status(new std::vector<unsigned>());

  //get geometry
  edm::ESHandle<CaloGeometry> caloGeometryHandle;
  iSetup.get<CaloGeometryRecord>().get(caloGeometryHandle);
  const CaloGeometry* caloGeometry = caloGeometryHandle.product();

  //get channel status handle
  edm::ESHandle<HcalChannelQuality> channelQualityHandle;
  iSetup.get<HcalChannelQualityRcd>().get(channelQualityHandle);
  const HcalChannelQuality* channelQuality = channelQualityHandle.product();

  for (uint32_t i = 0; i < HcalDetId::kSizeForDenseIndexing; ++i) {
    HcalDetId id = HcalDetId::detIdFromDenseIndex(i);
    
    //ignore HO etc.
    HcalSubdetector subdet = id.subdet();
    if (subdet!=HcalBarrel && subdet!=HcalEndcap && subdet!=HcalForward) continue;

    uint32_t channelStatus = channelQuality->getValues(id.rawId())->getValue();
    
    if ( channelStatus & statusMask ) {
      const GlobalPoint& point = caloGeometry->getPosition(id);
      p4->push_back( PolarLorentzV(0.0, point.eta(), point.phi(), 0.0));
      status->push_back(channelStatus);
      std::cout << "got one: " << id << std::endl;
    }
  }

  iEvent.put( p4,     "hcalDeadChannelP4");
  iEvent.put( status, "hcalDeadChannelStatus");
}
