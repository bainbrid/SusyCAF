#ifndef SUSY_CAF_PHOTON
#define SUSY_CAF_PHOTON

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"

#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/PatCandidates/interface/Photon.h"

#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterTools.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "RecoCaloTools/MetaCollections/interface/CaloRecHitMetaCollections.h"
#include "RecoCaloTools/Selectors/interface/CaloConeSelector.h"
#include "MyAnalysis/IsolationTools/interface/SuperClusterHitsEcalIsolation.h"

#include <Math/ProbFuncMathCore.h>
#include <Math/VectorUtil.h>

template< typename T >
class SusyCAF_Photon : public edm::EDProducer 
{
public: 
  explicit SusyCAF_Photon(const edm::ParameterSet&);

private: 
  void initTemplate();
  void initRECO();
  void initPAT();
  void initExtra();
  void produce(edm::Event &, const edm::EventSetup & );
  void produceTemplate(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<reco::Photon> > &);
  void produceTemplate(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<pat::Photon> > &);
  void produceRECO(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &);
  void producePAT(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &);
  void produceExtra(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &);

  void produceExtraTrackVars(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &);
  void produceExtraSuperClusterVars(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &);
  void produceExtraCaloIsoVars(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &);
  double hcalEnergy(const CaloGeometry* geometry,
		    const HBHERecHitMetaCollection& mHbhe,
		    reco::SuperClusterRef& sc,
		    typename std::vector<T>::const_iterator it,
		    double coneSize);

  double ebEeBoundary() const {return 1.479;}

  const edm::InputTag   inputTag;
  const std::string     prefix,suffix;

  const bool produceExtraVars;
  const edm::InputTag trackTag;
  const std::string ecalRecHitProducer;
  const std::string ebRecHitCollection;
  const std::string eeRecHitCollection;
  const std::string hbheRecHitCollection;

  typedef reco::Candidate::LorentzVector  LorentzVector;
  typedef reco::Candidate::Vector         Vector;
  typedef reco::Candidate::Point          Point;
};

template< typename T >
SusyCAF_Photon<T>::SusyCAF_Photon(const edm::ParameterSet& iConfig) 
  : inputTag(iConfig.getParameter<edm::InputTag>("InputTag"))
  , prefix  (iConfig.getParameter<std::string>  ("Prefix"  ))
  , suffix  (iConfig.getParameter<std::string>  ("Suffix"  ))

  , produceExtraVars(iConfig.getParameter<bool>("ProduceExtraVars"))
  , trackTag(iConfig.getParameter<edm::InputTag>("TrackTag"))
  , ecalRecHitProducer(iConfig.getParameter<std::string>("EcalRecHitProducer"))
  , ebRecHitCollection(iConfig.getParameter<std::string>("EbRecHitCollection"))
  , eeRecHitCollection(iConfig.getParameter<std::string>("EeRecHitCollection"))
  , hbheRecHitCollection(iConfig.getParameter<std::string>("HbheRecHitCollection"))
{
  initTemplate();
}


template< typename T >
void SusyCAF_Photon<T>::initRECO()
{
  produces <bool                        >(prefix + "HandleValid"          + suffix);
  produces <std::vector<LorentzVector > >(prefix + "P4"                   + suffix);
  produces <std::vector<Point         > >(prefix + "CaloPosition"         + suffix);
  produces <std::vector<float         > >(prefix + "HadronicDepth1OverEm" + suffix);
  produces <std::vector<float         > >(prefix + "HadronicDepth2OverEm" + suffix);
  produces <std::vector<float         > >(prefix + "HadronicOverEm"       + suffix);
  produces <std::vector<int           > >(prefix + "HasPixelSeed"         + suffix);
  produces <std::vector<int           > >(prefix + "IsEB"                 + suffix);
  produces <std::vector<int           > >(prefix + "IsEE"                 + suffix);
  produces <std::vector<int           > >(prefix + "IsEBGap"              + suffix);
  produces <std::vector<int           > >(prefix + "IsEEGap"              + suffix);
  produces <std::vector<int           > >(prefix + "IsEBEEGap"            + suffix);
  produces <std::vector<float> >  (prefix + "TrkSumPtHollowConeDR04"     + suffix);
  produces <std::vector<float> >  (prefix + "EcalRecHitEtConeDR04"       + suffix);
  produces <std::vector<float> >  (prefix + "HcalTowSumEtConeDR04"       + suffix);
  produces <std::vector<float> >  (prefix + "HcalDepth1TowSumEtConeDR04" + suffix);
  produces <std::vector<float> >  (prefix + "HcalDepth2TowSumEtConeDR04" + suffix);
  produces <std::vector<float> >  (prefix + "R9"   + suffix);
  produces <std::vector<float> >  (prefix + "e1x5" + suffix);
  produces <std::vector<float> >  (prefix + "e2x5" + suffix);
  produces <std::vector<float> >  (prefix + "e3x3" + suffix);
  produces <std::vector<float> >  (prefix + "e5x5" + suffix);
  produces <std::vector<double> > (prefix + "SuperClusterEnergy" + suffix);
  produces <std::vector<Point> >  (prefix + "SuperClusterPos" + suffix);
  produces <std::vector<double> > (prefix + "SuperClusterEtaWidth" + suffix);
  produces <std::vector<double> > (prefix + "SuperClusterPhiWidth" + suffix);

  produces <std::vector<int   > >(prefix + "NConversions"         + suffix);
  produces <std::vector<float > >(prefix + "AllConversionTracksSumPt" + suffix);
  produces <std::vector<Vector> >(prefix + "BestConversionTrack0P3" + suffix);
  produces <std::vector<Vector> >(prefix + "BestConversionTrack1P3" + suffix);
  produces <std::vector<Point > >(prefix + "BestConversionVertex" + suffix);
  produces <std::vector<float > >(prefix + "BestConversionEoverP" + suffix);
  produces <std::vector<float > >(prefix + "BestConversionMass"   + suffix);

}

