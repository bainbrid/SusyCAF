#ifndef SUSY_CAF_HCALRECHIT
#define SUSY_CAF_HCALRECHIT

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "CalibCalorimetry/HcalAlgos/interface/HcalLogicalMapGenerator.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "TMath.h"

template< typename T >
class SusyCAF_HcalRecHit : public edm::EDProducer {
 public: 
  explicit SusyCAF_HcalRecHit(const edm::ParameterSet&);
  ~SusyCAF_HcalRecHit();
 private: 
  void produce(edm::Event &, const edm::EventSetup & );
  void setupCrudeGeometry();
  const edm::InputTag inputTag;
  const std::string Prefix,Suffix;
  bool outputAllRecHits;

  //workaround for a bug in DataFormats/HcalDetId/HcalFrontEndId
  //static const int rbxBitShift=18;//for CMSSW_3_3_0_pre2 and later
  static const int rbxBitShift=17;//for CMSSW_3_3_0_pre1 and earlier
  static const int maxRbxIndex=0xFF;
  static const int maxRmIndex=0x3FF;
  int rbxIndex(const HcalFrontEndId& hFeid) const {return (hFeid.rawId()>>rbxBitShift)&maxRbxIndex;}
  int rmIndex (const HcalFrontEndId& hFeid) const {return ((hFeid.rm()-1)&0x3)+(rbxIndex(hFeid)<<2);}
  //end workaround

  HcalLogicalMap *logicalMap;
  double rbxEnergies[maxRbxIndex+1]; //energy sum for each readout box
  double rmEnergies  [maxRmIndex+1]; //energy sum for each readout module

  //for crude geometry
  static const int nEtaAbs=42; //41+1
  static const int nPhi=73; //72+1
  double etaabs[nEtaAbs];
  double phi[nPhi];

};

