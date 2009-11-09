#ifndef SUSY_CAF_ELECTRON
#define SUSY_CAF_ELECTRON

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include <string>

template< typename T >
class SusyCAF_Electron : public edm::EDProducer {
 public: 
  explicit SusyCAF_Electron(const edm::ParameterSet&);
 private:
  void initTemplate(edm::Handle<reco::GsfElectron> &);
  void initTemplate(edm::Handle<pat::Electron> &);
  void initRECO();
  void initPAT();
  void produce(edm::Event &, const edm::EventSetup & );
  void produceTemplate(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<reco::GsfElectron> > &);
  void produceTemplate(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<pat::Electron> > &);
  void produceRECO(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &);
  void producePAT(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &);

  typedef reco::Candidate::LorentzVector LorentzVector; 

  const edm::InputTag inputTag;
  const std::string Prefix,Suffix;
};

template< typename T >
SusyCAF_Electron<T>::SusyCAF_Electron(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
  Prefix(iConfig.getParameter<std::string>("Prefix")),
  Suffix(iConfig.getParameter<std::string>("Suffix"))
{
  edm::Handle<T> dataType;
  initTemplate(dataType);
}

// init method in case of RECO data
template< typename T >
void SusyCAF_Electron<T>::initTemplate(edm::Handle<reco::GsfElectron>& dataType)
{
  initRECO();
}

// init method in case of PAT data
template< typename T >
void SusyCAF_Electron<T>::initTemplate(edm::Handle<pat::Electron>& dataType)
{
  initRECO();
  initPAT();
}

template< typename T >
void SusyCAF_Electron<T>::initRECO()
{
  produces <std::vector<reco::Candidate::LorentzVector> > ( Prefix + "P4" + Suffix );
  produces <std::vector<int> > (  Prefix + "Charge" + Suffix);
  produces <std::vector<double> > (  Prefix + "GsfTracknormalizedChi2" + Suffix);
  produces <std::vector<double> > (  Prefix + "GsfTracknumberOfValidHits" + Suffix);
  produces <std::vector<double> > (  Prefix + "GsfTrackdxy" + Suffix);
  produces <std::vector<double> > (  Prefix + "GsfTrackdxyError" + Suffix);
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
  produces <std::vector<double> > (  Prefix + "Vx" + Suffix);
  produces <std::vector<double> > (  Prefix + "Vy" + Suffix);
  produces <std::vector<double> > (  Prefix + "Vz" + Suffix);
  produces <std::vector<double> > (  Prefix + "VertexChi2" + Suffix);
  produces <std::vector<double> > (  Prefix + "VertexNdof" + Suffix);
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
}

template< typename T >
void SusyCAF_Electron<T>::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  edm::Handle<std::vector<T> > collection;
  iEvent.getByLabel(inputTag,collection);

  produceTemplate(iEvent, iSetup, collection);
}

// produce method in case of RECO data
template< typename T >
void SusyCAF_Electron<T>::
produceTemplate(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<reco::GsfElectron> >& collection) {
  produceRECO(iEvent, iSetup, collection);
}

// produce method in case of PAT data
template< typename T >
void SusyCAF_Electron<T>::
produceTemplate(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<pat::Electron> >& collection) {
  produceRECO(iEvent, iSetup, collection);
  producePAT(iEvent, iSetup, collection);
}

template< typename T >
void SusyCAF_Electron<T>::
produceRECO(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<T> >& collection) {
  std::auto_ptr<std::vector<reco::Candidate::LorentzVector> > p4 ( new std::vector<reco::Candidate::LorentzVector>() );
  std::auto_ptr<std::vector<int> >  charge   ( new std::vector<int>()  ) ;
  std::auto_ptr<std::vector<double> >  gsfTrack_normalizedChi2   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  gsfTrack_numberOfValidHits   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  gsfTrack_dxy   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  gsfTrack_dxyError   ( new std::vector<double>()  ) ;
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
  std::auto_ptr<std::vector<double> >  vx   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  vy   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  vz   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  vertexChi2   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  vertexNdof   ( new std::vector<double>()  ) ;
  
  for(typename std::vector<T>::const_iterator it = collection->begin(); it!=collection->end(); it++) {
    p4->push_back(it->p4());
    charge->push_back(it->charge());
    gsfTrack_normalizedChi2->push_back(it->gsfTrack()->normalizedChi2());
    gsfTrack_numberOfValidHits->push_back(it->gsfTrack()->numberOfValidHits());
    gsfTrack_dxy->push_back(it->gsfTrack()->dxy());
    gsfTrack_dxyError->push_back(it->gsfTrack()->dxyError());
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
    vx->push_back(it->vx());
    vy->push_back(it->vy());
    vz->push_back(it->vz());
    vertexChi2->push_back(it->vertexChi2());
    vertexNdof->push_back(it->vertexNdof());
  }
 
  iEvent.put( p4,  Prefix + "P4" + Suffix ); 
  iEvent.put( charge,  Prefix + "Charge" + Suffix );
  iEvent.put( gsfTrack_normalizedChi2,  Prefix + "GsfTracknormalizedChi2" + Suffix );
  iEvent.put( gsfTrack_numberOfValidHits,  Prefix + "GsfTracknumberOfValidHits" + Suffix );
  iEvent.put( gsfTrack_dxy,  Prefix + "GsfTrackdxy" + Suffix );
  iEvent.put( gsfTrack_dxyError,  Prefix + "GsfTrackdxyError" + Suffix );
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
  iEvent.put( vx,  Prefix + "Vx" + Suffix );
  iEvent.put( vy,  Prefix + "Vy" + Suffix );
  iEvent.put( vz,  Prefix + "Vz" + Suffix );
  iEvent.put( vertexChi2,  Prefix + "VertexChi2" + Suffix );
  iEvent.put( vertexNdof,  Prefix + "VertexNdof" + Suffix );
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

  for(std::vector<pat::Electron>::const_iterator it = collection->begin(); it!=collection->end(); it++) { 
    ecalIso                 ->push_back(it->ecalIso                   ());
    hcalIso                 ->push_back(it->hcalIso                   ());
    trackIso                ->push_back(it->trackIso                  ());
    eIDTight                ->push_back(it->electronID("eidTight"));
    eIDRobustTight          ->push_back(it->electronID("eidRobustTight"));
    eIDLoose                ->push_back(it->electronID("eidLoose"));
    eIDRobustLoose          ->push_back(it->electronID("eidRobustLoose"));
  } // end loop over electrons


  iEvent.put(ecalIso                 , Prefix + "EcalIso"                  + Suffix);
  iEvent.put(hcalIso                 , Prefix + "HcalIso"                  + Suffix);
  iEvent.put(trackIso                , Prefix + "TrackIso"                 + Suffix);
  iEvent.put(eIDTight                , Prefix + "EIDTight"                 + Suffix);
  iEvent.put(eIDRobustTight          , Prefix + "EIDRobustTight"           + Suffix);
  iEvent.put(eIDLoose                , Prefix + "EIDLoose"                 + Suffix);
  iEvent.put(eIDRobustLoose          , Prefix + "EIDRobustLoose"           + Suffix);
}

#endif