template< typename T >
void SusyCAF_Photon<T>::initPAT()
{
  produces <std::vector<int> >  (prefix + "IDLoose" + suffix);
  produces <std::vector<int> >  (prefix + "IDTight" + suffix);
  produces <std::vector<float> >(prefix + "TrkIso"  + suffix);
  produces <std::vector<float> >(prefix + "CaloIso"       + suffix);
  produces <std::vector<float> >(prefix + "EcalIso"       + suffix);
  produces <std::vector<float> >(prefix + "HcalIso"       + suffix);
  produces <std::vector<float> >(prefix + "SigmaEtaEta"   + suffix);
  produces <std::vector<float> >(prefix + "SigmaIetaIeta" + suffix);
}

template< typename T >
void SusyCAF_Photon<T>::initExtra()
{
  if (!produceExtraVars) return;

  produces <std::vector<float> >  (prefix + "ExtraTrkIso0015" + suffix);
  produces <std::vector<float> >  (prefix + "ExtraTrkIso035"  + suffix);
  produces <std::vector<float> >  (prefix + "ExtraTrkIso04"   + suffix);
  produces <std::vector<float> >  (prefix + "ExtraTrkIso05"   + suffix);
  produces <std::vector<float> >  (prefix + "ExtraTrkIso07"   + suffix);
  produces <std::vector<float> >  (prefix + "ExtraTrkIso1"    + suffix);

  produces <std::vector<int> >    (prefix + "ExtraNTrk0015"   + suffix);
  produces <std::vector<int> >    (prefix + "ExtraNTrk035"    + suffix);
  produces <std::vector<int> >    (prefix + "ExtraNTrk04"     + suffix);
  produces <std::vector<int> >    (prefix + "ExtraNTrk05"     + suffix);
  produces <std::vector<int> >    (prefix + "ExtraNTrk07"     + suffix);
  produces <std::vector<int> >    (prefix + "ExtraNTrk1"      + suffix);

  produces <std::vector<double> > (prefix + "SuperClusterMajorMajor" + suffix);
  produces <std::vector<double> > (prefix + "SuperClusterMinorMinor" + suffix);

  produces <std::vector<double> > (prefix + "ExtraHcalOverEcal01"  + suffix);
  produces <std::vector<double> > (prefix + "ExtraHcalOverEcal015" + suffix);
  produces <std::vector<double> > (prefix + "ExtraHcalOverEcal04"  + suffix);
  produces <std::vector<double> > (prefix + "ExtraHcalOverEcal05"  + suffix);
  produces <std::vector<double> > (prefix + "ExtraHcalOverEcal07"  + suffix);
  produces <std::vector<double> > (prefix + "ExtraHcalOverEcal1"   + suffix);

  produces <std::vector<double> > (prefix + "ExtraEcalIso01"  + suffix);
  produces <std::vector<double> > (prefix + "ExtraEcalIso015" + suffix);
  produces <std::vector<double> > (prefix + "ExtraEcalIso04"  + suffix);
  produces <std::vector<double> > (prefix + "ExtraEcalIso05"  + suffix);
  produces <std::vector<double> > (prefix + "ExtraEcalIso07"  + suffix);
  produces <std::vector<double> > (prefix + "ExtraEcalIso1"   + suffix);

}

