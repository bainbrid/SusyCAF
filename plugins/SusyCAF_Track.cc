#include <algorithm>

#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_Track.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"


SusyCAF_Track::SusyCAF_Track(const edm::ParameterSet& iConfig)
  : inputTag        (iConfig.getParameter<edm::InputTag>("InputTag"         ))
  , primaryVertexTag(iConfig.getParameter<edm::InputTag>("PrimaryVertexTag" ))
  , prefix          (iConfig.getParameter<std::string>  ("Prefix"           ))
  , suffix          (iConfig.getParameter<std::string>  ("Suffix"           ))
  , ptErrFrac       (iConfig.getParameter<double>       ("PTErrFrac"        ))
  , maxD0           (iConfig.getParameter<double>       ("MaxD0"            ))
{
  /**
    Multiple versions of MPT are calculated, since we don't want to store 
    all tracks. However it is probably undesirable to ever use very-high-pT
    tracks in the calculation, so all of the MPT versions only use tracks
    within small chi2, the given pT range, and compatible with the primary 
    vertex via the d0 cut. Since they may be of interest for problem diagnosing, 
    we do store the list of tracks that exceed the pT threshold.
  */
  produces<Vector>  (prefix + "MPTwithEverything"               + suffix);  // no chi2, pT or d0 cuts
  produces<Vector>  (prefix + "MPTwithAllTracks"                + suffix);  // with chi2, pT, d0 cuts, no quality criteria
  produces<Vector>  (prefix + "MPTwithLooseTracks"              + suffix);  // with chi2, pT, d0 cuts, and the stated quality 
  produces<Vector>  (prefix + "MPTwithTightTracks"              + suffix);  // with chi2, pT, d0 cuts, and the stated quality 
  produces<Vector>  (prefix + "MPTwithHighPurityTracks"         + suffix);  // with chi2, pT, d0 cuts, and the stated quality 
  produces<Vector>  (prefix + "MPTwithConfirmedTracks"          + suffix);  // with chi2, pT, d0 cuts, and the stated quality 
  produces<Vector>  (prefix + "MPTwithGoodIterativeTracks"      + suffix);  // with chi2, pT, d0 cuts, and the stated quality 
  produces<Vector>  (prefix + "MPTwithAllPixelTracks"           + suffix);  // pixel seed, with chi2, pT, d0 cuts, no quality criteria
  produces<Vector>  (prefix + "MPTwithLoosePixelTracks"         + suffix);  // pixel seed, with chi2, pT, d0 cuts, and the stated quality 
  produces<Vector>  (prefix + "MPTwithTightPixelTracks"         + suffix);  // pixel seed, with chi2, pT, d0 cuts, and the stated quality 
  produces<Vector>  (prefix + "MPTwithHighPurityPixelTracks"    + suffix);  // pixel seed, with chi2, pT, d0 cuts, and the stated quality 
  produces<Vector>  (prefix + "MPTwithConfirmedPixelTracks"     + suffix);  // pixel seed, with chi2, pT, d0 cuts, and the stated quality 
  produces<Vector>  (prefix + "MPTwithGoodIterativePixelTracks" + suffix);  // pixel seed, with chi2, pT, d0 cuts, and the stated quality 
  produces<int>     (prefix + "NEtaLT0p9AllTracks"              + suffix);
  produces<int>     (prefix + "NEtaLT0p9LooseTracks"            + suffix);
  produces<int>     (prefix + "NEtaLT0p9TightTracks"            + suffix);
  produces<int>     (prefix + "NEtaLT0p9HighPurityTracks"       + suffix);
  produces<int>     (prefix + "NEta0p9to1p5AllTracks"           + suffix);
  produces<int>     (prefix + "NEta0p9to1p5LooseTracks"         + suffix);
  produces<int>     (prefix + "NEta0p9to1p5TightTracks"         + suffix);
  produces<int>     (prefix + "NEta0p9to1p5HighPurityTracks"    + suffix);
  produces<int>     (prefix + "NEtaGT1p5AllTracks"              + suffix);
  produces<int>     (prefix + "NEtaGT1p5LooseTracks"            + suffix);
  produces<int>     (prefix + "NEtaGT1p5TightTracks"            + suffix);
  produces<int>     (prefix + "NEtaGT1p5HighPurityTracks"       + suffix);
}

