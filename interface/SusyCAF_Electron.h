#ifndef SUSY_CAF_ELECTRON
#define SUSY_CAF_ELECTRON

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_functions.h"
#include <string>

// Conversion variables
#include "RecoEgamma/EgammaTools/interface/ConversionFinder.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"

template< typename T >
class SusyCAF_Electron : public edm::EDProducer {
public:
 explicit SusyCAF_Electron(const edm::ParameterSet&);
private:
 void initTemplate();
 void initRECO();
 void initPAT();
 void produce(edm::Event &, const edm::EventSetup & );
 void produceTemplate(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &);
 void produceRECO(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &);
 void producePAT(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &);

 typedef reco::Candidate::LorentzVector LorentzVector;

 const edm::InputTag inputTag;
 const std::string Prefix,Suffix;
 const bool StoreConversionInfo;
};

template< typename T >
SusyCAF_Electron<T>::SusyCAF_Electron(const edm::ParameterSet& iConfig) :
 inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
 Prefix(iConfig.getParameter<std::string>("Prefix")),
 Suffix(iConfig.getParameter<std::string>("Suffix")),
 StoreConversionInfo(iConfig.getParameter<bool>("StoreConversionInfo"))
{
 initTemplate();
}


template< typename T >
void SusyCAF_Electron<T>::initRECO()
{
 produces <bool> (  Prefix + "HandleValid" + Suffix);
 produces <std::vector<reco::Candidate::LorentzVector> > ( Prefix + "P4" + Suffix );
 produces <std::vector<int> > (  Prefix + "Charge" + Suffix);
 produces <std::vector<double> > (  Prefix + "GsfTracknormalizedChi2" + Suffix);
 produces <std::vector<unsigned> > (  Prefix + "GsfTracknumberOfValidHits" + Suffix);

 produces <std::vector<float> > (  Prefix + "GsfTrackChargeMode" + Suffix);
 produces <std::vector<float> > (  Prefix + "GsfTrackPtMode" + Suffix);
 produces <std::vector<float> > (  Prefix + "GsfTrackQoverPErrorMode" + Suffix);
 produces <std::vector<float> > (  Prefix + "GsfTrackCharge" + Suffix);
 produces <std::vector<float> > (  Prefix + "GsfTrackPt" + Suffix);
 produces <std::vector<float> > (  Prefix + "GsfTrackQoverPError" + Suffix);
 produces <std::vector<float> > (  Prefix + "GsfTrackLostHits" + Suffix);
 produces <std::vector<int> > ( Prefix + "HasValidHitInFirstPixelBarrel" + Suffix);
 produces <std::vector<int> > ( Prefix +  "GsfTrackTrackerExpectedHitsInner" + Suffix);
 produces <std::vector<double> > (  Prefix + "GsfTrackDxy" + Suffix);
 produces <std::vector<double> > (  Prefix + "GsfTrackDz" + Suffix);
 produces <std::vector<double> > (  Prefix + "GsfTrackDxyBS" + Suffix);
 produces <std::vector<double> > (  Prefix + "GsfTrackDzBS" + Suffix);
 produces <std::vector<double> > (  Prefix + "GsfTrackDxyError" + Suffix);
 produces <std::vector<double> > (  Prefix + "GsfTrackDzError" + Suffix);

 produces <std::vector<float> > (  Prefix + "E1x5" + Suffix);
 produces <std::vector<float> > (  Prefix + "E5x5" + Suffix);
 produces <std::vector<float> > (  Prefix + "E2x5Max" + Suffix);
 produces <std::vector<float> > (  Prefix + "Fbrem" + Suffix);
 produces <std::vector<float> > (  Prefix + "HcalOverEcal" + Suffix);
 produces <std::vector<float> > (  Prefix + "HcalDepth1OverEcal" + Suffix);
 produces <std::vector<float> > (  Prefix + "HcalDepth2OverEcal" + Suffix);
 produces <std::vector<float> > (  Prefix + "EEleClusterOverPout" + Suffix);
 produces <std::vector<float> > (  Prefix + "ESeedClusterOverPout" + Suffix);
 produces <std::vector<float> > (  Prefix + "ESeedClusterOverP" + Suffix);
 produces <std::vector<float> > (  Prefix + "ESuperClusterOverP" + Suffix);
 //MICHELE
 produces <std::vector<float> > (  Prefix + "ESuperClusterEta" + Suffix);
 produces <std::vector<float> > (  Prefix + "ESuperClusterPhi" + Suffix); 
 //MICHELE
 produces <std::vector<float> > (  Prefix + "DeltaPhiSuperClusterTrackAtVtx" + Suffix);
 produces <std::vector<float> > (  Prefix + "DeltaEtaSuperClusterTrackAtVtx" + Suffix);
 produces <std::vector<float> > (  Prefix + "DeltaPhiSeedClusterTrackAtCalo" + Suffix);
 produces <std::vector<float> > (  Prefix + "DeltaEtaSeedClusterTrackAtCalo" + Suffix);
 produces <std::vector<float> > (  Prefix + "DeltaEtaEleClusterTrackAtCalo" + Suffix);
 produces <std::vector<float> > (  Prefix + "DeltaPhiEleClusterTrackAtCalo" + Suffix);
 produces <std::vector<float> > (  Prefix + "SigmaEtaEta" + Suffix);
 produces <std::vector<float> > (  Prefix + "SigmaIetaIeta" + Suffix);
 produces <std::vector<float> > (  Prefix + "Classification" + Suffix);
 produces <std::vector<float> > (  Prefix + "Mva" + Suffix);
 produces <std::vector<float> > (  Prefix + "Dr03TkSumPt" + Suffix);
 produces <std::vector<float> > (  Prefix + "Dr03EcalRecHitSumEt" + Suffix);
 produces <std::vector<float> > (  Prefix + "Dr03HcalTowerSumEt" + Suffix);
 produces <std::vector<float> > (  Prefix + "Dr03HcalDepth1TowerSumEt" + Suffix);
 produces <std::vector<float> > (  Prefix + "Dr03HcalDepth2TowerSumEt" + Suffix);
 produces <std::vector<float> > (  Prefix + "CaloEnergy" + Suffix);
 produces <std::vector<float> > (  Prefix + "EcalEnergy" + Suffix);
 produces <std::vector<float> > (  Prefix + "EcalEnergyError" + Suffix);
 produces <std::vector<float> > (  Prefix + "ElectronMomentumError" + Suffix);
 produces <std::vector<float> > (  Prefix + "NumberOfTracks" + Suffix);
 produces <std::vector<int> >   (  Prefix + "NumberOfBrems" + Suffix);
 produces <std::vector<float> > (  Prefix + "ShFracInnerHits" + Suffix);
 produces <std::vector<math::XYZPoint> > (  Prefix + "Vertex" + Suffix);
 produces <std::vector<double> > (  Prefix + "VertexChi2" + Suffix);
 produces <std::vector<double> > (  Prefix + "VertexNdof" + Suffix);
 produces <bool> ( Prefix + "ConversionInfoStored" + Suffix);
 if(StoreConversionInfo){
   produces <std::vector<double> > (  Prefix + "ConversionDCot" + Suffix );
   produces <std::vector<double> > (  Prefix + "ConversionDist" + Suffix );
   produces <std::vector<int> > (  Prefix + "ConversionMissingHits" + Suffix );
   produces <std::vector<int> > ( Prefix + "ConversionPartnerCtfTrackTrackerExpectedHitsInner" + Suffix);
   produces <std::vector<int> > ( Prefix + "ConversionPartnerGsfTrackTrackerExpectedHitsInner" + Suffix);
 }
 produces <std::vector<float> > ( Prefix + "KfTrackCharge" + Suffix );
 produces <std::vector<int> > ( Prefix + "ScPixCharge" + Suffix );
 produces <std::vector<int> > ( Prefix + "ClosestCtfTrackCharge" + Suffix );
}