template< typename T >
void SusyCAF_Photon<T>::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) 
{
  edm::Handle<std::vector<T> > collection;
  iEvent.getByLabel(inputTag,collection);
  produceTemplate(iEvent, iSetup, collection);
}
// produce method in case of RECO data
template< typename T >
void SusyCAF_Photon<T>::produceTemplate(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<reco::Photon> >& collection) {
  produceRECO (iEvent, iSetup, collection);
  produceExtra(iEvent, iSetup, collection);
}
// produce method in case of PAT data
template< typename T >
void SusyCAF_Photon<T>::produceTemplate(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<pat::Photon> >& collection) {
  produceRECO (iEvent, iSetup, collection);
  produceExtra(iEvent, iSetup, collection);
  producePAT  (iEvent, iSetup, collection);
}

template< typename T >
void SusyCAF_Photon<T>::
produceRECO(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<T> >& collection) 
{
  std::auto_ptr<bool                        > isHandleValid       ( new bool(collection.isValid())    );
  std::auto_ptr<std::vector<LorentzVector > > p4                  ( new std::vector<LorentzVector >() );
  std::auto_ptr<std::vector<Point> > caloPosition        ( new std::vector<Point>() );
  std::auto_ptr<std::vector<float> > hadronicDepth1OverEm( new std::vector<float>() );
  std::auto_ptr<std::vector<float> > hadronicDepth2OverEm( new std::vector<float>() );
  std::auto_ptr<std::vector<float> > hadronicOverEm      ( new std::vector<float>() );
  std::auto_ptr<std::vector<int  > > hasPixelSeed        ( new std::vector<int  >() );
  std::auto_ptr<std::vector<int  > > isEB                ( new std::vector<int  >() );
  std::auto_ptr<std::vector<int  > > isEE                ( new std::vector<int  >() );
  std::auto_ptr<std::vector<int  > > isEBGap             ( new std::vector<int  >() );
  std::auto_ptr<std::vector<int  > > isEEGap             ( new std::vector<int  >() );
  std::auto_ptr<std::vector<int  > > isEBEEGap           ( new std::vector<int  >() );

  std::auto_ptr<std::vector<float> > trkSumPtHolConeDR04 (new std::vector<float>());
  std::auto_ptr<std::vector<float> > EcalrechitEtConeDR04 (new std::vector<float>());
  std::auto_ptr<std::vector<float> > Hcal       (new std::vector<float>());
  std::auto_ptr<std::vector<float> > HcalDepth1 (new std::vector<float>());
  std::auto_ptr<std::vector<float> > HcalDepth2 (new std::vector<float>());
  std::auto_ptr<std::vector<float> > R9   (new std::vector<float>());
  std::auto_ptr<std::vector<float> > e1x5 (new std::vector<float>());
  std::auto_ptr<std::vector<float> > e2x5 (new std::vector<float>());
  std::auto_ptr<std::vector<float> > e3x3 (new std::vector<float>());
  std::auto_ptr<std::vector<float> > e5x5 (new std::vector<float>());
  std::auto_ptr<std::vector<double> > SCenergy   (new std::vector<double>());
  std::auto_ptr<std::vector<Point> >  SCpoint    (new std::vector<Point>());
  std::auto_ptr<std::vector<double> > SCetaWidth (new std::vector<double>());
  std::auto_ptr<std::vector<double> > SCphiWidth (new std::vector<double>());

  std::auto_ptr<std::vector<int  > > nConversions        ( new std::vector<int  >() );
  std::auto_ptr<std::vector<float  > > allConversionTracksSumPt ( new std::vector<float  >() );
  std::auto_ptr<std::vector<Vector > > bestConvTrack0P3   ( new std::vector<Vector >() );
  std::auto_ptr<std::vector<Vector > > bestConvTrack1P3   ( new std::vector<Vector >() );
  std::auto_ptr<std::vector<Point  > > bestConvVertex     ( new std::vector<Point >() );
  std::auto_ptr<std::vector<float  > > bestConvEoverP     ( new std::vector<float >() ); 
  std::auto_ptr<std::vector<float  > > bestConvMass       ( new std::vector<float >() );

  if (collection.isValid()) {
    for (typename std::vector<T>::const_iterator it = collection->begin(); 
	 it != collection->end(); ++it) {
      const reco::Photon& photon = *it;
      p4                  ->push_back(photon.p4                   ());
      caloPosition        ->push_back(photon.caloPosition         ());
      hadronicDepth1OverEm->push_back(photon.hadronicDepth1OverEm ());
      hadronicDepth2OverEm->push_back(photon.hadronicDepth2OverEm ());
      hadronicOverEm      ->push_back(photon.hadronicOverEm       ());
      hasPixelSeed        ->push_back(photon.hasPixelSeed         ());
      isEB                ->push_back(photon.isEB                 ());
      isEE                ->push_back(photon.isEE                 ());
      isEBGap             ->push_back(photon.isEBGap              ());
      isEEGap             ->push_back(photon.isEEGap              ());
      isEBEEGap           ->push_back(photon.isEBEEGap            ());
      
      trkSumPtHolConeDR04  -> push_back(photon.trkSumPtHollowConeDR04());
      EcalrechitEtConeDR04 -> push_back(photon.ecalRecHitSumEtConeDR04());
      Hcal                 -> push_back(photon.hcalTowerSumEtConeDR04());
      HcalDepth1           -> push_back(photon.hcalDepth1TowerSumEtConeDR04());
      HcalDepth2           -> push_back(photon.hcalDepth2TowerSumEtConeDR04());
      R9   -> push_back(photon.r9());
      e1x5 -> push_back(photon.e1x5());
      e2x5 -> push_back(photon.e2x5());
      e3x3 -> push_back(photon.e3x3());
      e5x5 -> push_back(photon.e5x5());
      
      reco::SuperClusterRef scluster = photon.superCluster();
      SCenergy   -> push_back(scluster->energy());
      SCpoint    -> push_back(scluster->position());
      SCetaWidth -> push_back(scluster->etaWidth());
      SCphiWidth -> push_back(scluster->phiWidth());

      
      reco::ConversionRef bestConv;
      float tracksSumPt = 0;
      unsigned nConv = 0;
      
      reco::ConversionRefVector conversions = photon.conversions();
      for (unsigned int iConv = 0; iConv < conversions.size(); ++iConv) {
	const reco::ConversionRef& conversion = conversions[iConv];
	if  ( conversion->nTracks() != 2) continue;
	std::vector<reco::TrackRef> tracks = conversion->tracks();
	const reco::Vertex&         vertex = conversion->conversionVertex();
	double chi2 = vertex.chi2();
	double ndof = vertex.ndof();
	double dPhi = conversion->dPhiTracksAtVtx();
	double dCotTheta = conversion->pairCotThetaSeparation();
	double chi2Prob = ROOT::Math::chisquared_cdf_c(chi2,ndof);
	// http://cdsweb.cern.ch/record/1279143
	if (! ( ndof &&
		chi2 > 0 &&
		fabs(dPhi) < 0.2 &&
		fabs(dCotTheta) < 0.3 &&
		chi2Prob > 5e-5) ) continue;

	if (bestConv.isNull() || bestConv->EoverP() > conversion->EoverP())
	  bestConv  = conversion;
	tracksSumPt += tracks[0]->pt() ;
	tracksSumPt += tracks[1]->pt() ;
	nConv++;
      } // end loop over conversions
      
      nConversions->push_back(nConv);
      allConversionTracksSumPt->push_back(tracksSumPt);
      bestConvTrack0P3->push_back(bestConv.isNull() ? Vector() : bestConv->tracksPin()[0]);
      bestConvTrack1P3->push_back(bestConv.isNull() ? Vector() : bestConv->tracksPin()[1]);
      bestConvVertex ->push_back(bestConv.isNull() ? Point() : bestConv->conversionVertex().position());
      bestConvEoverP ->push_back(bestConv.isNull() ? 0 : bestConv->EoverP());
      bestConvMass   ->push_back(bestConv.isNull() ? 0 : bestConv->pairInvariantMass());
    }
  }
  
  iEvent.put(isHandleValid           , prefix + "HandleValid"                + suffix);
  iEvent.put(p4                      , prefix + "P4"                         + suffix);
  iEvent.put(caloPosition            , prefix + "CaloPosition"               + suffix);
  iEvent.put(hadronicDepth1OverEm    , prefix + "HadronicDepth1OverEm"       + suffix);
  iEvent.put(hadronicDepth2OverEm    , prefix + "HadronicDepth2OverEm"       + suffix);
  iEvent.put(hadronicOverEm          , prefix + "HadronicOverEm"             + suffix);
  iEvent.put(hasPixelSeed            , prefix + "HasPixelSeed"               + suffix);
  iEvent.put(isEB                    , prefix + "IsEB"                       + suffix);
  iEvent.put(isEE                    , prefix + "IsEE"                       + suffix);
  iEvent.put(isEBGap                 , prefix + "IsEBGap"                    + suffix);
  iEvent.put(isEEGap                 , prefix + "IsEEGap"                    + suffix);
  iEvent.put(isEBEEGap               , prefix + "IsEBEEGap"                  + suffix);
  				     
  iEvent.put(trkSumPtHolConeDR04     , prefix + "TrkSumPtHollowConeDR04"     + suffix);
  iEvent.put(EcalrechitEtConeDR04    , prefix + "EcalRecHitEtConeDR04"       + suffix);
  iEvent.put(Hcal                    , prefix + "HcalTowSumEtConeDR04"       + suffix);
  iEvent.put(HcalDepth1              , prefix + "HcalDepth1TowSumEtConeDR04" + suffix);
  iEvent.put(HcalDepth2              , prefix + "HcalDepth2TowSumEtConeDR04" + suffix);
  iEvent.put(R9                      , prefix + "R9"                         + suffix);
  iEvent.put(e1x5                    , prefix + "e1x5"                       + suffix);
  iEvent.put(e2x5                    , prefix + "e2x5"                       + suffix);
  iEvent.put(e3x3                    , prefix + "e3x3"                       + suffix);
  iEvent.put(e5x5                    , prefix + "e5x5"                       + suffix);
  iEvent.put(SCenergy                , prefix + "SuperClusterEnergy"         + suffix);
  iEvent.put(SCpoint                 , prefix + "SuperClusterPos"            + suffix);
  iEvent.put(SCetaWidth              , prefix + "SuperClusterEtaWidth"       + suffix);
  iEvent.put(SCphiWidth              , prefix + "SuperClusterPhiWidth"       + suffix);

  iEvent.put(nConversions            , prefix + "NConversions"               + suffix);
  iEvent.put(allConversionTracksSumPt, prefix + "AllConversionTracksSumPt"   + suffix);
  iEvent.put(bestConvTrack0P3        , prefix + "BestConversionTrack0P3"     + suffix);
  iEvent.put(bestConvTrack1P3        , prefix + "BestConversionTrack1P3"     + suffix);
  iEvent.put(bestConvVertex          , prefix + "BestConversionVertex"       + suffix);
  iEvent.put(bestConvEoverP          , prefix + "BestConversionEoverP"       + suffix);
  iEvent.put(bestConvMass            , prefix + "BestConversionMass"         + suffix);
}

