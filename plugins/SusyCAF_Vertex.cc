#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_Vertex.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

SusyCAF_Vertex::SusyCAF_Vertex(const edm::ParameterSet& iConfig) 
  : inputTag(iConfig.getParameter<edm::InputTag>("InputTag"))
  , prefix  (iConfig.getParameter<std::string>  ("Prefix"  ))
  , suffix  (iConfig.getParameter<std::string>  ("Suffix"  ))
{
  produces <std::vector<double> >  (prefix + "X"                  + suffix);
  produces <std::vector<double> >  (prefix + "Y"                  + suffix);
  produces <std::vector<double> >  (prefix + "Z"                  + suffix);
}

void SusyCAF_Vertex::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) 
{
  std::auto_ptr<std::vector<double> >  x                 ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  y                 ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  z                 ( new std::vector<double>()  ) ;


  edm::Handle<std::vector<reco::Vertex> >           collection;
  iEvent.getByLabel(inputTag, collection);
  
  for (std::vector<reco::Vertex>::const_iterator it = collection->begin(); it != collection->end(); ++it) {
    x                 ->push_back(it->x());
    y                 ->push_back(it->y());
    z                 ->push_back(it->z());
  } // end loop over vertices


  iEvent.put(x                 , prefix + "X"                  + suffix);
  iEvent.put(y                 , prefix + "Y"                  + suffix);
  iEvent.put(z                 , prefix + "Z"                  + suffix);
}