// extra information stored for PAT data
template< typename T >
void SusyCAF_Electron<T>::initPAT()
{
 produces <std::vector<float> >  (Prefix + "EcalIso"                   + Suffix);
 produces <std::vector<float> >  (Prefix + "HcalIso"                   + Suffix);
 produces <std::vector<float> >  (Prefix + "TrackIso"                  + Suffix);
 produces <std::vector<float> >  (Prefix + "EIDTight"                  + Suffix);
 produces <std::vector<float> >  (Prefix + "EIDRobustTight"            + Suffix);
 produces <std::vector<float> >  (Prefix + "EIDLoose"                  + Suffix);
 produces <std::vector<float> >  (Prefix + "EIDRobustLoose"            + Suffix);
 produces <std::vector<float> > (Prefix + "EcalIsoDep" + Suffix);
 produces <std::vector<float> > (Prefix + "HcalIsoDep" + Suffix);
 produces <std::vector<int> > (Prefix + "ProducedFromPF" + Suffix);
 produces <std::vector<float> > (Prefix + "IdPfevspi" + Suffix);
 produces <std::vector<float> > (Prefix + "ParticleIso" + Suffix);
 produces <std::vector<float> > (Prefix + "ChargedHadronIso" + Suffix);
 produces <std::vector<float> > (Prefix + "NeutralHadronIso" + Suffix);
 produces <std::vector<float> > (Prefix + "PhotonIso" + Suffix);


}