// extra information stored for PAT data
template< typename T >
void SusyCAF_Photon<T>::
producePAT(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<T> >& collection) {
  std::auto_ptr<std::vector<int> >    idLoose       ( new std::vector<int>() );
  std::auto_ptr<std::vector<int> >    idTight       ( new std::vector<int>() );
  std::auto_ptr<std::vector<float> >  trkIso        ( new std::vector<float>() );
  std::auto_ptr<std::vector<float> >  caloIso       ( new std::vector<float>() );
  std::auto_ptr<std::vector<float> >  ecalIso       ( new std::vector<float>() );
  std::auto_ptr<std::vector<float> >  hcalIso       ( new std::vector<float>() );
  std::auto_ptr<std::vector<float> >  sigmaEtaEta   ( new std::vector<float>() );
  std::auto_ptr<std::vector<float> >  sigmaIetaIeta ( new std::vector<float>() );
  
  if (collection.isValid()){
    for (typename std::vector<T>::const_iterator it = collection->begin(); it != collection->end(); ++it) {
      const pat::Photon& photon = *it;
      idLoose      ->push_back(photon.photonID("PhotonCutBasedIDLoose"));
      idTight      ->push_back(photon.photonID("PhotonCutBasedIDTight"));
      trkIso       ->push_back(photon.trackIso     ());
      caloIso      ->push_back(photon.caloIso      ());
      ecalIso      ->push_back(photon.ecalIso      ());
      hcalIso      ->push_back(photon.hcalIso      ());
      sigmaEtaEta  ->push_back(photon.sigmaEtaEta  ());
      sigmaIetaIeta->push_back(photon.sigmaIetaIeta());
    }
  }
  
  iEvent.put(idLoose      , prefix + "IDLoose"        + suffix);
  iEvent.put(idTight      , prefix + "IDTight"        + suffix);
  iEvent.put(trkIso       , prefix + "TrkIso"         + suffix);
  iEvent.put(caloIso      , prefix + "CaloIso"        + suffix);
  iEvent.put(ecalIso      , prefix + "EcalIso"        + suffix);
  iEvent.put(hcalIso      , prefix + "HcalIso"        + suffix);
  iEvent.put(sigmaEtaEta  , prefix + "SigmaEtaEta"    + suffix);
  iEvent.put(sigmaIetaIeta, prefix + "SigmaIetaIeta"  + suffix);
}

