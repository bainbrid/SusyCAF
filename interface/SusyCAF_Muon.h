#ifndef SUSY_CAF_MUON
#define SUSY_CAF_MUON

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_functions.h"
#include <string>

template< typename T >
class SusyCAF_Muon : public edm::EDProducer {
 public: 
  explicit SusyCAF_Muon(const edm::ParameterSet&);
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
};

template< typename T >
SusyCAF_Muon<T>::SusyCAF_Muon(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
  Prefix(iConfig.getParameter<std::string>("Prefix")),
  Suffix(iConfig.getParameter<std::string>("Suffix"))
{
  initTemplate();
}

template< typename T >
void SusyCAF_Muon<T>::initRECO()
{
  produces <bool> (  Prefix + "HandleValid" + Suffix);
  produces <std::vector<LorentzVector> > ( Prefix + "P4" + Suffix );
  produces <std::vector<int> > (  Prefix + "Charge" + Suffix);
  produces <std::vector<double> > (  Prefix + "GlobalTracknormalizedChi2" + Suffix);
  produces <std::vector<unsigned> > (  Prefix + "GlobalTracknumberOfValidHits" + Suffix);

  produces <std::vector<double> > (  Prefix + "GlobalTrackDxy" + Suffix);
  produces <std::vector<double> > (  Prefix + "GlobalTrackDz" + Suffix);
  produces <std::vector<double> > (  Prefix + "GlobalTrackDxyBS" + Suffix);
  produces <std::vector<double> > (  Prefix + "GlobalTrackDzBS" + Suffix);
  produces <std::vector<double> > (  Prefix + "GlobalTrackDxyError" + Suffix);
  produces <std::vector<double> > (  Prefix + "GlobalTrackDzError" + Suffix);

  produces <std::vector<double> > (  Prefix + "InnerTrackDxy" + Suffix);
  produces <std::vector<double> > (  Prefix + "InnerTrackDxyBS" + Suffix);
  produces <std::vector<double> > (  Prefix + "InnerTrackDz" + Suffix);
  produces <std::vector<double> > (  Prefix + "InnerTrackDzBS" + Suffix);
  produces <std::vector<double> > (  Prefix + "InnerTrackDxyError" + Suffix);
  produces <std::vector<double> > (  Prefix + "InnerTrackDzError" + Suffix);

  produces <std::vector<double> > (  Prefix + "InnerTrackNormalizedChi2" + Suffix);
  produces <std::vector<unsigned> > (  Prefix + "InnerTrackNumberOfValidHits" + Suffix);

  produces <std::vector<double> > (  Prefix + "OuterTrackNormalizedChi2" + Suffix);
  produces <std::vector<unsigned> > (  Prefix + "OuterTrackNumberOfValidHits" + Suffix);
  produces <std::vector<float> > (  Prefix + "CaloCompatibility" + Suffix);
  produces <std::vector<float> > (  Prefix + "IsolationR03sumPt" + Suffix);
  produces <std::vector<float> > (  Prefix + "IsolationR03emEt" + Suffix);
  produces <std::vector<float> > (  Prefix + "IsolationR03hadEt" + Suffix);
  produces <std::vector<math::XYZPoint> > (  Prefix + "Vertex" + Suffix);
  produces <std::vector<double> > (  Prefix + "VertexChi2" + Suffix);
  produces <std::vector<double> > (  Prefix + "VertexNdof" + Suffix);
  produces <std::vector<int> > (  Prefix + "IsGlobalMuon" + Suffix);
  produces <std::vector<int> > (  Prefix + "IsTrackerMuon" + Suffix);
  produces <std::vector<int> > (  Prefix + "IsStandAloneMuon" + Suffix);
}

// extra information stored for PAT data
template< typename T >
void SusyCAF_Muon<T>::initPAT()
{
  produces <std::vector<int> > (Prefix + "IDGlobalMuonPromptTight" + Suffix);
  produces <std::vector<int> > (Prefix + "TMLastStationAngTight" + Suffix);
  produces <std::vector<int> > (Prefix + "TMLastStationOptimizedLowPtTight" + Suffix);
  produces <std::vector<int> > (Prefix + "TMLastStationOptimizedLowPtLoose" + Suffix);
  produces <std::vector<int> > (Prefix + "TMLastStationOptimizedBarrelLowPtTight" + Suffix);
  produces <std::vector<int> > (Prefix + "TMLastStationOptimizedBarrelLowPtLoose" + Suffix);
  produces <std::vector<float> > (Prefix + "EcalIso" + Suffix);
  produces <std::vector<float> > (Prefix + "HcalIso" + Suffix);
  produces <std::vector<float> > (Prefix + "TrackIso" + Suffix);

  produces <std::vector<int> > (Prefix + "TrackerMuonArbitrated" + Suffix);
  produces <std::vector<int> > (Prefix + "AllArbitrated" + Suffix);
  produces <std::vector<int> > (Prefix + "TMLastStationLoose" + Suffix);
  produces <std::vector<int> > (Prefix + "TMLastStationTight" + Suffix);
  produces <std::vector<int> > (Prefix + "TM2DCompatibilityLoose" + Suffix);
  produces <std::vector<int> > (Prefix + "TM2DCompatibilityTight" + Suffix);
  produces <std::vector<int> > (Prefix + "TMOneStationLoose" + Suffix);
  produces <std::vector<int> > (Prefix + "TMOneStationTight" + Suffix);
  produces <std::vector<int> > (Prefix + "GMTkChiCompatibility" + Suffix);
  produces <std::vector<int> > (Prefix + "GMStaChiCompatibility" + Suffix);
  produces <std::vector<int> > (Prefix + "GMTkKinkTight" + Suffix);
  produces <std::vector<int> > (Prefix + "TMLastStationAngLoose" + Suffix);
  produces <std::vector<int> > (Prefix + "TMOneStationAngLoose" + Suffix);
  produces <std::vector<int> > (Prefix + "TMOneStationAngTight" + Suffix);


//pf muons - AGB 18/12/09
  produces <std::vector<int> > (Prefix + "ProducedFromPF" + Suffix);
  produces <std::vector<float> > (Prefix + "ParticleIso" + Suffix);
  produces <std::vector<float> > (Prefix + "ChargedHadronIso" + Suffix);
  produces <std::vector<float> > (Prefix + "NeutralHadronIso" + Suffix);
  produces <std::vector<float> > (Prefix + "PhotonIso" + Suffix);

}


template< typename T >
void SusyCAF_Muon<T>::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  edm::Handle<std::vector<T> > collection;
  iEvent.getByLabel(inputTag,collection);

  produceTemplate(iEvent, iSetup, collection);
}