template< typename T >
SusyCAF_HcalRecHit<T>::SusyCAF_HcalRecHit(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
  Prefix(iConfig.getParameter<std::string>("Prefix")),
  Suffix(iConfig.getParameter<std::string>("Suffix")),
  outputAllRecHits(iConfig.getParameter<bool>("OutputAllRecHits"))
{
  produces <float>                ( Prefix + "etMax"    + Suffix );
  produces <float>                ( Prefix + "tMax"     + Suffix );
  produces <int>                  ( Prefix + "ietaMax"  + Suffix );
  produces <int>                  ( Prefix + "iphiMax"  + Suffix );
  produces <int>                  ( Prefix + "depthMax" + Suffix );

  produces <int>                  ( Prefix + "rbxcount" + Suffix );
  produces <int>                  ( Prefix + "rmcount"  + Suffix );
  produces <std::vector<double> > ( Prefix + "rbxE"     + Suffix );
  produces <std::vector<double> > ( Prefix + "rmE"      + Suffix );

  produces <std::vector<float> >  ( Prefix + "et"       + Suffix );
  produces <std::vector<int> >    ( Prefix + "ietaabs"  + Suffix );

  HcalLogicalMapGenerator gen;
  logicalMap=new HcalLogicalMap(gen.createMap());
  
  setupCrudeGeometry();
}

template< typename T >
SusyCAF_HcalRecHit<T>::~SusyCAF_HcalRecHit()
{
  delete logicalMap;
}

template< typename T >
void SusyCAF_HcalRecHit<T>::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  std::auto_ptr<float>                etMax     ( new float()               ) ;
  std::auto_ptr<float>                tMax      ( new float()               ) ;
  std::auto_ptr<int>                  ietaMax   ( new int()                 ) ;
  std::auto_ptr<int>                  iphiMax   ( new int()                 ) ;
  std::auto_ptr<int>                  depthMax  ( new int()                 ) ;

  std::auto_ptr<int>                  rbxcount  ( new int()                 ) ;
  std::auto_ptr<int>                  rmcount   ( new int()                 ) ;
  std::auto_ptr<std::vector<double> > rbxE      ( new std::vector<double>() ) ;
  std::auto_ptr<std::vector<double> > rmE       ( new std::vector<double>() ) ;

  std::auto_ptr<std::vector<float> >  et        ( new std::vector<float>()  ) ;
  std::auto_ptr<std::vector<int> >    ietaabs   ( new std::vector<int>  ()  ) ;

  for (int iRbx=0;iRbx<=maxRbxIndex;iRbx++) rbxEnergies[iRbx]=0.0;
  for (int iRm=0;iRm<=maxRmIndex;iRm++) rmEnergies[iRm]=0.0;
  
  edm::Handle<T> hcalrechitcollection;
  iEvent.getByLabel(inputTag, hcalrechitcollection);

  float etMaxLocal=-1000.0;
  typename T::const_iterator itMax;

  for(typename T::const_iterator it = hcalrechitcollection->begin(); it != hcalrechitcollection->end(); ++it) {
    const float energy=it->energy();
    const int iEtaAbsLocal=it->id().ietaAbs();
    const float etLocal=energy/cosh(etaabs[iEtaAbsLocal]);

    if (etLocal>etMaxLocal) {
      etMaxLocal=etLocal;
      itMax=it;
    }

    if (outputAllRecHits && iEtaAbsLocal<15) {
      et->push_back(etLocal);
      ietaabs->push_back(iEtaAbsLocal);
    }

    const HcalFrontEndId& hFeid=logicalMap->getHcalFrontEndId(it->detid());
    int rbxIndexValue=rbxIndex(hFeid);
    int rmIndexValue=rmIndex(hFeid);
    rbxEnergies[rbxIndexValue]+=energy;
    rmEnergies  [rmIndexValue]+=energy;
    //std::cout 
    //  << hFeid.rbx() << " " << hFeid.rm() 
    //  << " has rbxIndex=" << rbxIndexValue 
    //  << " and  rmIndex=" << rmIndexValue 
    //  << std::endl;
  }

  int rbxCount=0;
  double rbxThreshold=15.0; //GeV
  for (int iRbx=0;iRbx<=maxRbxIndex;iRbx++) {
    if (rbxEnergies[iRbx]>rbxThreshold) {
      //HcalFrontEndId hFeid(iRbx<<rbxBitShift);
      //std::cout << iRbx << " " << hFeid.rbx() << std::endl;
      rbxE->push_back(rbxEnergies[iRbx]);
      rbxCount++;
    }
  }
  *rbxcount.get()=rbxCount;

  int rmCount=0;
  double rmThreshold=15.0; //GeV
  for (int iRm=0;iRm<=maxRmIndex;iRm++) {
    if (rmEnergies[iRm]>rmThreshold) {
      rmCount++;
      rmE->push_back(rmEnergies[iRm]);
    }
  }
  *rmcount.get()=rmCount;

  //std::cout << Suffix << " rbxCount=" << rbxCount << "; rmCount=" << rmCount << std::endl;

  if (etMaxLocal>-1000.0) {
    *etMax.get()=etMaxLocal;
    *tMax.get()=itMax->time();
    *ietaMax.get()=itMax->id().ieta();
    *iphiMax.get()=itMax->id().iphi();
    *depthMax.get()=itMax->id().depth();
  }
  else {  //dummy values
    *etMax.get()=-1000.0;
    *tMax.get()=-1000.0;
    *ietaMax.get() =-100;
    *iphiMax.get() =-100;
    *depthMax.get()=-100;
  }

  iEvent.put( etMax     , Prefix + "etMax"    + Suffix );
  iEvent.put( tMax      , Prefix + "tMax"     + Suffix );
  iEvent.put( ietaMax   , Prefix + "ietaMax"  + Suffix );
  iEvent.put( iphiMax   , Prefix + "iphiMax"  + Suffix );
  iEvent.put( depthMax  , Prefix + "depthMax" + Suffix );

  iEvent.put( rbxcount  , Prefix + "rbxcount" + Suffix );
  iEvent.put( rmcount   , Prefix + "rmcount"  + Suffix );
  iEvent.put( rbxE      , Prefix + "rbxE"     + Suffix );
  iEvent.put( rmE       , Prefix + "rmE"      + Suffix );

  iEvent.put( et        , Prefix + "et"       + Suffix );
  iEvent.put( ietaabs   , Prefix + "ietaabs"  + Suffix );
}

