#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_BeamSpot.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

SusyCAF_BeamSpot::SusyCAF_BeamSpot(const edm::ParameterSet& iConfig) 
  : inputTag(iConfig.getParameter<edm::InputTag>("InputTag"))
  , prefix  (iConfig.getParameter<std::string>  ("Prefix"  ))
  , suffix  (iConfig.getParameter<std::string>  ("Suffix"  ))
{
  produces <double>  (prefix + "X0"                  + suffix);
  produces <double>  (prefix + "Y0"                  + suffix);
  produces <double>  (prefix + "Z0"                  + suffix);
}

void SusyCAF_BeamSpot::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) 
{
  edm::Handle<reco::BeamSpot> bs;
  iEvent.getByLabel(inputTag, bs);
  std::auto_ptr<double >  x0                 ( new double(bs->x0())  ) ;
  std::auto_ptr<double >  y0                 ( new double(bs->y0())  ) ;
  std::auto_ptr<double >  z0                 ( new double(bs->z0())  ) ;

  iEvent.put(x0                 , prefix + "X0"                  + suffix);
  iEvent.put(y0                 , prefix + "Y0"                  + suffix);
  iEvent.put(z0                 , prefix + "Z0"                  + suffix);
}