template< typename T >
void SusyCAF_Muon<T>::
produceRECO(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<T> >& collection) {
  std::auto_ptr<bool> isHandleValid ( new bool(collection.isValid()) );
  std::auto_ptr<std::vector<LorentzVector> > p4 ( new std::vector<LorentzVector>() );
  std::auto_ptr<std::vector<int> >  charge   ( new std::vector<int>()  ) ;
  std::auto_ptr<std::vector<double> >  globalTrack_normalizedChi2   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<unsigned> >    globalTrack_numberOfValidHits   ( new std::vector<unsigned>()  ) ;
  std::auto_ptr<std::vector<double> >  globalTrack_dxy   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  globalTrack_dz   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  globalTrack_dxyBS   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  globalTrack_dzBS   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  globalTrack_dxyError   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  globalTrack_dzError   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  innerTrack_normalizedChi2   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<unsigned> >    innerTrack_numberOfValidHits   ( new std::vector<unsigned>()  ) ;
  std::auto_ptr<std::vector<double> >  innerTrack_dxy   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  innerTrack_dxyBS   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  innerTrack_dxyError   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  innerTrack_dz   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  innerTrack_dzBS   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  innerTrack_dzError   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  outerTrack_normalizedChi2   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<unsigned> >    outerTrack_numberOfValidHits   ( new std::vector<unsigned>()  ) ;
  std::auto_ptr<std::vector<float> >  caloCompatibility   ( new std::vector<float>()  ) ;
  std::auto_ptr<std::vector<float> >  isolationR03sumPt   ( new std::vector<float>()  ) ;
  std::auto_ptr<std::vector<float> >  isolationR03emEt   ( new std::vector<float>()  ) ;
  std::auto_ptr<std::vector<float> >  isolationR03hadEt   ( new std::vector<float>()  ) ;
  std::auto_ptr<std::vector<math::XYZPoint> > vertex   ( new std::vector<math::XYZPoint>()  ) ;
  std::auto_ptr<std::vector<double> >  vertexChi2   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  vertexNdof   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<int> >  isGlobalMuon   ( new std::vector<int>()  ) ;
  std::auto_ptr<std::vector<int> >  isTrackerMuon   ( new std::vector<int>()  ) ;
  std::auto_ptr<std::vector<int> >  isStandAloneMuon   ( new std::vector<int>()  ) ;

  math::XYZPoint bs = math::XYZPoint(0.,0.,0.);
  math::XYZPoint vx = math::XYZPoint(0.,0.,0.);
  edm::Handle<reco::BeamSpot> beamspots;  iEvent.getByLabel("offlineBeamSpot", beamspots);
  edm::Handle<reco::VertexCollection> vertices; iEvent.getByLabel("offlinePrimaryVertices", vertices);
  if (beamspots.isValid()){ bs = beamspots->position();}
     
  if (collection.isValid()) {
    for(typename std::vector<T>::const_iterator it = collection->begin(); it!=collection->end(); it++) {
      p4->push_back(it->p4());
      charge->push_back(it->charge());
      caloCompatibility->push_back(it->caloCompatibility());
      isolationR03sumPt->push_back(it->isolationR03().sumPt);
      isolationR03emEt->push_back(it->isolationR03().emEt);
      isolationR03hadEt->push_back(it->isolationR03().hadEt);
      vertex->push_back(it->vertex());
      vertexChi2->push_back(it->vertexChi2());
      vertexNdof->push_back(it->vertexNdof());
      isGlobalMuon->push_back(it->isGlobalMuon());
      isTrackerMuon->push_back(it->isTrackerMuon());
      isStandAloneMuon->push_back(it->isStandAloneMuon());

      bool global = it->globalTrack().isNonnull();
      if(global && vertices.isValid() && vertices->size()) vx = SusyCAF_functions::closestDzPrimaryVertexPosition(it->globalTrack().get(),*vertices);
      globalTrack_dxy->push_back( global? it->globalTrack()->dxy(vx) : 999999999.);
      globalTrack_dz->push_back( global? it->globalTrack()->dz(vx) : 999999999.);
      globalTrack_dxyBS->push_back( global? it->globalTrack()->dxy(bs) : 999999999.);
      globalTrack_dzBS->push_back( global? it->globalTrack()->dz(bs) : 999999999.);
      globalTrack_dxyError->push_back( global? it->globalTrack()->dxyError() : -10000);
      globalTrack_dzError->push_back( global? it->globalTrack()->dzError() : -10000);
      globalTrack_normalizedChi2->push_back( global? it->globalTrack()->normalizedChi2() : -1);
      globalTrack_numberOfValidHits->push_back( global? it->globalTrack()->numberOfValidHits() : 0);

      bool inner = it->innerTrack().isNonnull();
      if(inner && vertices.isValid() && vertices->size()) vx = SusyCAF_functions::closestDzPrimaryVertexPosition(it->innerTrack().get(),*vertices);
      innerTrack_dxy->push_back( inner? it->innerTrack()->dxy(vx) : 999999999.);
      innerTrack_dz->push_back( inner? it->innerTrack()->dz(vx) : 999999999.);
      innerTrack_dxyBS->push_back( inner? it->innerTrack()->dxy(bs) : 999999999.);
      innerTrack_dzBS->push_back( inner? it->innerTrack()->dz(bs) : 999999999.);
      innerTrack_dxyError->push_back( inner? it->innerTrack()->dxyError() : -10000);
      innerTrack_dzError->push_back( inner? it->innerTrack()->dzError() : -10000);
      innerTrack_normalizedChi2->push_back( inner? it->innerTrack()->normalizedChi2() : -1);
      innerTrack_numberOfValidHits->push_back( inner? it->innerTrack()->numberOfValidHits() : 0);

      bool outer = it->outerTrack().isNonnull();
      outerTrack_normalizedChi2->push_back( outer? it->outerTrack()->normalizedChi2() : -1);
      outerTrack_numberOfValidHits->push_back(outer? it->outerTrack()->numberOfValidHits() : 0);
    }
  }
  
  iEvent.put( isHandleValid,  Prefix + "HandleValid" + Suffix );
  iEvent.put( p4,  Prefix + "P4" + Suffix );
  iEvent.put( charge,  Prefix + "Charge" + Suffix );
  iEvent.put( globalTrack_normalizedChi2,  Prefix + "GlobalTracknormalizedChi2" + Suffix );
  iEvent.put( globalTrack_numberOfValidHits,  Prefix + "GlobalTracknumberOfValidHits" + Suffix );
  iEvent.put( globalTrack_dxy,  Prefix + "GlobalTrackDxy" + Suffix );
  iEvent.put( globalTrack_dz,  Prefix + "GlobalTrackDz" + Suffix );
  iEvent.put( globalTrack_dxyBS,  Prefix + "GlobalTrackDxyBS" + Suffix );
  iEvent.put( globalTrack_dzBS,  Prefix + "GlobalTrackDzBS" + Suffix );
  iEvent.put( globalTrack_dxyError,  Prefix + "GlobalTrackDxyError" + Suffix );
  iEvent.put( globalTrack_dzError,  Prefix + "GlobalTrackDzError" + Suffix );
  iEvent.put( innerTrack_dxy,  Prefix + "InnerTrackDxy" + Suffix );
  iEvent.put( innerTrack_dz,  Prefix + "InnerTrackDz" + Suffix );
  iEvent.put( innerTrack_dxyBS,  Prefix + "InnerTrackDxyBS" + Suffix );
  iEvent.put( innerTrack_dzBS,  Prefix + "InnerTrackDzBS" + Suffix );
  iEvent.put( innerTrack_dxyError,  Prefix + "InnerTrackDxyError" + Suffix );
  iEvent.put( innerTrack_dzError,  Prefix + "InnerTrackDzError" + Suffix );
  iEvent.put( innerTrack_normalizedChi2,  Prefix + "InnerTrackNormalizedChi2" + Suffix );
  iEvent.put( innerTrack_numberOfValidHits,  Prefix + "InnerTrackNumberOfValidHits" + Suffix );
  iEvent.put( outerTrack_normalizedChi2,  Prefix + "OuterTrackNormalizedChi2" + Suffix );
  iEvent.put( outerTrack_numberOfValidHits,  Prefix + "OuterTrackNumberOfValidHits" + Suffix );
  iEvent.put( caloCompatibility,  Prefix + "CaloCompatibility" + Suffix );
  iEvent.put( isolationR03sumPt,  Prefix + "IsolationR03sumPt" + Suffix );
  iEvent.put( isolationR03emEt,  Prefix + "IsolationR03emEt" + Suffix );
  iEvent.put( isolationR03hadEt,  Prefix + "IsolationR03hadEt" + Suffix );
  iEvent.put( vertex,      Prefix + "Vertex" + Suffix );
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
  std::auto_ptr<std::vector<int> >  IDGlobalMuonPromptTight( new std::vector<int>() );
  std::auto_ptr<std::vector<int> > TMLastStationAngTight( new std::vector<int>() );
  std::auto_ptr<std::vector<int> > TMLastStationOptimLowPtTight (new std::vector<int>());
  std::auto_ptr<std::vector<int> > TMLastStationOptimLowPtLoose (new std::vector<int>());
  std::auto_ptr<std::vector<int> > TMLastStationOptimBarrelLowPtTight (new std::vector<int>());
  std::auto_ptr<std::vector<int> > TMLastStationOptimBarrelLowPtLoose (new std::vector<int>());
  std::auto_ptr<std::vector<float> >  ecalIso( new std::vector<float>() );
  std::auto_ptr<std::vector<float> >  hcalIso( new std::vector<float>() );
  std::auto_ptr<std::vector<float> >  trackIso( new std::vector<float>() );

  std::auto_ptr<std::vector<int> > TrackerMuonArbitrated_( new std::vector<int>() );
  std::auto_ptr<std::vector<int> > AllArbitrated_( new std::vector<int>() );
  std::auto_ptr<std::vector<int> > TMLastStationLoose_( new std::vector<int>() );
  std::auto_ptr<std::vector<int> > TMLastStationTight_( new std::vector<int>() );
  std::auto_ptr<std::vector<int> > TM2DCompatibilityLoose_( new std::vector<int>() );
  std::auto_ptr<std::vector<int> > TM2DCompatibilityTight_( new std::vector<int>() );
  std::auto_ptr<std::vector<int> > TMOneStationLoose_( new std::vector<int>() );
  std::auto_ptr<std::vector<int> > TMOneStationTight_( new std::vector<int>() );
  std::auto_ptr<std::vector<int> > GMTkChiCompatibility_( new std::vector<int>() );
  std::auto_ptr<std::vector<int> > GMStaChiCompatibility_( new std::vector<int>() );
  std::auto_ptr<std::vector<int> > GMTkKinkTight_( new std::vector<int>() );
  std::auto_ptr<std::vector<int> > TMLastStationAngLoose_( new std::vector<int>() );
  std::auto_ptr<std::vector<int> > TMOneStationAngLoose_( new std::vector<int>() );
  std::auto_ptr<std::vector<int> > TMOneStationAngTight_( new std::vector<int>() );

//pf
  
  std::auto_ptr<std::vector<int> > ispf (new std::vector<int>() );
  std::auto_ptr<std::vector<float> > partIso (new std::vector<float>() );
  std::auto_ptr<std::vector<float> > charHadIso (new std::vector<float>() );
  std::auto_ptr<std::vector<float> > neutHadIso (new std::vector<float>() );
  std::auto_ptr<std::vector<float> > photIso (new std::vector<float>() );
  
  if (collection.isValid()){
    for(typename std::vector<T>::const_iterator it = collection->begin(); it!=collection->end(); it++) {
      IDGlobalMuonPromptTight->push_back(it->muonID("GlobalMuonPromptTight"));
      TMLastStationAngTight->push_back(it->muonID("TMLastStationAngTight"));
      TMLastStationOptimLowPtTight->push_back(it->muonID("TMLastStationOptimizedLowPtTight"));
      TMLastStationOptimLowPtLoose->push_back(it->muonID("TMLastStationOptimizedLowPtLoose"));
      TMLastStationOptimBarrelLowPtTight->push_back(it->muonID("TMLastStationOptimizedBarrelLowPtTight"));
      TMLastStationOptimBarrelLowPtLoose->push_back(it->muonID("TMLastStationOptimizedBarrelLowPtLoose"));
  
  TrackerMuonArbitrated_->push_back(it->muonID("TrackerMuonArbitrated"));
  AllArbitrated_->push_back(it->muonID("AllArbitrated"));
  TMLastStationLoose_->push_back(it->muonID("TMLastStationLoose"));
  TMLastStationTight_->push_back(it->muonID("TMLastStationTight"));
  TM2DCompatibilityLoose_->push_back(it->muonID("TM2DCompatibilityLoose"));
  TM2DCompatibilityTight_->push_back(it->muonID("TM2DCompatibilityTight"));
  TMOneStationLoose_->push_back(it->muonID("TMOneStationLoose"));
  TMOneStationTight_->push_back(it->muonID("TMOneStationTight"));
  GMTkChiCompatibility_->push_back(it->muonID("GMTkChiCompatibility"));
  GMStaChiCompatibility_->push_back(it->muonID("GMStaChiCompatibility"));
  GMTkKinkTight_->push_back(it->muonID("GMTkKinkTight"));
  TMLastStationAngLoose_->push_back(it->muonID("TMLastStationAngLoose"));
  TMOneStationAngLoose_->push_back(it->muonID("TMOneStationAngLoose"));
  TMOneStationAngTight_->push_back(it->muonID("TMOneStationAngTight"));
      
      ecalIso->push_back(it->ecalIso());
      hcalIso->push_back(it->hcalIso());
      trackIso->push_back(it->trackIso());
    

 //pf
      ispf->push_back(it->pfCandidateRef().isAvailable()); //just for safety, could be removed later
      
      if(it->pfCandidateRef().isAvailable()){

	partIso->push_back(it->particleIso());
	charHadIso->push_back(it->chargedHadronIso());
	neutHadIso->push_back(it->neutralHadronIso());
	photIso->push_back(it->photonIso());
      }
    }
  }
  
  iEvent.put(IDGlobalMuonPromptTight, Prefix + "IDGlobalMuonPromptTight" + Suffix );
  iEvent.put(TMLastStationAngTight, Prefix + "TMLastStationAngTight" + Suffix);
  iEvent.put(TMLastStationOptimLowPtTight, Prefix + "TMLastStationOptimizedLowPtTight" + Suffix);
  iEvent.put(TMLastStationOptimLowPtLoose, Prefix + "TMLastStationOptimizedLowPtLoose" + Suffix);
  iEvent.put(TMLastStationOptimBarrelLowPtTight, Prefix + "TMLastStationOptimizedBarrelLowPtTight" + Suffix);
  iEvent.put(TMLastStationOptimBarrelLowPtLoose, Prefix + "TMLastStationOptimizedBarrelLowPtLoose" + Suffix);

  iEvent.put(TrackerMuonArbitrated_, Prefix + "TrackerMuonArbitrated" + Suffix);
  iEvent.put(AllArbitrated_, Prefix + "AllArbitrated" + Suffix);
  iEvent.put(TMLastStationLoose_, Prefix + "TMLastStationLoose" + Suffix);
  iEvent.put(TMLastStationTight_, Prefix + "TMLastStationTight" + Suffix);
  iEvent.put(TM2DCompatibilityLoose_, Prefix + "TM2DCompatibilityLoose" + Suffix);
  iEvent.put(TM2DCompatibilityTight_, Prefix + "TM2DCompatibilityTight" + Suffix);
  iEvent.put(TMOneStationLoose_, Prefix + "TMOneStationLoose" + Suffix);
  iEvent.put(TMOneStationTight_, Prefix + "TMOneStationTight" + Suffix);
  iEvent.put(GMTkChiCompatibility_, Prefix + "GMTkChiCompatibility" + Suffix);
  iEvent.put(GMStaChiCompatibility_, Prefix + "GMStaChiCompatibility" + Suffix);
  iEvent.put(GMTkKinkTight_, Prefix + "GMTkKinkTight" + Suffix);
  iEvent.put(TMLastStationAngLoose_, Prefix + "TMLastStationAngLoose" + Suffix);
  iEvent.put(TMOneStationAngLoose_, Prefix + "TMOneStationAngLoose" + Suffix);
  iEvent.put(TMOneStationAngTight_, Prefix + "TMOneStationAngTight" + Suffix);


  iEvent.put(ecalIso, Prefix + "EcalIso" + Suffix);
  iEvent.put(hcalIso, Prefix + "HcalIso" + Suffix);
  iEvent.put(trackIso, Prefix + "TrackIso" + Suffix);
 //pf stuff
  iEvent.put(ispf, Prefix + "ProducedFromPF" + Suffix);
  iEvent.put(partIso, Prefix + "ParticleIso" + Suffix);
  iEvent.put(charHadIso, Prefix + "ChargedHadronIso" + Suffix);
  iEvent.put(neutHadIso, Prefix + "NeutralHadronIso" + Suffix);
  iEvent.put(photIso, Prefix + "PhotonIso" + Suffix);
}

#endif
