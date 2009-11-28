#include <algorithm>

#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_Track.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"


SusyCAF_Track::SusyCAF_Track(const edm::ParameterSet& iConfig)
  : inputTag        (iConfig.getParameter<edm::InputTag>("InputTag"         ))
  , primaryVertexTag(iConfig.getParameter<edm::InputTag>("PrimaryVertexTag" ))
  , prefix          (iConfig.getParameter<std::string>  ("Prefix"           ))
  , suffix          (iConfig.getParameter<std::string>  ("Suffix"           ))
  , maxChi2         (iConfig.getParameter<double>       ("MaxChi2"          ))
  , maxD0           (iConfig.getParameter<double>       ("MaxD0"            ))
  , minPT           (iConfig.getParameter<double>       ("MinPT"            ))
  , maxPT           (iConfig.getParameter<double>       ("MaxPT"            ))
{
  /**
    Multiple versions of MPT are calculated, since we don't want to store 
    all tracks. However it is probably undesirable to ever use very-high-pT
    tracks in the calculation, so all of the MPT versions only use tracks
    within small chi2, the given pT range, and compatible with the primary 
    vertex via the d0 cut. Since they may be of interest for problem diagnosing, 
    we do store the list of tracks that exceed the pT threshold.
  */
  produces<std::vector<Vector> >(prefix + "VeryHighPTTracks" + suffix);  // exceeds MaxPT, sorted by pT
  produces<Vector>   (prefix + "MPTwithEverything"           + suffix);  // no chi2, pT or d0 cuts
  produces<Vector>   (prefix + "MPTwithAllTracks"            + suffix);  // with chi2, pT, d0 cuts, no quality criteria
  produces<Vector>   (prefix + "MPTwithLooseTracks"          + suffix);  // with chi2, pT, d0 cuts, and the stated quality 
  produces<Vector>   (prefix + "MPTwithTightTracks"          + suffix);  // with chi2, pT, d0 cuts, and the stated quality 
  produces<Vector>   (prefix + "MPTwithHighPurityTracks"     + suffix);  // with chi2, pT, d0 cuts, and the stated quality 
  produces<Vector>   (prefix + "MPTwithConfirmedTracks"      + suffix);  // with chi2, pT, d0 cuts, and the stated quality 
  produces<Vector>   (prefix + "MPTwithGoodIterativeTracks"  + suffix);  // with chi2, pT, d0 cuts, and the stated quality 
}

void SusyCAF_Track::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) 
{
  std::auto_ptr<std::vector<Vector> >  veryHighPTTracks( new std::vector<Vector> );
  std::auto_ptr<Vector>      MPTwithEverything         ( new Vector              );
  std::auto_ptr<Vector>      MPTwithAllTracks          ( new Vector              );
  std::auto_ptr<Vector>      MPTwithLooseTracks        ( new Vector              );
  std::auto_ptr<Vector>      MPTwithTightTracks        ( new Vector              );
  std::auto_ptr<Vector>      MPTwithHighPurityTracks   ( new Vector              );
  std::auto_ptr<Vector>      MPTwithConfirmedTracks    ( new Vector              );
  std::auto_ptr<Vector>      MPTwithGoodIterativeTracks( new Vector              );


  edm::Handle<reco::VertexCollection> vertices;   iEvent.getByLabel(primaryVertexTag, vertices);
  edm::Handle<reco::TrackCollection>  tracks;     iEvent.getByLabel(inputTag        , tracks  );
  if (vertices.isValid() && tracks.isValid()) {

    std::vector<bool>               preselectedTracks(tracks->size(), true);    // maxD0, minPT, maxPT
    std::vector<Vector>      veryHighPTTracks;                           // within maxD0 but exceeds maxPT

    computeMHT(*tracks, preselectedTracks, reco::Track::undefQuality  , *MPTwithEverything         );
    preselectTracks(*tracks, vertices->front(), preselectedTracks, veryHighPTTracks);
    computeMHT(*tracks, preselectedTracks, reco::Track::undefQuality  , *MPTwithAllTracks          );
    computeMHT(*tracks, preselectedTracks, reco::Track::loose         , *MPTwithLooseTracks        );
    computeMHT(*tracks, preselectedTracks, reco::Track::tight         , *MPTwithTightTracks        );
    computeMHT(*tracks, preselectedTracks, reco::Track::highPurity    , *MPTwithHighPurityTracks   );
    computeMHT(*tracks, preselectedTracks, reco::Track::confirmed     , *MPTwithConfirmedTracks    );
    computeMHT(*tracks, preselectedTracks, reco::Track::goodIterative , *MPTwithGoodIterativeTracks);

  }


  iEvent.put(veryHighPTTracks           , prefix + "VeryHighPTTracks"            + suffix);
  iEvent.put(MPTwithEverything          , prefix + "MPTwithEverything"           + suffix);
  iEvent.put(MPTwithAllTracks           , prefix + "MPTwithAllTracks"            + suffix);
  iEvent.put(MPTwithLooseTracks         , prefix + "MPTwithLooseTracks"          + suffix);
  iEvent.put(MPTwithTightTracks         , prefix + "MPTwithTightTracks"          + suffix);
  iEvent.put(MPTwithHighPurityTracks    , prefix + "MPTwithHighPurityTracks"     + suffix);
  iEvent.put(MPTwithConfirmedTracks     , prefix + "MPTwithConfirmedTracks"      + suffix);
  iEvent.put(MPTwithGoodIterativeTracks , prefix + "MPTwithGoodIterativeTracks"  + suffix);
}

void SusyCAF_Track::
preselectTracks(const reco::TrackCollection& tracks, const reco::Vertex& primaryVertex, 
                std::vector<bool>& preselectedTracks, std::vector<Vector>& veryHighPTTracks) const
{
  const unsigned int      numTracks = tracks.size();
  if (preselectedTracks.size() != numTracks)
    preselectedTracks.resize(numTracks);

  for (unsigned int iTrack = 0; iTrack < numTracks; ++iTrack) {
    const reco::Track&    track     = tracks[iTrack];
    const bool            isOK      = fabs(track.dxy(primaryVertex.position())) < maxD0 && track.chi2() < maxChi2;
    preselectedTracks[iTrack]       = ( isOK && minPT <= track.pt() && track.pt() <= maxPT );

    if (isOK && track.pt() > maxPT)
      veryHighPTTracks.push_back(track.momentum());
  } // end loop over tracks

  std::sort(veryHighPTTracks.begin(), veryHighPTTracks.end(), GreaterByPerp2<Vector>());
}

void SusyCAF_Track::
computeMHT(const reco::TrackCollection& tracks, const std::vector<bool>& preselectedTracks, reco::Track::TrackQuality quality, Vector& mht) const
{
  mht.SetCoordinates(0, 0, 0);

  const unsigned int      numTracks = tracks.size();
  for (unsigned int iTrack = 0; iTrack < numTracks; ++iTrack) {
    if (!preselectedTracks[iTrack]) continue;

    const reco::Track&    track     = tracks[iTrack];
    if (quality == reco::Track::undefQuality || track.quality(quality))
      mht -= track.momentum();
  } // end loop over tracks
}

