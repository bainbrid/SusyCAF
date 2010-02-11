#ifndef SUSY_CAF_MUON
#define SUSY_CAF_MUON

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
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
  produces <std::vector<double> > (  Prefix + "GlobalTrackdxy" + Suffix);
  produces <std::vector<double> > (  Prefix + "GlobalTrackdxyError" + Suffix);
  produces <std::vector<double> > (  Prefix + "InnerTrackNormalizedChi2" + Suffix);
  produces <std::vector<unsigned> > (  Prefix + "InnerTrackNumberOfValidHits" + Suffix);
  produces <std::vector<double> > (  Prefix + "InnerTrackDxy" + Suffix);
  produces <std::vector<double> > (  Prefix + "InnerTrackDxyBS" + Suffix);
  produces <std::vector<double> > (  Prefix + "InnerTrackDxyError" + Suffix);
  produces <std::vector<double> > (  Prefix + "InnerTrackDz" + Suffix);
  produces <std::vector<double> > (  Prefix + "InnerTrackDzBS" + Suffix);
  produces <std::vector<double> > (  Prefix + "InnerTrackDzError" + Suffix);
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
  produces <std::vector<int> > (Prefix + "MuonIDGlobalMuonPromptTight" + Suffix);
  produces <std::vector<float> > (Prefix + "EcalIso" + Suffix);
  produces <std::vector<float> > (Prefix + "HcalIso" + Suffix);
  produces <std::vector<float> > (Prefix + "TrackIso" + Suffix);

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
  std::auto_ptr<std::vector<double> >  globalTrack_dxyError   ( new std::vector<double>()  ) ;
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
  edm::Handle<reco::BeamSpot> beamSpotCollection;
  iEvent.getByLabel("offlineBeamSpot", beamSpotCollection);
  if (beamSpotCollection.isValid()){ bs = beamSpotCollection->position();}
     
  if (collection.isValid()){
    for(typename std::vector<T>::const_iterator it = collection->begin(); it!=collection->end(); it++) {
      p4->push_back(it->p4());
      charge->push_back(it->charge());
      if( it->globalTrack().isNonnull()){
    	globalTrack_normalizedChi2->push_back(it->globalTrack()->normalizedChi2());
    	globalTrack_numberOfValidHits->push_back(it->globalTrack()->numberOfValidHits());
    	globalTrack_dxy->push_back(it->globalTrack()->dxy());
    	globalTrack_dxyError->push_back(it->globalTrack()->dxyError());
      }
      else {
    	globalTrack_normalizedChi2->push_back(-1);
    	globalTrack_numberOfValidHits->push_back(0);
    	globalTrack_dxy->push_back(999999999.);
    	globalTrack_dxyError->push_back(-10000);
      }	
      if( it->innerTrack().isNonnull()){
    	innerTrack_normalizedChi2->push_back(it->innerTrack()->normalizedChi2());
    	innerTrack_numberOfValidHits->push_back(it->innerTrack()->numberOfValidHits());
    	innerTrack_dxy->push_back(it->innerTrack()->dxy());
    	innerTrack_dxyBS->push_back(it->innerTrack()->dxy(bs));
    	innerTrack_dxyError->push_back(it->innerTrack()->dxyError());
    	innerTrack_dz->push_back(it->innerTrack()->dz());
    	innerTrack_dzBS->push_back(it->innerTrack()->dz(bs));
    	innerTrack_dzError->push_back(it->innerTrack()->dzError());
      }
      else {
    	innerTrack_normalizedChi2->push_back(-1);
    	innerTrack_numberOfValidHits->push_back(0);
    	innerTrack_dxy->push_back(999999999.);
    	innerTrack_dxyBS->push_back(999999999.);
    	innerTrack_dxyError->push_back(-10000);
    	innerTrack_dz->push_back(999999999.);
    	innerTrack_dzBS->push_back(999999999.);
    	innerTrack_dzError->push_back(-10000);
      }	
      if( it->outerTrack().isNonnull()){
    	outerTrack_normalizedChi2->push_back(it->outerTrack()->normalizedChi2());
    	outerTrack_numberOfValidHits->push_back(it->outerTrack()->numberOfValidHits());
      }
      else {
    	outerTrack_normalizedChi2->push_back(-1);
    	outerTrack_numberOfValidHits->push_back(0);
      }	
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
    }



  }
  
  iEvent.put( isHandleValid,  Prefix + "HandleValid" + Suffix );
  iEvent.put( p4,  Prefix + "P4" + Suffix );
  iEvent.put( charge,  Prefix + "Charge" + Suffix );
  iEvent.put( globalTrack_normalizedChi2,  Prefix + "GlobalTracknormalizedChi2" + Suffix );
  iEvent.put( globalTrack_numberOfValidHits,  Prefix + "GlobalTracknumberOfValidHits" + Suffix );
  iEvent.put( globalTrack_dxy,  Prefix + "GlobalTrackdxy" + Suffix );
  iEvent.put( globalTrack_dxyError,  Prefix + "GlobalTrackdxyError" + Suffix );
  iEvent.put( innerTrack_normalizedChi2,  Prefix + "InnerTrackNormalizedChi2" + Suffix );
  iEvent.put( innerTrack_numberOfValidHits,  Prefix + "InnerTrackNumberOfValidHits" + Suffix );
  iEvent.put( innerTrack_dxy,  Prefix + "InnerTrackDxy" + Suffix );
  iEvent.put( innerTrack_dxyBS,  Prefix + "InnerTrackDxyBS" + Suffix );
  iEvent.put( innerTrack_dxyError,  Prefix + "InnerTrackDxyError" + Suffix );
  iEvent.put( innerTrack_dz,  Prefix + "InnerTrackDz" + Suffix );
  iEvent.put( innerTrack_dzBS,  Prefix + "InnerTrackDzBS" + Suffix );
  iEvent.put( innerTrack_dzError,  Prefix + "InnerTrackDzError" + Suffix );
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
  std::auto_ptr<std::vector<int> >  muonIDGlobalMuonPromptTight( new std::vector<int>() );
  std::auto_ptr<std::vector<float> >  ecalIso( new std::vector<float>() );
  std::auto_ptr<std::vector<float> >  hcalIso( new std::vector<float>() );
  std::auto_ptr<std::vector<float> >  trackIso( new std::vector<float>() );

//pf
  
  std::auto_ptr<std::vector<int> > ispf (new std::vector<int>() );
  std::auto_ptr<std::vector<float> > partIso (new std::vector<float>() );
  std::auto_ptr<std::vector<float> > charHadIso (new std::vector<float>() );
  std::auto_ptr<std::vector<float> > neutHadIso (new std::vector<float>() );
  std::auto_ptr<std::vector<float> > photIso (new std::vector<float>() );
  
  if (collection.isValid()){
    for(typename std::vector<T>::const_iterator it = collection->begin(); it!=collection->end(); it++) {
      muonIDGlobalMuonPromptTight->push_back(it->muonID("GlobalMuonPromptTight"));
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
  
  iEvent.put(muonIDGlobalMuonPromptTight, Prefix + "MuonIDGlobalMuonPromptTight" + Suffix );
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