template< typename T >
void SusyCAF_HcalRecHit<T>::setupCrudeGeometry() {
  //from http://www.hep.wisc.edu/cms/trig/RCTDocu/towers_ieta_iphi.pdf

  phi[0]=0.0; //iPhi=0 not defined
  for (int iPhi=1;iPhi<nPhi;iPhi++) {
    phi[iPhi]=2.0*TMath::Pi()*(iPhi-1.0)/nPhi;
    if (phi[iPhi]>TMath::Pi()) phi[iPhi]-=2.0*TMath::Pi();
  }

  etaabs[ 0]=0.0; //iEta=0 not defined

  //numbers from CMS NOTE 2005/016 (Sunanda Banerjee)
  etaabs[ 1]=(0.000 + 0.087)/2.0; //HB
  etaabs[ 2]=(0.087 + 0.174)/2.0; //HB
  etaabs[ 3]=(0.174 + 0.261)/2.0; //HB
  etaabs[ 4]=(0.261 + 0.348)/2.0; //HB
  etaabs[ 5]=(0.348 + 0.435)/2.0; //HB
  etaabs[ 6]=(0.435 + 0.522)/2.0; //HB
  etaabs[ 7]=(0.522 + 0.609)/2.0; //HB
  etaabs[ 8]=(0.609 + 0.696)/2.0; //HB
  etaabs[ 9]=(0.696 + 0.783)/2.0; //HB
  etaabs[10]=(0.783 + 0.870)/2.0; //HB
  etaabs[11]=(0.879 + 0.957)/2.0; //HB
  etaabs[12]=(0.957 + 1.044)/2.0; //HB
  etaabs[13]=(1.044 + 1.131)/2.0; //HB
  etaabs[14]=(1.131 + 1.218)/2.0; //HB
  etaabs[15]=(1.218 + 1.305)/2.0; //HB
  etaabs[16]=(1.305 + 1.392)/2.0; //HB
  etaabs[17]=(1.392 + 1.479)/2.0; //HE
  etaabs[18]=(1.479 + 1.566)/2.0; //HE
  etaabs[19]=(1.566 + 1.653)/2.0; //HE
  etaabs[20]=(1.653 + 1.740)/2.0; //HE
  etaabs[21]=(1.740 + 1.830)/2.0; //HE
  etaabs[22]=(1.830 + 1.930)/2.0; //HE
  etaabs[23]=(1.930 + 2.043)/2.0; //HE
  etaabs[24]=(2.043 + 2.172)/2.0; //HE
  etaabs[25]=(2.172 + 2.322)/2.0; //HE
  etaabs[26]=(2.322 + 2.500)/2.0; //HE
  etaabs[27]=(2.500 + 2.650)/2.0; //HE
  etaabs[28]=(2.650 + 3.000)/2.0; //HE
  etaabs[29]=(2.853 + 2.964)/2.0; //HF
  etaabs[30]=(2.964 + 3.139)/2.0; //HF
  etaabs[31]=(3.139 + 3.314)/2.0; //HF
  etaabs[32]=(3.314 + 3.489)/2.0; //HF
  etaabs[33]=(3.489 + 3.664)/2.0; //HF
  etaabs[34]=(3.664 + 3.839)/2.0; //HF
  etaabs[35]=(3.839 + 4.013)/2.0; //HF
  etaabs[36]=(4.013 + 4.191)/2.0; //HF
  etaabs[37]=(4.191 + 4.363)/2.0; //HF
  etaabs[38]=(4.363 + 4.538)/2.0; //HF
  etaabs[39]=(4.538 + 4.716)/2.0; //HF
  etaabs[40]=(4.716 + 4.889)/2.0; //HF
  etaabs[41]=(4.889 + 5.191)/2.0; //HF
}


#endif
