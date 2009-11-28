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
  
  void produce( edm::Event &, const edm::EventSetup & );
  void preselectTracks(const reco::TrackCollection& tracks, const reco::Vertex& primaryVertex, std::vector<bool>& preselectedTracks, std::vector<Vector>& veryHighPTTracks) const;
  void computeMHT(const reco::TrackCollection& tracks, const std::vector<bool>& preselectedTracks, reco::Track::TrackQuality quality, Vector& mht) const;

  const edm::InputTag                 inputTag;
  const edm::InputTag                 primaryVertexTag;
  const std::string                   prefix, suffix;
  const double                        maxD0;
  const double                        minPT;
  const double                        maxPT;

  template<typename T>
  struct GreaterByPerp2 {
	  bool operator()( const T & t1, const T & t2 ) const {
		  return t1.Perp2() > t2.Perp2();
	  }
  };
};

#endif