template< typename T >
void SusyCAF_Electron<T>::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
 edm::Handle<std::vector<T> > collection;
 iEvent.getByLabel(inputTag,collection);

 produceTemplate(iEvent, iSetup, collection);
}

template< typename T >
void SusyCAF_Electron<T>::
produceRECO(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<T> >& collection) {
 std::auto_ptr<bool> isHandleValid ( new bool(collection.isValid()) );
 std::auto_ptr<std::vector<reco::Candidate::LorentzVector> > p4 ( new std::vector<reco::Candidate::LorentzVector>() );
 std::auto_ptr<std::vector<int> >  charge   ( new std::vector<int>()  ) ;
 std::auto_ptr<std::vector<double> >  gsfTrack_normalizedChi2   ( new std::vector<double>()  ) ;
 std::auto_ptr<std::vector<unsigned> >  gsfTrack_numberOfValidHits   ( new std::vector<unsigned>()  ) ;

 std::auto_ptr<std::vector<double> >  gsfTrack_dxy     ( new std::vector<double>()  ) ;
 std::auto_ptr<std::vector<double> >  gsfTrack_dz      ( new std::vector<double>()  ) ;
 std::auto_ptr<std::vector<double> >  gsfTrack_dxyBS   ( new std::vector<double>()  ) ;
 std::auto_ptr<std::vector<double> >  gsfTrack_dzBS    ( new std::vector<double>()  ) ;
 std::auto_ptr<std::vector<double> >  gsfTrack_dxyError( new std::vector<double>()  ) ;
 std::auto_ptr<std::vector<double> >  gsfTrack_dzError ( new std::vector<double>()  ) ;

 std::auto_ptr<std::vector<float> > gsfTrkChargeMode (new std::vector<float>() );
 std::auto_ptr<std::vector<float> > gsfTrkPtMode (new std::vector<float>() );
 std::auto_ptr<std::vector<float> > gsfTrkQoverPErrMode (new std::vector<float>() );
 std::auto_ptr<std::vector<float> > gsfTrkCharge (new std::vector<float>() );
 std::auto_ptr<std::vector<float> > gsfTrkPt (new std::vector<float>() );
 std::auto_ptr<std::vector<float> > gsfTrkQoverPErr (new std::vector<float>() );
 std::auto_ptr<std::vector<float> > gsfTrkLostHits (new std::vector<float>() );
 std::auto_ptr<std::vector<int> > hasValHitinFirstPixBarrel (new std::vector<int>() );
 std::auto_ptr<std::vector<int> > gsfTrkTrackerExpectedHitsInner (new std::vector<int>() );
 std::auto_ptr<std::vector<float> >  e1x5   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  e5x5   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  e2x5Max   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  fbrem   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  hcalOverEcal   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  hcalDepth1OverEcal   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  hcalDepth2OverEcal   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  eEleClusterOverPout   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  eSeedClusterOverPout   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  eSeedClusterOverP   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  eSuperClusterOverP   ( new std::vector<float>()  ) ;
 //MICHELE
 std::auto_ptr<std::vector<float> >  eSuperClusterEta  ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  eSuperClusterPhi   ( new std::vector<float>()  ) ;
 //MICHELE
 std::auto_ptr<std::vector<float> >  deltaPhiSuperClusterTrackAtVtx   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  deltaEtaSuperClusterTrackAtVtx   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  deltaPhiSeedClusterTrackAtCalo   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  deltaEtaSeedClusterTrackAtCalo   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  deltaEtaEleClusterTrackAtCalo   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  deltaPhiEleClusterTrackAtCalo   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  sigmaEtaEta   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  sigmaIetaIeta   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  classification   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  mva   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  dr03TkSumPt   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  dr03EcalRecHitSumEt   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  dr03HcalTowerSumEt   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  dr03HcalDepth1TowerSumEt   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  dr03HcalDepth2TowerSumEt   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  caloEnergy   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  ecalEnergy   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  ecalEnergyError   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  electronMomentumError   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  numberOfTracks   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<int> >    numberOfBrems   ( new std::vector<int>()  ) ;
 std::auto_ptr<std::vector<float> >  shFracInnerHits   ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<math::XYZPoint> >  vertex   ( new std::vector<math::XYZPoint>()  ) ;
 std::auto_ptr<std::vector<double> >  vertexChi2   ( new std::vector<double>()  ) ;
 std::auto_ptr<std::vector<double> >  vertexNdof   ( new std::vector<double>()  ) ;
 std::auto_ptr<bool> conversionInfoStored ( new bool() );
 std::auto_ptr<std::vector<double> > dcot ( new std::vector<double>() ) ;
 std::auto_ptr<std::vector<double> > dist ( new std::vector<double>() ) ;
 std::auto_ptr<std::vector<int> > missingHits ( new std::vector<int>() ) ;
 std::auto_ptr<std::vector<int> > conversionPartnerCtfTrackTrackerExpectedHitsInner ( new std::vector<int>() ) ;
 std::auto_ptr<std::vector<int> > conversionPartnerGsfTrackTrackerExpectedHitsInner ( new std::vector<int>() ) ;
 std::auto_ptr<std::vector<float> > kfcharge ( new std::vector<float>() );
 std::auto_ptr<std::vector<int> > scPixCharge ( new std::vector<int>() );
 std::auto_ptr<std::vector<int> > closestCtfTrackCharge( new std::vector<int>() );
 math::XYZPoint bs = math::XYZPoint(0.,0.,0.);
 math::XYZPoint vx = math::XYZPoint(0.,0.,0.);
 edm::Handle<reco::BeamSpot> beamspots;        iEvent.getByLabel("offlineBeamSpot", beamspots);
 edm::Handle<reco::VertexCollection> vertices; iEvent.getByLabel("offlinePrimaryVertices", vertices);

 if (beamspots.isValid()) bs = beamspots->position();

 const  MagneticField *mField = 0;
 edm::Handle<reco::TrackCollection> ctfTracks;
 ConversionFinder cf;
 if(StoreConversionInfo){
   edm::ESHandle<MagneticField> magneticField;
   iSetup.get<IdealMagneticFieldRecord>().get(magneticField);
   mField = magneticField.product();
   iEvent.getByLabel("generalTracks", ctfTracks);
 }

 if (collection.isValid()){
   for(typename std::vector<T>::const_iterator it = collection->begin(); it!=collection->end(); it++) {

     p4->push_back(it->p4());
     charge->push_back(it->charge());
     gsfTrack_normalizedChi2->push_back(it->gsfTrack()->normalizedChi2());
     gsfTrack_numberOfValidHits->push_back(it->gsfTrack()->numberOfValidHits());

     if(vertices.isValid() && vertices->size()) vx = SusyCAF_functions::closestDzPrimaryVertexPosition(it->gsfTrack().get(),*vertices);
     gsfTrack_dxy->push_back(it->gsfTrack()->dxy(vx));
     gsfTrack_dz->push_back(it->gsfTrack()->dz(vx));
     gsfTrack_dxyBS->push_back(it->gsfTrack()->dxy(bs));
     gsfTrack_dzBS->push_back(it->gsfTrack()->dz(bs));
     gsfTrack_dxyError->push_back(it->gsfTrack()->dxyError());
     gsfTrack_dzError->push_back(it->gsfTrack()->dzError());

     gsfTrkChargeMode->push_back(it->gsfTrack()->chargeMode());
     gsfTrkPtMode->push_back(it->gsfTrack()->ptMode());
     gsfTrkQoverPErrMode->push_back(it->gsfTrack()->qoverpModeError());
     gsfTrkCharge->push_back(it->gsfTrack()->charge());
     gsfTrkPt->push_back(it->gsfTrack()->pt());
     gsfTrkQoverPErr->push_back(it->gsfTrack()->qoverpError());
     gsfTrkLostHits->push_back(it->gsfTrack()->lost());
     hasValHitinFirstPixBarrel->push_back(it->gsfTrack()->hitPattern().hasValidHitInFirstPixelBarrel());
     gsfTrkTrackerExpectedHitsInner->push_back(it->gsfTrack()->trackerExpectedHitsInner().numberOfHits());
     e1x5->push_back(it->e1x5());
     e5x5->push_back(it->e5x5());
     e2x5Max->push_back(it->e2x5Max());
     fbrem->push_back(it->fbrem());
     hcalOverEcal->push_back(it->hcalOverEcal());
     hcalDepth1OverEcal->push_back(it->hcalDepth1OverEcal());
     hcalDepth2OverEcal->push_back(it->hcalDepth2OverEcal());
     eEleClusterOverPout->push_back(it->eEleClusterOverPout());
     eSeedClusterOverPout->push_back(it->eSeedClusterOverPout());
     eSeedClusterOverP->push_back(it->eSeedClusterOverP());
     eSuperClusterOverP->push_back(it->eSuperClusterOverP());
     //MICHELE
     eSuperClusterEta->push_back(it->superClusterPosition().Eta());
     eSuperClusterPhi->push_back(it->superClusterPosition().Phi());      
     //MICHELE
     deltaPhiSuperClusterTrackAtVtx->push_back(it->deltaPhiSuperClusterTrackAtVtx());
     deltaEtaSuperClusterTrackAtVtx->push_back(it->deltaEtaSuperClusterTrackAtVtx());
     deltaPhiSeedClusterTrackAtCalo->push_back(it->deltaPhiSeedClusterTrackAtCalo());
     deltaEtaSeedClusterTrackAtCalo->push_back(it->deltaEtaSeedClusterTrackAtCalo());
     deltaEtaEleClusterTrackAtCalo->push_back(it->deltaEtaEleClusterTrackAtCalo());
     deltaPhiEleClusterTrackAtCalo->push_back(it->deltaPhiEleClusterTrackAtCalo());
     sigmaEtaEta->push_back(it->sigmaEtaEta());
     sigmaIetaIeta->push_back(it->sigmaIetaIeta());
     classification->push_back(it->classification());
     mva->push_back(it->mva());
     dr03TkSumPt->push_back(it->dr03TkSumPt());
     dr03EcalRecHitSumEt->push_back(it->dr03EcalRecHitSumEt());
     dr03HcalTowerSumEt->push_back(it->dr03HcalTowerSumEt());
     dr03HcalDepth1TowerSumEt->push_back(it->dr03HcalDepth1TowerSumEt());
     dr03HcalDepth2TowerSumEt->push_back(it->dr03HcalDepth2TowerSumEt());
     caloEnergy->push_back(it->caloEnergy());
     ecalEnergy->push_back(it->ecalEnergy());
     ecalEnergyError->push_back(it->ecalEnergyError());
     electronMomentumError->push_back(it->electronMomentumError());
     numberOfTracks->push_back(it->numberOfTracks());
     numberOfBrems->push_back(it->numberOfBrems());
     shFracInnerHits->push_back(it->shFracInnerHits());
     vertex->push_back(it->vertex());
     vertexChi2->push_back(it->vertexChi2());
     vertexNdof->push_back(it->vertexNdof());
     if(StoreConversionInfo && ctfTracks.isValid()){
	*conversionInfoStored = true;
	
       const math::XYZPoint tpoint = it->gsfTrack()->referencePoint();
       const GlobalPoint gp(tpoint.x(), tpoint.y(), tpoint.z());
       double bfield = mField->inTesla(gp).mag();
       ConversionInfo info = cf.getConversionInfo(*it, ctfTracks, bfield);
       dist->push_back(info.dist());
       dcot->push_back(info.dcot());
	missingHits->push_back(it->gsfTrack()->trackerExpectedHitsInner().numberOfHits());
	conversionPartnerCtfTrackTrackerExpectedHitsInner->push_back(info.conversionPartnerCtfTk().isAvailable() ? 
								     info.conversionPartnerCtfTk()->trackerExpectedHitsInner().numberOfHits() : -1);
	conversionPartnerGsfTrackTrackerExpectedHitsInner->push_back(info.conversionPartnerGsfTk().isAvailable() ? 
								     info.conversionPartnerGsfTk()->trackerExpectedHitsInner().numberOfHits() : -1);
     }
     kfcharge->push_back(it->track().isAvailable() ? it->track()->charge() : 0);
     scPixCharge->push_back(it->scPixCharge());
     closestCtfTrackCharge->push_back(it->closestCtfTrackRef().isAvailable() ? it->closestCtfTrackRef()->charge() : 0) ;
   }
 }

 iEvent.put( isHandleValid,  Prefix + "HandleValid" + Suffix );
 iEvent.put( p4,  Prefix + "P4" + Suffix );
 iEvent.put( charge,  Prefix + "Charge" + Suffix );

 iEvent.put( gsfTrack_normalizedChi2,  Prefix + "GsfTracknormalizedChi2" + Suffix );
 iEvent.put( gsfTrack_numberOfValidHits,  Prefix + "GsfTracknumberOfValidHits" + Suffix );

 iEvent.put( gsfTrack_dxy,  Prefix + "GsfTrackDxy" + Suffix );
 iEvent.put( gsfTrack_dz,   Prefix + "GsfTrackDz" + Suffix );
 iEvent.put( gsfTrack_dxyBS,  Prefix + "GsfTrackDxyBS" + Suffix );
 iEvent.put( gsfTrack_dzBS,   Prefix + "GsfTrackDzBS" + Suffix );
 iEvent.put( gsfTrack_dxyError,  Prefix + "GsfTrackDxyError" + Suffix );
 iEvent.put( gsfTrack_dzError,   Prefix + "GsfTrackDzError" + Suffix );

 iEvent.put( gsfTrkChargeMode,  Prefix + "GsfTrackChargeMode" + Suffix );
 iEvent.put( gsfTrkPtMode,  Prefix + "GsfTrackPtMode" + Suffix );
 iEvent.put( gsfTrkQoverPErrMode,  Prefix + "GsfTrackQoverPErrorMode" + Suffix );
 iEvent.put( gsfTrkCharge,  Prefix + "GsfTrackCharge" + Suffix );
 iEvent.put( gsfTrkPt, Prefix+ "GsfTrackPt" + Suffix);
 iEvent.put( gsfTrkQoverPErr,  Prefix + "GsfTrackQoverPError" + Suffix );
 iEvent.put( gsfTrkLostHits,  Prefix + "GsfTrackLostHits" + Suffix );
 iEvent.put( hasValHitinFirstPixBarrel, Prefix + "HasValidHitInFirstPixelBarrel" + Suffix);
 iEvent.put( gsfTrkTrackerExpectedHitsInner, Prefix + "GsfTrackTrackerExpectedHitsInner" + Suffix);
 iEvent.put( e1x5,  Prefix + "E1x5" + Suffix );
 iEvent.put( e5x5,  Prefix + "E5x5" + Suffix );
 iEvent.put( e2x5Max,  Prefix + "E2x5Max" + Suffix );
 iEvent.put( fbrem,  Prefix + "Fbrem" + Suffix );
 iEvent.put( hcalOverEcal,  Prefix + "HcalOverEcal" + Suffix );
 iEvent.put( hcalDepth1OverEcal,  Prefix + "HcalDepth1OverEcal" + Suffix );
 iEvent.put( hcalDepth2OverEcal,  Prefix + "HcalDepth2OverEcal" + Suffix );
 iEvent.put( eEleClusterOverPout,  Prefix + "EEleClusterOverPout" + Suffix );
 iEvent.put( eSeedClusterOverPout,  Prefix + "ESeedClusterOverPout" + Suffix );
 iEvent.put( eSeedClusterOverP,  Prefix + "ESeedClusterOverP" + Suffix );
 //Michele (this stuff was missing - AGB)
 iEvent.put (eSuperClusterEta, Prefix + "ESuperClusterEta" + Suffix);
 iEvent.put (eSuperClusterPhi, Prefix + "ESuperClusterPhi" + Suffix);
 //
 iEvent.put( eSuperClusterOverP,  Prefix + "ESuperClusterOverP" + Suffix );
 iEvent.put( deltaPhiSuperClusterTrackAtVtx,  Prefix + "DeltaPhiSuperClusterTrackAtVtx" + Suffix );
 iEvent.put( deltaEtaSuperClusterTrackAtVtx,  Prefix + "DeltaEtaSuperClusterTrackAtVtx" + Suffix );
 iEvent.put( deltaPhiSeedClusterTrackAtCalo,  Prefix + "DeltaPhiSeedClusterTrackAtCalo" + Suffix );
 iEvent.put( deltaEtaSeedClusterTrackAtCalo,  Prefix + "DeltaEtaSeedClusterTrackAtCalo" + Suffix );
 iEvent.put( deltaEtaEleClusterTrackAtCalo,  Prefix + "DeltaEtaEleClusterTrackAtCalo" + Suffix );
 iEvent.put( deltaPhiEleClusterTrackAtCalo,  Prefix + "DeltaPhiEleClusterTrackAtCalo" + Suffix );
 iEvent.put( sigmaEtaEta,  Prefix + "SigmaEtaEta" + Suffix );
 iEvent.put( sigmaIetaIeta,  Prefix + "SigmaIetaIeta" + Suffix );
 iEvent.put( classification,  Prefix + "Classification" + Suffix );
 iEvent.put( mva,  Prefix + "Mva" + Suffix );
 iEvent.put( dr03TkSumPt,  Prefix + "Dr03TkSumPt" + Suffix );
 iEvent.put( dr03EcalRecHitSumEt,  Prefix + "Dr03EcalRecHitSumEt" + Suffix );
 iEvent.put( dr03HcalTowerSumEt,  Prefix + "Dr03HcalTowerSumEt" + Suffix );
 iEvent.put( dr03HcalDepth1TowerSumEt,  Prefix + "Dr03HcalDepth1TowerSumEt" + Suffix );
 iEvent.put( dr03HcalDepth2TowerSumEt,  Prefix + "Dr03HcalDepth2TowerSumEt" + Suffix );
 iEvent.put( caloEnergy,  Prefix + "CaloEnergy" + Suffix );
 iEvent.put( ecalEnergy,  Prefix + "EcalEnergy" + Suffix );
 iEvent.put( ecalEnergyError,  Prefix + "EcalEnergyError" + Suffix );
 iEvent.put( electronMomentumError,  Prefix + "ElectronMomentumError" + Suffix );
 iEvent.put( numberOfTracks,  Prefix + "NumberOfTracks" + Suffix );
 iEvent.put( numberOfBrems,  Prefix + "NumberOfBrems" + Suffix );
 iEvent.put( shFracInnerHits,  Prefix + "ShFracInnerHits" + Suffix );
 iEvent.put( vertex,  Prefix + "Vertex" + Suffix );
 iEvent.put( vertexChi2,  Prefix + "VertexChi2" + Suffix );
 iEvent.put( vertexNdof,  Prefix + "VertexNdof" + Suffix );
 if(StoreConversionInfo) {
   iEvent.put( dist, Prefix + "ConversionDist" + Suffix );
   iEvent.put( dcot, Prefix + "ConversionDCot" + Suffix );
   iEvent.put( missingHits, Prefix + "ConversionMissingHits" + Suffix );
   iEvent.put( conversionPartnerCtfTrackTrackerExpectedHitsInner, Prefix + "ConversionPartnerCtfTrackTrackerExpectedHitsInner" + Suffix );
   iEvent.put( conversionPartnerGsfTrackTrackerExpectedHitsInner, Prefix + "ConversionPartnerGsfTrackTrackerExpectedHitsInner" + Suffix );
 }
 iEvent.put( conversionInfoStored , Prefix + "ConversionInfoStored" + Suffix );
 iEvent.put(kfcharge, Prefix + "KfTrackCharge" + Suffix);
 iEvent.put(scPixCharge, Prefix + "ScPixCharge" + Suffix);
 iEvent.put(closestCtfTrackCharge, Prefix + "ClosestCtfTrackCharge" + Suffix);
}

