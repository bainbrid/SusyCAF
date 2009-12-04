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
  produces <std::vector<int> > (prefix + "Ntrks" + suffix);
}

void SusyCAF_Vertex::
produce(edm::Event& event, const edm::EventSetup& ) 
{
  std::auto_ptr<std::vector<math::XYZPoint> > position ( new std::vector<math::XYZPoint>()  ) ;
  std::auto_ptr<std::vector<math::XYZVector> > positionError ( new std::vector<math::XYZVector>()  ) ;
  std::auto_ptr<std::vector<double> > chi2 ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> > ndof ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<int> > ntrks ( new std::vector<int>()  ) ;

  edm::Handle<std::vector<reco::Vertex> > verticies;  
  event.getByLabel(inputTag, verticies);
  for (std::vector<reco::Vertex>::const_iterator it = verticies->begin(); it != verticies->end(); ++it) {
    position->push_back(it->position());
    positionError->push_back(math::XYZVector(it->xError(),it->yError(),it->zError()));
    chi2->push_back(it->chi2());
    ndof->push_back(it->ndof());
    ntrks->push_back(it->tracksSize());
  }

  event.put( position, prefix+"Position"+suffix);
  event.put( positionError, prefix+"PositionError"+suffix);
  event.put( chi2, prefix+"Chi2"+suffix);
  event.put( ndof, prefix+"Ndof"+suffix);
  event.put( ntrks, prefix+"Ntrks"+suffix);
}
