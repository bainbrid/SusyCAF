#ifndef SUSY_CAF_MUON
#define SUSY_CAF_MUON

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include <string>

template< typename T >
class SusyCAF_Muon : public edm::EDProducer {
 public: 
  explicit SusyCAF_Muon(const edm::ParameterSet&);
 private: 
  void initTemplate(edm::Handle<reco::Muon> &);
  void initTemplate(edm::Handle<pat::Muon> &);
  void initRECO();
  void initPAT();
  void produce(edm::Event &, const edm::EventSetup & );
  void produceTemplate(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<reco::Muon> > &);
  void produceTemplate(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<pat::Muon> > &);
  void produceRECO(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &);
  void producePAT(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &);

  typedef reco::Candidate::LorentzVector LorentzVector;
  const edm::InputTag inputTag;
  const std::string Prefix,Suffix;
};

template< typename T >
SusyCAF_Muon<T>::SusyCAF_Muon(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
  Prefix(iConfig.getParameter<std::string>("Prefix")),
  Suffix(iConfig.getParameter<std::string>("Suffix"))
{
  edm::Handle<T> dataType;
  initTemplate(dataType);
}

// init method in case of RECO data
template< typename T >
void SusyCAF_Muon<T>::initTemplate(edm::Handle<reco::Muon>& dataType)
{
  initRECO();
}

// init method in case of PAT data
template< typename T >
void SusyCAF_Muon<T>::initTemplate(edm::Handle<pat::Muon>& dataType)
{
  initRECO();
  initPAT();
}

template< typename T >
void SusyCAF_Muon<T>::initRECO()
{
  produces <std::vector<LorentzVector> > ( Prefix + "P4" + Suffix );
  produces <std::vector<int> > (  Prefix + "Charge" + Suffix);
  produces <std::vector<double> > (  Prefix + "GlobalTracknormalizedChi2" + Suffix);
  produces <std::vector<double> > (  Prefix + "GlobalTracknumberOfValidHits" + Suffix);
  produces <std::vector<double> > (  Prefix + "GlobalTrackdxy" + Suffix);
  produces <std::vector<double> > (  Prefix + "GlobalTrackdxyError" + Suffix);
  produces <std::vector<float> > (  Prefix + "CaloCompatibility" + Suffix);
  produces <std::vector<float> > (  Prefix + "IsolationR03sumPt" + Suffix);
  produces <std::vector<float> > (  Prefix + "IsolationR03emEt" + Suffix);
  produces <std::vector<float> > (  Prefix + "IsolationR03hadEt" + Suffix);
  produces <std::vector<double> > (  Prefix + "Vx" + Suffix);
  produces <std::vector<double> > (  Prefix + "Vy" + Suffix);
  produces <std::vector<double> > (  Prefix + "Vz" + Suffix);
  produces <std::vector<double> > (  Prefix + "VertexChi2" + Suffix);
  produces <std::vector<double> > (  Prefix + "VertexNdof" + Suffix);
  produces <std::vector<bool> > (  Prefix + "IsGlobalMuon" + Suffix);
  produces <std::vector<bool> > (  Prefix + "IsTrackerMuon" + Suffix);
  produces <std::vector<bool> > (  Prefix + "IsStandAloneMuon" + Suffix);
}

// extra information stored for PAT data
template< typename T >
void SusyCAF_Muon<T>::initPAT()
{
  produces <std::vector<bool> > (Prefix + "MuonIDGlobalMuonPromptTight" + Suffix);
  produces <std::vector<float> > (Prefix + "EcalIso" + Suffix);
  produces <std::vector<float> > (Prefix + "HcalIso" + Suffix);
  produces <std::vector<float> > (Prefix + "TrackIso" + Suffix);
}


template< typename T >
void SusyCAF_Muon<T>::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  edm::Handle<std::vector<T> > collection;
  iEvent.getByLabel(inputTag,collection);

  produceTemplate(iEvent, iSetup, collection);
}

// produce method in case of RECO data
template< typename T >
void SusyCAF_Muon<T>::
produceTemplate(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<reco::Muon> >& collection) {
  produceRECO(iEvent, iSetup, collection);
}

// produce method in case of PAT data
template< typename T >
void SusyCAF_Muon<T>::
produceTemplate(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<pat::Muon> >& collection) {
  produceRECO(iEvent, iSetup, collection);
  producePAT(iEvent, iSetup, collection);
}

