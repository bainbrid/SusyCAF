#include <memory>
#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_EcalDeadChannels.h"

SusyCAF_EcalDeadChannels::SusyCAF_EcalDeadChannels(const edm::ParameterSet& conf) 
  : channelStatus_cache_id(0),
    caloGeometry_cache_id(0),
    caloConstituents_cache_id(0)    
{

  produces <std::vector<PolarLorentzV> > ( "ecalDeadTowerTrigPrimP4" );
  produces <std::vector<unsigned> > ( "ecalDeadTowerNBadXtals" );
  produces <std::vector<unsigned> > ( "ecalDeadTowerMaxStatus" );
  produces <std::vector<int> > ( "ecalDeadTowerTrigPrimFound" );
}


void SusyCAF_EcalDeadChannels::
produce(edm::Event& e, const edm::EventSetup& es) {

  std::auto_ptr<std::vector<unsigned> > nbadxtal(new std::vector<unsigned>());
  std::auto_ptr<std::vector<unsigned> > maxstatus(new std::vector<unsigned>());
  std::auto_ptr<std::vector<PolarLorentzV> > p4(new std::vector<PolarLorentzV>());
  std::auto_ptr<std::vector<int> > tpfound(new std::vector<int>());


  edm::Handle<EcalTrigPrimDigiCollection> tpDigis;  e.getByLabel("ecalDigis:EcalTriggerPrimitives", tpDigis);
  updateBadTowers(es);
  
  for (std::vector<towerInfo>::const_iterator it = badTowers.begin(); it!=badTowers.end(); ++it) {
    float tpEt=0;
    bool found = false;
    if(tpDigis.isValid()) {
      EcalTrigPrimDigiCollection::const_iterator tp = (tpDigis->find(it->id)) ;
      found = tp != tpDigis->end();
      if (found) tpEt = std::max(0.,ecalScale_.getTPGInGeV( tp->compressedEt(), tp->id() )) ;
    }

    p4->push_back( PolarLorentzV( tpEt, it->eta, it->phi, tpEt*cosh(it->eta) ));
    tpfound->push_back(found);
    nbadxtal->push_back(it->nbad);
    maxstatus->push_back(it->maxstatus);
  }

  e.put(p4,       "ecalDeadTowerTrigPrimP4");
  e.put(nbadxtal, "ecalDeadTowerNBadXtals");
  e.put(maxstatus,"ecalDeadTowerMaxStatus");
  e.put(tpfound,  "ecalDeadTowerTrigPrimFound");
}


void SusyCAF_EcalDeadChannels::
updateBadTowers(const edm::EventSetup& es) {
  const uint32_t status_id = es.get<EcalChannelStatusRcd>().cacheIdentifier();
  const uint32_t geom_id = es.get<CaloGeometryRecord>().cacheIdentifier();
  const uint32_t const_id = es.get<IdealGeometryRecord>().cacheIdentifier();

  if ( status_id == channelStatus_cache_id &&
       geom_id == caloGeometry_cache_id &&
       const_id == caloConstituents_cache_id ) return;

  channelStatus_cache_id = status_id;   edm::ESHandle<EcalChannelStatus> channelStatus;    es.get<EcalChannelStatusRcd>().get(channelStatus);
  caloGeometry_cache_id = geom_id;      edm::ESHandle<CaloGeometry> caloGeometry;          es.get<CaloGeometryRecord>().get(caloGeometry);
  caloConstituents_cache_id = const_id; edm::ESHandle<EcalTrigTowerConstituentsMap> ttMap; es.get<IdealGeometryRecord>().get(ttMap);

  std::map<uint32_t,unsigned> nBadXtal, maxStatus;
  std::map<uint32_t,double> sumEta,sumPhi;

  for (int i = 0;i<EBDetId::kSizeForDenseIndexing;++i) {
    EBDetId id = EBDetId::unhashIndex( i );  if (id==EBDetId(0)) continue;
    EcalChannelStatusMap::const_iterator it = channelStatus->getMap().find(id.rawId());
    unsigned status = it == channelStatus->end() ? 0 : it->getStatusCode();
    if (status > 11) {
      const GlobalPoint& point = caloGeometry->getPosition(id);
      uint32_t key = ttMap->towerOf(id); //id.tower().rawId();
      maxStatus[key] = std::max(status,maxStatus[key]);
      nBadXtal[key]++;
      sumEta[key]+=point.eta();
      sumPhi[key]+= 10+point.phi();
    }
  }
  
  badTowers.clear();
  for(std::map<uint32_t,unsigned>::const_iterator it = nBadXtal.begin(); it!=nBadXtal.end(); it++) {
    uint32_t key = it->first;
    badTowers.push_back( towerInfo( key, nBadXtal[key], maxStatus[key], sumEta[key]/nBadXtal[key], sumPhi[key]/nBadXtal[key] - 10)  );
  }
}