template< typename T >
void SusyCAF_Photon<T>::
produceExtra(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<T> >& collection) 
{
  //ID from CMS AN 2010/141
  if (!produceExtraVars) return;
  produceExtraTrackVars(iEvent, iSetup, collection);
  produceExtraSuperClusterVars(iEvent, iSetup, collection);
  produceExtraCaloIsoVars(iEvent, iSetup, collection);
}

template< typename T >
double SusyCAF_Photon<T>::hcalEnergy(const CaloGeometry* geometry,
				     const HBHERecHitMetaCollection& mHbhe,
				     reco::SuperClusterRef& sc,
				     typename std::vector<T>::const_iterator it,
				     double coneSize) {

  CaloConeSelector selector(coneSize, geometry, DetId::Hcal);
  std::auto_ptr<CaloRecHitMetaCollectionV> selected = selector.select(sc->eta(), sc->phi(), mHbhe);

  double answer = 0.0;
  for (CaloRecHitMetaCollectionV::const_iterator hit=selected->begin(); hit != selected->end(); ++hit) answer += hit->energy();
  return answer;
}

template< typename T >
void SusyCAF_Photon<T>::
produceExtraCaloIsoVars(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<T> >& collection)
{
  std::auto_ptr<std::vector<double> > hcalOverEcal01 (new std::vector<double>());
  std::auto_ptr<std::vector<double> > hcalOverEcal015(new std::vector<double>());
  std::auto_ptr<std::vector<double> > hcalOverEcal04 (new std::vector<double>());
  std::auto_ptr<std::vector<double> > hcalOverEcal05 (new std::vector<double>());
  std::auto_ptr<std::vector<double> > hcalOverEcal07 (new std::vector<double>());
  std::auto_ptr<std::vector<double> > hcalOverEcal1  (new std::vector<double>());

  std::auto_ptr<std::vector<double> > ecalIso01 (new std::vector<double>());
  std::auto_ptr<std::vector<double> > ecalIso015(new std::vector<double>());
  std::auto_ptr<std::vector<double> > ecalIso04 (new std::vector<double>());
  std::auto_ptr<std::vector<double> > ecalIso05 (new std::vector<double>());
  std::auto_ptr<std::vector<double> > ecalIso07 (new std::vector<double>());
  std::auto_ptr<std::vector<double> > ecalIso1  (new std::vector<double>());

  edm::ESHandle<CaloGeometry> geometry;
  iSetup.get<CaloGeometryRecord>().get(geometry);

  edm::Handle<EBRecHitCollection> ebRecHits;
  iEvent.getByLabel(ecalRecHitProducer, ebRecHitCollection, ebRecHits);

  edm::Handle<EERecHitCollection> eeRecHits;
  iEvent.getByLabel(ecalRecHitProducer, eeRecHitCollection, eeRecHits);

  edm::Handle<HBHERecHitCollection> hbhe;
  iEvent.getByLabel(hbheRecHitCollection, hbhe);
  const HBHERecHitMetaCollection mHbhe(*hbhe);
 
  bool allValid = geometry.isValid() && hbhe.isValid() && ebRecHits.isValid() && eeRecHits.isValid();
  double dummyValue = -100.0;

  if (collection.isValid()) {
    for (typename std::vector<T>::const_iterator it = collection->begin(); it != collection->end(); ++it) {
      const reco::Photon& photon = *it;
      reco::SuperClusterRef scluster = photon.superCluster();
      hcalOverEcal01 ->push_back( allValid ? hcalEnergy(geometry.product(), mHbhe, scluster, it, 0.1 )/it->energy() : dummyValue );
      hcalOverEcal015->push_back( allValid ? hcalEnergy(geometry.product(), mHbhe, scluster, it, 0.15)/it->energy() : dummyValue );
      hcalOverEcal04 ->push_back( allValid ? hcalEnergy(geometry.product(), mHbhe, scluster, it, 0.4 )/it->energy() : dummyValue );
      hcalOverEcal05 ->push_back( allValid ? hcalEnergy(geometry.product(), mHbhe, scluster, it, 0.5 )/it->energy() : dummyValue );
      hcalOverEcal07 ->push_back( allValid ? hcalEnergy(geometry.product(), mHbhe, scluster, it, 0.7 )/it->energy() : dummyValue );
      hcalOverEcal1  ->push_back( allValid ? hcalEnergy(geometry.product(), mHbhe, scluster, it, 1.0 )/it->energy() : dummyValue );

      reco::CaloClusterPtr SCseed = scluster->seed();
      SuperClusterHitsEcalIsolation scBasedIsolation(ebRecHits.product(),eeRecHits.product());
      scBasedIsolation.setExtRadius(0.1);
      scBasedIsolation.excludeHalo(false);
      ecalIso01->push_back( allValid ? scBasedIsolation.getSum(iEvent,iSetup,&(*SCseed)) : dummyValue );

      scBasedIsolation.setExtRadius(0.15);
      ecalIso015->push_back( allValid ? scBasedIsolation.getSum(iEvent,iSetup,&(*SCseed)) : dummyValue );

      scBasedIsolation.setExtRadius(0.4);
      ecalIso04->push_back( allValid ? scBasedIsolation.getSum(iEvent,iSetup,&(*SCseed)) : dummyValue );

      scBasedIsolation.setExtRadius(0.5);
      ecalIso05->push_back( allValid ? scBasedIsolation.getSum(iEvent,iSetup,&(*SCseed)) : dummyValue );

      scBasedIsolation.setExtRadius(0.7);
      ecalIso07->push_back( allValid ? scBasedIsolation.getSum(iEvent,iSetup,&(*SCseed)) : dummyValue );

      scBasedIsolation.setExtRadius(1.);
      ecalIso1->push_back( allValid ? scBasedIsolation.getSum(iEvent,iSetup,&(*SCseed)) : dummyValue );

    }//end loop over photons
  }//end photon collection is valid
  
  iEvent.put(hcalOverEcal01  , prefix + "ExtraHcalOverEcal01"  + suffix);
  iEvent.put(hcalOverEcal015 , prefix + "ExtraHcalOverEcal015" + suffix);
  iEvent.put(hcalOverEcal04  , prefix + "ExtraHcalOverEcal04"  + suffix);
  iEvent.put(hcalOverEcal05  , prefix + "ExtraHcalOverEcal05"  + suffix);
  iEvent.put(hcalOverEcal07  , prefix + "ExtraHcalOverEcal07"  + suffix);
  iEvent.put(hcalOverEcal1   , prefix + "ExtraHcalOverEcal1"   + suffix);

  iEvent.put(ecalIso01  , prefix + "ExtraEcalIso01"  + suffix);
  iEvent.put(ecalIso015 , prefix + "ExtraEcalIso015" + suffix);
  iEvent.put(ecalIso04  , prefix + "ExtraEcalIso04"  + suffix);
  iEvent.put(ecalIso05  , prefix + "ExtraEcalIso05"  + suffix);
  iEvent.put(ecalIso07  , prefix + "ExtraEcalIso07"  + suffix);
  iEvent.put(ecalIso1   , prefix + "ExtraEcalIso1"   + suffix);
 }