template< typename T >
void SusyCAF_Muon<T>::
produceRECO(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<T> >& collection) {
  std::auto_ptr<std::vector<LorentzVector> > p4 ( new std::vector<LorentzVector>() );
  std::auto_ptr<std::vector<int> >  charge   ( new std::vector<int>()  ) ;
  std::auto_ptr<std::vector<double> >  globalTrack_normalizedChi2   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  globalTrack_numberOfValidHits   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  globalTrack_dxy   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  globalTrack_dxyError   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<float> >  caloCompatibility   ( new std::vector<float>()  ) ;
  std::auto_ptr<std::vector<float> >  isolationR03sumPt   ( new std::vector<float>()  ) ;
  std::auto_ptr<std::vector<float> >  isolationR03emEt   ( new std::vector<float>()  ) ;
  std::auto_ptr<std::vector<float> >  isolationR03hadEt   ( new std::vector<float>()  ) ;
  std::auto_ptr<std::vector<double> >  vx   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  vy   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  vz   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  vertexChi2   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  vertexNdof   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<bool> >  isGlobalMuon   ( new std::vector<bool>()  ) ;
  std::auto_ptr<std::vector<bool> >  isTrackerMuon   ( new std::vector<bool>()  ) ;
  std::auto_ptr<std::vector<bool> >  isStandAloneMuon   ( new std::vector<bool>()  ) ;
  
  
  for(typename std::vector<T>::const_iterator it = collection->begin(); it!=collection->end(); it++) {
    p4->push_back(it->p4());
    charge->push_back(it->charge());
    if( it->isGlobalMuon()){
    	globalTrack_normalizedChi2->push_back(it->globalTrack()->normalizedChi2());
    	globalTrack_numberOfValidHits->push_back(it->globalTrack()->numberOfValidHits());
    	globalTrack_dxy->push_back(it->globalTrack()->dxy());
    	globalTrack_dxyError->push_back(it->globalTrack()->dxyError());
    }
    else {
    	globalTrack_normalizedChi2->push_back(999999999.);
    	globalTrack_numberOfValidHits->push_back(-1.);
    	globalTrack_dxy->push_back(999999999.);
    	globalTrack_dxyError->push_back(999999999.);
    }	
    caloCompatibility->push_back(it->caloCompatibility());
    isolationR03sumPt->push_back(it->isolationR03().sumPt);
    isolationR03emEt->push_back(it->isolationR03().emEt);
    isolationR03hadEt->push_back(it->isolationR03().hadEt);
    vx->push_back(it->vx());
    vy->push_back(it->vy());
    vz->push_back(it->vz());
    vertexChi2->push_back(it->vertexChi2());
    vertexNdof->push_back(it->vertexNdof());
    isGlobalMuon->push_back(it->isGlobalMuon());
    isTrackerMuon->push_back(it->isTrackerMuon());
    isStandAloneMuon->push_back(it->isStandAloneMuon());
  }
  
  iEvent.put( p4,  Prefix + "P4" + Suffix );
  iEvent.put( charge,  Prefix + "Charge" + Suffix );
  iEvent.put( globalTrack_normalizedChi2,  Prefix + "GlobalTracknormalizedChi2" + Suffix );
  iEvent.put( globalTrack_numberOfValidHits,  Prefix + "GlobalTracknumberOfValidHits" + Suffix );
  iEvent.put( globalTrack_dxy,  Prefix + "GlobalTrackdxy" + Suffix );
  iEvent.put( globalTrack_dxyError,  Prefix + "GlobalTrackdxyError" + Suffix );
  iEvent.put( caloCompatibility,  Prefix + "CaloCompatibility" + Suffix );
  iEvent.put( isolationR03sumPt,  Prefix + "IsolationR03sumPt" + Suffix );
  iEvent.put( isolationR03emEt,  Prefix + "IsolationR03emEt" + Suffix );
  iEvent.put( isolationR03hadEt,  Prefix + "IsolationR03hadEt" + Suffix );
  iEvent.put( vx,  Prefix + "Vx" + Suffix );
  iEvent.put( vy,  Prefix + "Vy" + Suffix );
  iEvent.put( vz,  Prefix + "Vz" + Suffix );
  iEvent.put( vertexChi2,  Prefix + "VertexChi2" + Suffix );
  iEvent.put( vertexNdof,  Prefix + "VertexNdof" + Suffix );
  iEvent.put( isGlobalMuon,  Prefix + "IsGlobalMuon" + Suffix );
  iEvent.put( isTrackerMuon,  Prefix + "IsTrackerMuon" + Suffix );
  iEvent.put( isStandAloneMuon,  Prefix + "IsStandAloneMuon" + Suffix );
}

// extra information stored for PAT data
template< typename T >
void SusyCAF_Muon<T>::
producePAT(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<T> >& collection) {
  std::auto_ptr<std::vector<bool> >  muonIDGlobalMuonPromptTight( new std::vector<bool>() );
  std::auto_ptr<std::vector<float> >  ecalIso( new std::vector<float>() );
  std::auto_ptr<std::vector<float> >  hcalIso( new std::vector<float>() );
  std::auto_ptr<std::vector<float> >  trackIso( new std::vector<float>() );
  
  for(typename std::vector<T>::const_iterator it = collection->begin(); it!=collection->end(); it++) {
    if( !it->isGlobalMuon()) continue;
    muonIDGlobalMuonPromptTight->push_back(it->muonID("GlobalMuonPromptTight"));
    ecalIso->push_back(it->ecalIso());
    hcalIso->push_back(it->hcalIso());
    trackIso->push_back(it->trackIso());
  }
  
  iEvent.put(muonIDGlobalMuonPromptTight, Prefix + "MuonIDGlobalMuonPromptTight" + Suffix );
  iEvent.put(ecalIso, Prefix + "EcalIso" + Suffix);
  iEvent.put(hcalIso, Prefix + "HcalIso" + Suffix);
  iEvent.put(trackIso, Prefix + "TrackIso" + Suffix);
}

#endif
