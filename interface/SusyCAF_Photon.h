#ifndef SUSY_CAF_PHOTON
#define SUSY_CAF_PHOTON

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"

#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include <Math/ProbFuncMathCore.h>


template< typename T >
class SusyCAF_Photon : public edm::EDProducer 
{
public: 
  explicit SusyCAF_Photon(const edm::ParameterSet&);

private: 
  void initTemplate();
  void initRECO();
  void initPAT();
  void produce(edm::Event &, const edm::EventSetup & );
  void produceTemplate(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<reco::Photon> > &);
  void produceTemplate(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<pat::Photon> > &);
  void produceRECO(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &);
  void producePAT(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &);

  const edm::InputTag   inputTag;
  const std::string     prefix,suffix;
  
  typedef reco::Candidate::LorentzVector  LorentzVector;
  typedef reco::Candidate::Vector         Vector;
  typedef reco::Candidate::Point          Point;
};


template< typename T >
SusyCAF_Photon<T>::SusyCAF_Photon(const edm::ParameterSet& iConfig) 
  : inputTag(iConfig.getParameter<edm::InputTag>("InputTag"))
  , prefix  (iConfig.getParameter<std::string>  ("Prefix"  ))
  , suffix  (iConfig.getParameter<std::string>  ("Suffix"  ))
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
  produces <std::vector<float> > (prefix + "TrkSumPtHollowConeDR04" + suffix);
  produces <std::vector<float> > (prefix + "EcalRecHitEtConeDR04" + suffix);
  produces <std::vector<float> > (prefix + "HcalDepth1TowSumEtConeDR04" + suffix);
  produces <std::vector<float> > (prefix + "HcalDepth2TowSumEtConeDR04" + suffix);
  produces <std::vector<float> > (prefix + "R9" + suffix);
  produces <std::vector<float> > (prefix + "e1x5" + suffix);
  produces <std::vector<float> > (prefix + "e2x5" + suffix);
  produces <std::vector<float> > (prefix + "e3x3" + suffix);
  produces <std::vector<float> > (prefix + "e5x5" + suffix);
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
  produces <std::vector<int> > (prefix + "IDLoose" + suffix);
  produces <std::vector<int> > (prefix + "IDTight" + suffix);
  produces <std::vector<float> > (prefix + "TrkIso" + suffix);
  produces <std::vector<float> >(prefix + "CaloIso"       + suffix);
  produces <std::vector<float> >(prefix + "EcalIso"       + suffix);
  produces <std::vector<float> >(prefix + "HcalIso"       + suffix);
  produces <std::vector<float> >(prefix + "SigmaEtaEta"   + suffix);
  produces <std::vector<float> >(prefix + "SigmaIetaIeta" + suffix);
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
  produceRECO(iEvent, iSetup, collection);
}
// produce method in case of PAT data
template< typename T >
void SusyCAF_Photon<T>::produceTemplate(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<pat::Photon> >& collection) {
  produceRECO(iEvent, iSetup, collection);
  producePAT (iEvent, iSetup, collection);
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
  
  iEvent.put(isHandleValid        , prefix + "HandleValid"          + suffix);
  iEvent.put(p4                   , prefix + "P4"                   + suffix);
  iEvent.put(caloPosition         , prefix + "CaloPosition"         + suffix);
  iEvent.put(hadronicDepth1OverEm , prefix + "HadronicDepth1OverEm" + suffix);
  iEvent.put(hadronicDepth2OverEm , prefix + "HadronicDepth2OverEm" + suffix);
  iEvent.put(hadronicOverEm       , prefix + "HadronicOverEm"       + suffix);
  iEvent.put(hasPixelSeed         , prefix + "HasPixelSeed"         + suffix);
  iEvent.put(isEB                 , prefix + "IsEB"                 + suffix);
  iEvent.put(isEE                 , prefix + "IsEE"                 + suffix);
  iEvent.put(isEBGap              , prefix + "IsEBGap"              + suffix);
  iEvent.put(isEEGap              , prefix + "IsEEGap"              + suffix);
  iEvent.put(isEBEEGap            , prefix + "IsEBEEGap"            + suffix);
  
  iEvent.put(trkSumPtHolConeDR04,  prefix + "TrkSumPtHollowConeDR04" + suffix);
  iEvent.put(EcalrechitEtConeDR04, prefix + "EcalRecHitEtConeDR04"   + suffix);
  iEvent.put(HcalDepth1, prefix + "HcalDepth1TowSumEtConeDR04" + suffix);
  iEvent.put(HcalDepth2, prefix + "HcalDepth2TowSumEtConeDR04" + suffix);
  iEvent.put(R9,   prefix + "R9"   + suffix);
  iEvent.put(e1x5, prefix + "e1x5" + suffix);
  iEvent.put(e2x5, prefix + "e2x5" + suffix);
  iEvent.put(e3x3, prefix + "e3x3" + suffix);
  iEvent.put(e5x5, prefix + "e5x5" + suffix);
  iEvent.put(SCenergy,   prefix + "SuperClusterEnergy"   + suffix);
  iEvent.put(SCpoint,    prefix + "SuperClusterPos"      + suffix);
  iEvent.put(SCetaWidth, prefix + "SuperClusterEtaWidth" + suffix);
  iEvent.put(SCphiWidth, prefix + "SuperClusterPhiWidth" + suffix);

  iEvent.put(nConversions, prefix + "NConversions" + suffix);
  iEvent.put(allConversionTracksSumPt, prefix + "AllConversionTracksSumPt" + suffix);
  iEvent.put(bestConvTrack0P3, prefix + "BestConversionTrack0P3"     + suffix);
  iEvent.put(bestConvTrack1P3, prefix + "BestConversionTrack1P3"     + suffix);
  iEvent.put(bestConvVertex  , prefix + "BestConversionVertex" + suffix);
  iEvent.put(bestConvEoverP  , prefix + "BestConversionEoverP" + suffix);
  iEvent.put(bestConvMass    , prefix + "BestConversionMass"   + suffix);
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



#endif
