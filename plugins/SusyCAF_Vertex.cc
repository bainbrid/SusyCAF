#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_Vertex.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Math/interface/Vector3D.h"

SusyCAF_Vertex::SusyCAF_Vertex(const edm::ParameterSet& cfg) 
  : inputTag(cfg.getParameter<edm::InputTag>("InputTag"))
  , prefix  (cfg.getParameter<std::string>  ("Prefix"  ))
  , suffix  (cfg.getParameter<std::string>  ("Suffix"  ))
{
  produces <std::vector<math::XYZPoint> >  (prefix + "Position" + suffix);
  produces <std::vector<math::XYZVector> > (prefix + "PositionError" + suffix);
  produces <std::vector<double> > (prefix + "Chi2" + suffix);
  produces <std::vector<double> > (prefix + "Ndof" + suffix);
  produces <std::vector<int> > (prefix + "IsFake" + suffix);
  produces <std::vector<double> > (prefix + "SumPt" + suffix);
  produces <std::vector<math::XYZVector> > (prefix + "SumP3" + suffix);
  produces <std::vector<int> > (prefix + "Ntrks" + suffix);
}

void SusyCAF_Vertex::
produce(edm::Event& event, const edm::EventSetup& ) 
{
  std::auto_ptr<std::vector<math::XYZPoint> > position ( new std::vector<math::XYZPoint>()  ) ;
  std::auto_ptr<std::vector<math::XYZVector> > positionError ( new std::vector<math::XYZVector>()  ) ;
  std::auto_ptr<std::vector<double> > chi2 ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> > ndof ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<int> > isFake ( new std::vector<int>()  ) ;
  std::auto_ptr<std::vector<double> > sumPts ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<math::XYZVector> > sumP3s ( new std::vector<math::XYZVector>()  ) ;
  std::auto_ptr<std::vector<int> > ntrks ( new std::vector<int>()  ) ;

  edm::Handle<std::vector<reco::Vertex> > verticies;  
  event.getByLabel(inputTag, verticies);
  for (std::vector<reco::Vertex>::const_iterator it = verticies->begin(); it != verticies->end(); ++it) {
    position->push_back(it->position());
    positionError->push_back(math::XYZVector(it->xError(),it->yError(),it->zError()));
    chi2->push_back(it->chi2());
    ndof->push_back(it->ndof());
    isFake->push_back(it->isFake());
    
    int   numUsedTracks = 0;
    double sumPt = 0;
    math::XYZVector sumP3;
    for (reco::Vertex::trackRef_iterator ittrk = it->tracks_begin(); ittrk!=it->tracks_end(); ++ittrk) {
      sumPt += (*ittrk)->pt();
      sumP3 += (*ittrk)->momentum();
      if (it->trackWeight(*ittrk) > 0.5)  ++numUsedTracks;
    }
    sumPts->push_back(sumPt);
    sumP3s->push_back(sumP3);
    ntrks->push_back(numUsedTracks);
  }

  event.put( position, prefix+"Position"+suffix);
  event.put( positionError, prefix+"PositionError"+suffix);
  event.put( chi2, prefix+"Chi2"+suffix);
  event.put( ndof, prefix+"Ndof"+suffix);
  event.put( isFake, prefix+"IsFake"+suffix);
  event.put( sumPts, prefix+"SumPt"+suffix);
  event.put( sumP3s, prefix+"SumP3"+suffix);
  event.put( ntrks, prefix+"Ntrks"+suffix);
}