template< typename T >
void SusyCAF_Photon<T>::
produceExtraSuperClusterVars(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<T> >& collection)
{

  std::auto_ptr<std::vector<double> > SCMajorMajor(new std::vector<double>());
  std::auto_ptr<std::vector<double> > SCMinorMinor(new std::vector<double>());

  edm::Handle<EBRecHitCollection> ebRecHits;
  iEvent.getByLabel(ecalRecHitProducer, ebRecHitCollection, ebRecHits);

  if (collection.isValid()) {
    for (typename std::vector<T>::const_iterator it = collection->begin(); it != collection->end(); ++it) {
      const reco::Photon& photon = *it;
      reco::SuperClusterRef scluster = photon.superCluster();
      SCMajorMajor->push_back(-100.0);
      SCMinorMinor->push_back(-100.0);

      reco::CaloClusterPtr SCseed = scluster->seed();
      if (ebRecHits.isValid() && fabs(SCseed->eta())<ebEeBoundary()) {
      	Cluster2ndMoments moments = EcalClusterTools::cluster2ndMoments(*SCseed, *(ebRecHits.product()) );
      	SCMajorMajor->back()=moments.sMaj;
      	SCMinorMinor->back()=moments.sMin;
      }
    }//end loop over photons
  }//end photon collection is valid
  
  iEvent.put(SCMajorMajor            , prefix + "SuperClusterMajorMajor"     + suffix);
  iEvent.put(SCMinorMinor            , prefix + "SuperClusterMinorMinor"     + suffix);
 }