void SusyCAF_Track::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) 
{
  std::auto_ptr<Vector>     MPTwithEverything               ( new Vector );
  std::auto_ptr<Vector>     MPTwithAllTracks                ( new Vector );
  std::auto_ptr<Vector>     MPTwithLooseTracks              ( new Vector );
  std::auto_ptr<Vector>     MPTwithTightTracks              ( new Vector );
  std::auto_ptr<Vector>     MPTwithHighPurityTracks         ( new Vector );
  std::auto_ptr<Vector>     MPTwithConfirmedTracks          ( new Vector );
  std::auto_ptr<Vector>     MPTwithGoodIterativeTracks      ( new Vector );
  std::auto_ptr<Vector>     MPTwithAllPixelTracks           ( new Vector );
  std::auto_ptr<Vector>     MPTwithLoosePixelTracks         ( new Vector );
  std::auto_ptr<Vector>     MPTwithTightPixelTracks         ( new Vector );
  std::auto_ptr<Vector>     MPTwithHighPurityPixelTracks    ( new Vector );
  std::auto_ptr<Vector>     MPTwithConfirmedPixelTracks     ( new Vector );
  std::auto_ptr<Vector>     MPTwithGoodIterativePixelTracks ( new Vector );
  std::auto_ptr<int>        NEtaLT0p9AllTracks              ( new int    );
  std::auto_ptr<int>        NEtaLT0p9LooseTracks            ( new int    );
  std::auto_ptr<int>        NEtaLT0p9TightTracks            ( new int    );
  std::auto_ptr<int>        NEtaLT0p9HighPurityTracks       ( new int    );
  std::auto_ptr<int>        NEta0p9to1p5AllTracks           ( new int    );
  std::auto_ptr<int>        NEta0p9to1p5LooseTracks         ( new int    );
  std::auto_ptr<int>        NEta0p9to1p5TightTracks         ( new int    );
  std::auto_ptr<int>        NEta0p9to1p5HighPurityTracks    ( new int    );
  std::auto_ptr<int>        NEtaGT1p5AllTracks              ( new int    );
  std::auto_ptr<int>        NEtaGT1p5LooseTracks            ( new int    );
  std::auto_ptr<int>        NEtaGT1p5TightTracks            ( new int    );
  std::auto_ptr<int>        NEtaGT1p5HighPurityTracks       ( new int    );


  edm::Handle<reco::VertexCollection> vertices;   iEvent.getByLabel(primaryVertexTag, vertices);
  edm::Handle<reco::TrackCollection>  tracks;     iEvent.getByLabel(inputTag        , tracks  );
  if (vertices.isValid() && tracks.isValid()) {

    std::vector<bool>       preselectedTracks(tracks->size(), true);

    computeMHT(*tracks, preselectedTracks, reco::Track::undefQuality  , *MPTwithEverything              , false);
    preselectTracks(*tracks, vertices->front(), preselectedTracks);
    computeMHT(*tracks, preselectedTracks, reco::Track::undefQuality  , *MPTwithAllTracks               , false);
    computeMHT(*tracks, preselectedTracks, reco::Track::loose         , *MPTwithLooseTracks             , false);
    computeMHT(*tracks, preselectedTracks, reco::Track::tight         , *MPTwithTightTracks             , false);
    computeMHT(*tracks, preselectedTracks, reco::Track::highPurity    , *MPTwithHighPurityTracks        , false);
    computeMHT(*tracks, preselectedTracks, reco::Track::confirmed     , *MPTwithConfirmedTracks         , false);
    computeMHT(*tracks, preselectedTracks, reco::Track::goodIterative , *MPTwithGoodIterativeTracks     , false);
    computeMHT(*tracks, preselectedTracks, reco::Track::undefQuality  , *MPTwithAllPixelTracks          , true );
    computeMHT(*tracks, preselectedTracks, reco::Track::loose         , *MPTwithLoosePixelTracks        , true );
    computeMHT(*tracks, preselectedTracks, reco::Track::tight         , *MPTwithTightPixelTracks        , true );
    computeMHT(*tracks, preselectedTracks, reco::Track::highPurity    , *MPTwithHighPurityPixelTracks   , true );
    computeMHT(*tracks, preselectedTracks, reco::Track::confirmed     , *MPTwithConfirmedPixelTracks    , true );
    computeMHT(*tracks, preselectedTracks, reco::Track::goodIterative , *MPTwithGoodIterativePixelTracks, true );

    countTracks(*tracks, reco::Track::undefQuality, *NEtaLT0p9AllTracks       , *NEta0p9to1p5AllTracks        , *NEtaGT1p5AllTracks       );
    countTracks(*tracks, reco::Track::loose       , *NEtaLT0p9LooseTracks     , *NEta0p9to1p5LooseTracks      , *NEtaGT1p5LooseTracks     );
    countTracks(*tracks, reco::Track::tight       , *NEtaLT0p9TightTracks     , *NEta0p9to1p5TightTracks      , *NEtaGT1p5TightTracks     );
    countTracks(*tracks, reco::Track::highPurity  , *NEtaLT0p9HighPurityTracks, *NEta0p9to1p5HighPurityTracks , *NEtaGT1p5HighPurityTracks);

  }


  iEvent.put(MPTwithEverything              , prefix + "MPTwithEverything"                + suffix);
  iEvent.put(MPTwithAllTracks               , prefix + "MPTwithAllTracks"                 + suffix);
  iEvent.put(MPTwithLooseTracks             , prefix + "MPTwithLooseTracks"               + suffix);
  iEvent.put(MPTwithTightTracks             , prefix + "MPTwithTightTracks"               + suffix);
  iEvent.put(MPTwithHighPurityTracks        , prefix + "MPTwithHighPurityTracks"          + suffix);
  iEvent.put(MPTwithConfirmedTracks         , prefix + "MPTwithConfirmedTracks"           + suffix);
  iEvent.put(MPTwithGoodIterativeTracks     , prefix + "MPTwithGoodIterativeTracks"       + suffix);
  iEvent.put(MPTwithAllPixelTracks          , prefix + "MPTwithAllPixelTracks"            + suffix);
  iEvent.put(MPTwithLoosePixelTracks        , prefix + "MPTwithLoosePixelTracks"          + suffix);
  iEvent.put(MPTwithTightPixelTracks        , prefix + "MPTwithTightPixelTracks"          + suffix);
  iEvent.put(MPTwithHighPurityPixelTracks   , prefix + "MPTwithHighPurityPixelTracks"     + suffix);
  iEvent.put(MPTwithConfirmedPixelTracks    , prefix + "MPTwithConfirmedPixelTracks"      + suffix);
  iEvent.put(MPTwithGoodIterativePixelTracks, prefix + "MPTwithGoodIterativePixelTracks"  + suffix);
  iEvent.put(NEtaLT0p9AllTracks             , prefix + "NEtaLT0p9AllTracks"               + suffix);
  iEvent.put(NEtaLT0p9LooseTracks           , prefix + "NEtaLT0p9LooseTracks"             + suffix);
  iEvent.put(NEtaLT0p9TightTracks           , prefix + "NEtaLT0p9TightTracks"             + suffix);
  iEvent.put(NEtaLT0p9HighPurityTracks      , prefix + "NEtaLT0p9HighPurityTracks"        + suffix);
  iEvent.put(NEta0p9to1p5AllTracks          , prefix + "NEta0p9to1p5AllTracks"            + suffix);
  iEvent.put(NEta0p9to1p5LooseTracks        , prefix + "NEta0p9to1p5LooseTracks"          + suffix);
  iEvent.put(NEta0p9to1p5TightTracks        , prefix + "NEta0p9to1p5TightTracks"          + suffix);
  iEvent.put(NEta0p9to1p5HighPurityTracks   , prefix + "NEta0p9to1p5HighPurityTracks"     + suffix);
  iEvent.put(NEtaGT1p5AllTracks             , prefix + "NEtaGT1p5AllTracks"               + suffix);
  iEvent.put(NEtaGT1p5LooseTracks           , prefix + "NEtaGT1p5LooseTracks"             + suffix);
  iEvent.put(NEtaGT1p5TightTracks           , prefix + "NEtaGT1p5TightTracks"             + suffix);
  iEvent.put(NEtaGT1p5HighPurityTracks      , prefix + "NEtaGT1p5HighPurityTracks"        + suffix);
}

