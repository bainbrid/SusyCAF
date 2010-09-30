#ifndef SUSYCAF_ECALDEAD
#define SUSYCAF_ECALDEAD

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

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHit.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"

#include "CondFormats/EcalObjects/interface/EcalChannelStatus.h"
#include "CondFormats/DataRecord/interface/EcalChannelStatusRcd.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"

#include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"
#include "CalibCalorimetry/EcalTPGTools/interface/EcalTPGScale.h"
#include "Geometry/CaloTopology/interface/EcalTrigTowerConstituentsMap.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"

class SusyCAF_EcalDeadChannels : public edm::EDProducer {
 public:
  explicit SusyCAF_EcalDeadChannels(const edm::ParameterSet&);
 private:
  void produce(edm::Event&, const edm::EventSetup& );
  void updateBadTowers(const edm::EventSetup&);

  struct towerInfo {
    towerInfo(uint32_t _id, unsigned _nbad, unsigned _maxStat, double _eta, double _phi)
      : id(_id), nbad(_nbad), maxstatus(_maxStat), eta(_eta), phi(_phi) {}
    uint32_t id;
    unsigned nbad, maxstatus;
    double eta,phi;
  };
  typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<double> > PolarLorentzV;

  std::vector<towerInfo> badTowers;
  EcalTPGScale ecalScale_;

  uint32_t channelStatus_cache_id, caloGeometry_cache_id, caloConstituents_cache_id;
};


#endif
