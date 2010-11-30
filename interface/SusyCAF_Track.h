#ifndef SUSY_CAF_TRACK
#define SUSY_CAF_TRACK

#include <vector>

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

class SusyCAF_Track : public edm::EDProducer {
public: 
  explicit SusyCAF_Track(const edm::ParameterSet&);
private: 
  typedef reco::TrackBase::Vector     Vector;
  
  void produce          (edm::Event&, const edm::EventSetup&);
  void preselectTracks  (const reco::TrackCollection& tracks, const reco::Vertex& primaryVertex, std::vector<bool>& preselectedTracks) const;
  void computeMHT       (const reco::TrackCollection& tracks, const std::vector<bool>& preselectedTracks, reco::Track::TrackQuality quality, Vector& mht, double& ht, const bool pixelSeedOnly) const;
  void countTracks      (const reco::TrackCollection& tracks, reco::Track::TrackQuality quality, int& nEtaLT0p9, int& nEta0p9to1p5, int& nEtaGT1p5) const;

  const edm::InputTag   inputTag;
  const edm::InputTag   primaryVertexTag;
  const std::string     prefix, suffix;
  const double          ptErrFrac;
  const double          maxD0;

  template<typename T>
  struct GreaterByPerp2 {
	  bool operator()( const T & t1, const T & t2 ) const {
		  return t1.Perp2() > t2.Perp2();
	  }
  };
};

#endif