void SusyCAF_Track::
preselectTracks(const reco::TrackCollection& tracks, const reco::Vertex& primaryVertex, std::vector<bool>& preselectedTracks) const
{
  const unsigned int      numTracks = tracks.size();
  if (preselectedTracks.size() != numTracks)
    preselectedTracks.resize(numTracks);

  for (unsigned int iTrack = 0; iTrack < numTracks; ++iTrack) {
    const reco::Track&    track     = tracks[iTrack];
    const bool            isOK      = ( maxD0     < 0 || fabs(track.dxy(primaryVertex.position())) < maxD0                )
                                   && ( ptErrFrac < 0 || track.ptError()*track.normalizedChi2()    < ptErrFrac*track.pt() )
                                    ;
    preselectedTracks[iTrack]       = isOK;
  } // end loop over tracks
}

void SusyCAF_Track::
computeMHT(const reco::TrackCollection& tracks, const std::vector<bool>& preselectedTracks, reco::Track::TrackQuality quality, Vector& mht, const bool pixelSeedOnly) const
{
  mht.SetCoordinates(0, 0, 0);

  const unsigned int      numTracks = tracks.size();
  for (unsigned int iTrack = 0; iTrack < numTracks; ++iTrack) {
    if (!preselectedTracks[iTrack]) continue;

    const reco::Track&    track     = tracks[iTrack];
    if  ( (quality == reco::Track::undefQuality || track.quality(quality))
       && (!pixelSeedOnly || (track.algo()==reco::TrackBase::iter0 || track.algo()==reco::TrackBase::iter1 || track.algo()==reco::TrackBase::iter2 || track.algo()==reco::TrackBase::iter3))
        )
      mht -= track.momentum();
  } // end loop over tracks
}

void SusyCAF_Track::
countTracks (const reco::TrackCollection& tracks, reco::Track::TrackQuality quality, int& nEtaLT0p9, int& nEta0p9to1p5, int& nEtaGT1p5) const
{
  nEtaLT0p9               = 0;
  nEta0p9to1p5            = 0;
  nEtaGT1p5               = 0;

  const unsigned int      numTracks = tracks.size();
  for (unsigned int iTrack = 0; iTrack < numTracks; ++iTrack) {
    const reco::Track&    track     = tracks[iTrack];
    if (quality == reco::Track::undefQuality || track.quality(quality)) {
      const double        eta       = fabs(track.eta());
      if      (eta < 0.9) ++nEtaLT0p9;
      else if (eta < 1.5) ++nEta0p9to1p5;
      else                ++nEtaGT1p5;
    }
  } // end loop over tracks
}