template< typename T >
void SusyCAF_Photon<T>::
produceExtraTrackVars(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<T> >& collection)
{
  std::auto_ptr<std::vector<float> > TrkIso0015( new std::vector<float>() );
  std::auto_ptr<std::vector<float> > TrkIso035 ( new std::vector<float>() );
  std::auto_ptr<std::vector<float> > TrkIso04  ( new std::vector<float>() );
  std::auto_ptr<std::vector<float> > TrkIso05  ( new std::vector<float>() );
  std::auto_ptr<std::vector<float> > TrkIso07  ( new std::vector<float>() );
  std::auto_ptr<std::vector<float> > TrkIso1   ( new std::vector<float>() );
  
  std::auto_ptr<std::vector<int> > NTrk0015( new std::vector<int>() );
  std::auto_ptr<std::vector<int> > NTrk035 ( new std::vector<int>() );
  std::auto_ptr<std::vector<int> > NTrk04  ( new std::vector<int>() );
  std::auto_ptr<std::vector<int> > NTrk05  ( new std::vector<int>() );
  std::auto_ptr<std::vector<int> > NTrk07  ( new std::vector<int>() );
  std::auto_ptr<std::vector<int> > NTrk1   ( new std::vector<int>() );

  edm::Handle<reco::TrackCollection> tracks;
  iEvent.getByLabel(trackTag,tracks);

  if (collection.isValid()) {
    for (typename std::vector<T>::const_iterator it = collection->begin(); it != collection->end(); ++it) {
      const reco::Photon& photon = *it;

      TrkIso0015->push_back(0.0);
      TrkIso035 ->push_back(0.0);
      TrkIso04  ->push_back(0.0);
      TrkIso05  ->push_back(0.0);
      TrkIso07  ->push_back(0.0);
      TrkIso1   ->push_back(0.0);
  
      NTrk0015->push_back(0);
      NTrk035 ->push_back(0);
      NTrk04  ->push_back(0);
      NTrk05  ->push_back(0);
      NTrk07  ->push_back(0);
      NTrk1   ->push_back(0);

      if (tracks.isValid()) {
	for (reco::TrackCollection::const_iterator itTrack = tracks->begin(); itTrack != tracks->end(); ++itTrack) {
	  double deltaR = ROOT::Math::VectorUtil::DeltaR(itTrack->innerMomentum(), photon.p4());
	  //double p  = itTrack->innerMomentum().R();
	  double pt = itTrack->innerMomentum().Rho();
	  
	  if (deltaR < 0.015) {TrkIso0015->back() += pt; NTrk0015->back()++;}
	  if (deltaR < 0.350) {TrkIso035 ->back() += pt; NTrk035 ->back()++;}
	  if (deltaR < 0.400) {TrkIso04  ->back() += pt; NTrk04  ->back()++;}
	  if (deltaR < 0.500) {TrkIso05  ->back() += pt; NTrk05  ->back()++;}
	  if (deltaR < 0.700) {TrkIso07  ->back() += pt; NTrk07  ->back()++;}
	  if (deltaR < 1.000) {TrkIso1   ->back() += pt; NTrk1   ->back()++;}
	  
	}//track collection
      }//track collection handle valid

    }//photon collection
  }//photon collection handle valid

  iEvent.put(TrkIso0015, prefix + "ExtraTrkIso0015" + suffix);
  iEvent.put(TrkIso035 , prefix + "ExtraTrkIso035"  + suffix);
  iEvent.put(TrkIso04  , prefix + "ExtraTrkIso04"   + suffix);
  iEvent.put(TrkIso05  , prefix + "ExtraTrkIso05"   + suffix);
  iEvent.put(TrkIso07  , prefix + "ExtraTrkIso07"   + suffix);
  iEvent.put(TrkIso1   , prefix + "ExtraTrkIso1"    + suffix);

  iEvent.put(NTrk0015, prefix + "ExtraNTrk0015" + suffix);
  iEvent.put(NTrk035 , prefix + "ExtraNTrk035"  + suffix);
  iEvent.put(NTrk04  , prefix + "ExtraNTrk04"   + suffix);
  iEvent.put(NTrk05  , prefix + "ExtraNTrk05"   + suffix);
  iEvent.put(NTrk07  , prefix + "ExtraNTrk07"   + suffix);
  iEvent.put(NTrk1   , prefix + "ExtraNTrk1"    + suffix);
}

#endif