// extra information stored for PAT data
template< typename T >
void SusyCAF_Electron<T>::
producePAT(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<T> >& collection) {
 std::auto_ptr<std::vector<float> >  ecalIso                  ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  hcalIso                  ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  trackIso                 ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  eIDTight                 ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  eIDRobustTight           ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  eIDLoose                 ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> >  eIDRobustLoose           ( new std::vector<float>()  ) ;
 std::auto_ptr<std::vector<float> > ecalIsoDep( new std::vector<float>() );
 std::auto_ptr<std::vector<float> > hcalIsoDep( new std::vector<float>() );

 //pf

 std::auto_ptr<std::vector<int> > ispf (new std::vector<int>() );
 std::auto_ptr<std::vector<float> > ElId_pf_evspi (new std::vector<float>() );
 std::auto_ptr<std::vector<float> > partIso (new std::vector<float>() );
 std::auto_ptr<std::vector<float> > charHadIso (new std::vector<float>() );
 std::auto_ptr<std::vector<float> > neutHadIso (new std::vector<float>() );
 std::auto_ptr<std::vector<float> > photIso (new std::vector<float>() );



 if (collection.isValid()){
   for(std::vector<pat::Electron>::const_iterator it = collection->begin(); it!=collection->end(); it++) {

     ecalIso->push_back(it->ecalIso());
     hcalIso                 ->push_back(it->hcalIso                   ());
     trackIso                ->push_back(it->trackIso                  ());
     eIDTight                ->push_back(it->electronID("eidTight"));
     eIDRobustTight          ->push_back(it->electronID("eidRobustTight"));
     eIDLoose                ->push_back(it->electronID("eidLoose"));
     eIDRobustLoose          ->push_back(it->electronID("eidRobustLoose"));
     if(it->ecalIsoDeposit() && it->hcalIsoDeposit()){//this is needed to avoid the code seg faulting in 341 - NM 05/01/10
	ecalIsoDep->push_back(it->ecalIsoDeposit()->candEnergy());
	hcalIsoDep->push_back(it->hcalIsoDeposit()->candEnergy());
     }

     //pf
     ispf->push_back(it->pfCandidateRef().isAvailable()); //just for safety, could be removed later
     if(it->pfCandidateRef().isAvailable()){

	for(std::vector<std::pair<std::string, float> >::const_iterator ElIds = (it->electronIDs()).begin(); ElIds!=(it->electronIDs()).end(); ElIds++){
	  if(ElIds->first=="pf_evspi"){
	    ElId_pf_evspi ->push_back(ElIds->second);
	  }
	}
	partIso->push_back(it->particleIso());
	charHadIso->push_back(it->chargedHadronIso());
	neutHadIso->push_back(it->neutralHadronIso());
	photIso->push_back(it->photonIso());

     }
   }



   } // end loop over electrons



 iEvent.put(ecalIso                 , Prefix + "EcalIso"                  + Suffix);
 iEvent.put(hcalIso                 , Prefix + "HcalIso"                  + Suffix);
 iEvent.put(trackIso                , Prefix + "TrackIso"                 + Suffix);
 iEvent.put(eIDTight                , Prefix + "EIDTight"                 + Suffix);
 iEvent.put(eIDRobustTight          , Prefix + "EIDRobustTight"           + Suffix);
 iEvent.put(eIDLoose                , Prefix + "EIDLoose"                 + Suffix);
 iEvent.put(eIDRobustLoose          , Prefix + "EIDRobustLoose"           + Suffix);
 iEvent.put(ecalIsoDep, Prefix + "EcalIsoDep" + Suffix);
 iEvent.put(hcalIsoDep, Prefix + "HcalIsoDep" + Suffix);
 //pf stuff
 iEvent.put(ispf, Prefix + "ProducedFromPF" + Suffix);
 iEvent.put(ElId_pf_evspi, Prefix + "IdPfevspi" + Suffix);
 iEvent.put(partIso, Prefix + "ParticleIso" + Suffix);
 iEvent.put(charHadIso, Prefix + "ChargedHadronIso" + Suffix);
 iEvent.put(neutHadIso, Prefix + "NeutralHadronIso" + Suffix);
 iEvent.put(photIso, Prefix + "PhotonIso" + Suffix);
}

#endif
