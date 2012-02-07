#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_Track.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

SusyCAF_Track::SusyCAF_Track(const edm::ParameterSet& iConfig)
  : inputTag        (iConfig.getParameter<edm::InputTag>("InputTag"         ))
  , primaryVertexTag(iConfig.getParameter<edm::InputTag>("PrimaryVertexTag" ))
  , prefix          (iConfig.getParameter<std::string>  ("Prefix"           ))
  , suffix          (iConfig.getParameter<std::string>  ("Suffix"           ))
  , ptErrFrac       (iConfig.getParameter<double>       ("PTErrFrac"        ))
  , maxD0           (iConfig.getParameter<double>       ("MaxD0"            ))
  , qualities       (iConfig.getParameter<std::vector<int> > ("Qualities"        ))
  , pixelSeedOnly   (iConfig.getParameter<bool>         ("PixelSeedOnly"    ))
  , monsterVars     (iConfig.getParameter<bool>         ("MonsterVars"))
{
  for(unsigned j=0; j<qualities.size(); ++j) {
    std::string name = (qualities[j] < 0 ? "All" : reco::Track::qualityNames[qualities[j]]) + (pixelSeedOnly? "PixelTracks" : "Tracks") + suffix;
    name[0] = toupper((unsigned char) name[0]);
    produces<Vector>  (prefix + "SumP3with"    + name );
    produces<double>  (prefix + "SumPTwith"    + name );
    produces<unsigned>(prefix + "NEtaLT0p9"    + name );
    produces<unsigned>(prefix + "NEta0p9to1p5" + name );
    produces<unsigned>(prefix + "NEtaGT1p5"    + name );
    std::cout << name << " ";
  }
  std::cout << std::endl;
  if(monsterVars) {
    produces<unsigned> ("nTracksAll");
    produces<unsigned> ("nTracksHighPurity");
  }
}

void SusyCAF_Track::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) 
{
  std::vector< Vector >  sump3 (qualities.size(), Vector(0.,0.,0.) );
  std::vector< double >  sumpt (qualities.size(), 0.);
  std::vector< unsigned > nEtaLT0p9 (qualities.size(), 0);
  std::vector< unsigned > nEta0p9to1p5 (qualities.size(), 0);
  std::vector< unsigned > nEtaGT1p5 (qualities.size(), 0);
  unsigned nTracksAll(0), nTracksHighPurity(0); //without any D0 cut

  edm::Handle<reco::VertexCollection> vertices;   iEvent.getByLabel(primaryVertexTag, vertices);
  edm::Handle<reco::TrackCollection>  tracks;     iEvent.getByLabel(inputTag        , tracks  );
  if (vertices.isValid() && tracks.isValid()) {
    const reco::Vertex& primaryVertex = vertices->front();
    for(reco::TrackCollection::const_iterator track = tracks->begin(); track!=tracks->end(); ++track ) {
      
      if( (    maxD0  < 0 || fabs(track->dxy(primaryVertex.position())) < maxD0 ) &&
	  ( ptErrFrac < 0 || track->ptError()*track->normalizedChi2() < ptErrFrac*track->pt() ) &&
	  (!pixelSeedOnly || ( track->algo()==reco::TrackBase::iter0 || 
			       track->algo()==reco::TrackBase::iter1 || 
			       track->algo()==reco::TrackBase::iter2 || 
			       track->algo()==reco::TrackBase::iter3))) {
	const double eta = fabs(track->eta());
	for(unsigned j=0; j<qualities.size(); ++j) {
	  sump3[j] += track->momentum();
	  sumpt[j] += track->pt();
	  if      (eta < 0.9) nEtaLT0p9[j]++;
	  else if (eta < 1.5) nEta0p9to1p5[j]++;
	  else                nEtaGT1p5[j]++;
	}
      }
      if(monsterVars) {
	if( track->ptError()*track->normalizedChi2() < 0.2*track->pt() ) {
	  nTracksAll++;
	  if(track->quality(reco::Track::highPurity)) nTracksHighPurity++;
	}
      }    
    }
  }
  
  for(unsigned j=0; j<qualities.size(); ++j) {
    std::string name = (qualities[j] < 0 ? "All" : reco::Track::qualityNames[qualities[j]]) + (pixelSeedOnly? "PixelTracks" : "Tracks") + suffix;
    name[0] = toupper((unsigned char) name[0]);
    iEvent.put( std::auto_ptr< Vector > ( new Vector( sump3[j]) ),   prefix + "SumP3with"    + name );
    iEvent.put( std::auto_ptr< double > ( new double( sumpt[j]) ),   prefix + "SumPTwith"    + name );
    iEvent.put( std::auto_ptr< unsigned >( new unsigned(nEtaLT0p9[j]) ),   prefix + "NEtaLT0p9"    + name );
    iEvent.put( std::auto_ptr< unsigned >( new unsigned(nEta0p9to1p5[j]) ),prefix + "NEta0p9to1p5" + name );
    iEvent.put( std::auto_ptr< unsigned >( new unsigned(nEtaGT1p5[j]) ),   prefix + "NEtaGT1p5"    + name );
  }
  if(monsterVars) {
    iEvent.put( std::auto_ptr< unsigned>( new unsigned(nTracksAll)), "nTracksAll");
    iEvent.put( std::auto_ptr< unsigned>( new unsigned(nTracksHighPurity)), "nTracksHighPurity");
  }
}
