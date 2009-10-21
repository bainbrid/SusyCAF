#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_Photon.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "FWCore/Framework/interface/Event.h"

SusyCAF_Photon::SusyCAF_Photon(const edm::ParameterSet& iConfig) 
  : inputTag(iConfig.getParameter<edm::InputTag>("InputTag"))
  , prefix  (iConfig.getParameter<std::string>  ("Prefix"  ))
  , suffix  (iConfig.getParameter<std::string>  ("Suffix"  ))
{
  produces <std::vector<float> >  (prefix + "Px"                  + suffix);
  produces <std::vector<float> >  (prefix + "Py"                  + suffix);
  produces <std::vector<float> >  (prefix + "Pz"                  + suffix);
  produces <std::vector<float> >  (prefix + "Pt"                  + suffix);
  produces <std::vector<float> >  (prefix + "Eta"                 + suffix);
  produces <std::vector<float> >  (prefix + "Phi"                 + suffix);
  produces <std::vector<float> >  (prefix + "Energy"              + suffix);
  produces <std::vector<bool > >  (prefix + "HasConversionTracks" + suffix);
  produces <std::vector<bool > >  (prefix + "HasPixelSeed"        + suffix);
  produces <std::vector<float> >  (prefix + "CaloPositionX"       + suffix);
  produces <std::vector<float> >  (prefix + "CaloPositionY"       + suffix);
  produces <std::vector<float> >  (prefix + "CaloPositionZ"       + suffix);
  produces <std::vector<bool > >  (prefix + "IsEB"                + suffix);
  produces <std::vector<bool > >  (prefix + "IsEE"                + suffix);
  produces <std::vector<bool > >  (prefix + "IsEBGap"             + suffix);
  produces <std::vector<bool > >  (prefix + "IsEEGap"             + suffix);
  produces <std::vector<bool > >  (prefix + "IsEBEEGap"           + suffix);
}

void SusyCAF_Photon::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) 
{
  std::auto_ptr<std::vector<float> >  px                 ( new std::vector<float>()  ) ;
  std::auto_ptr<std::vector<float> >  py                 ( new std::vector<float>()  ) ;
  std::auto_ptr<std::vector<float> >  pz                 ( new std::vector<float>()  ) ;
  std::auto_ptr<std::vector<float> >  pt                 ( new std::vector<float>()  ) ;
  std::auto_ptr<std::vector<float> >  eta                ( new std::vector<float>()  ) ;
  std::auto_ptr<std::vector<float> >  phi                ( new std::vector<float>()  ) ;
  std::auto_ptr<std::vector<float> >  energy             ( new std::vector<float>()  ) ;
  std::auto_ptr<std::vector<bool > >  hasConversionTracks( new std::vector<bool >()  ) ;
  std::auto_ptr<std::vector<bool > >  hasPixelSeed       ( new std::vector<bool >()  ) ;
  std::auto_ptr<std::vector<float> >  caloPositionX      ( new std::vector<float>()  ) ;
  std::auto_ptr<std::vector<float> >  caloPositionY      ( new std::vector<float>()  ) ;
  std::auto_ptr<std::vector<float> >  caloPositionZ      ( new std::vector<float>()  ) ;
  std::auto_ptr<std::vector<bool > >  isEB               ( new std::vector<bool >()  ) ;
  std::auto_ptr<std::vector<bool > >  isEE               ( new std::vector<bool >()  ) ;
  std::auto_ptr<std::vector<bool > >  isEBGap            ( new std::vector<bool >()  ) ;
  std::auto_ptr<std::vector<bool > >  isEEGap            ( new std::vector<bool >()  ) ;
  std::auto_ptr<std::vector<bool > >  isEBEEGap          ( new std::vector<bool >()  ) ;


  edm::Handle<std::vector<reco::Photon> >           collection;
  iEvent.getByLabel(inputTag, collection);
  
  const std::vector<reco::Photon>::const_iterator   endOfStuff  = collection->end();
  for (std::vector<reco::Photon>::const_iterator it = collection->begin(); it != endOfStuff; ++it) {
    const reco::Photon&                             photon      = *it;
    px                 ->push_back(photon.px                   ());
    py                 ->push_back(photon.py                   ());
    pz                 ->push_back(photon.pz                   ());
    pt                 ->push_back(photon.pt                   ());
    eta                ->push_back(photon.eta                  ());
    phi                ->push_back(photon.phi                  ());
    energy             ->push_back(photon.energy               ());
    hasConversionTracks->push_back(photon.hasConversionTracks  ());
    hasPixelSeed       ->push_back(photon.hasPixelSeed         ());
    caloPositionX      ->push_back(photon.caloPosition().x     ());
    caloPositionY      ->push_back(photon.caloPosition().y     ());
    caloPositionZ      ->push_back(photon.caloPosition().z     ());
    isEB               ->push_back(photon.isEB                 ());
    isEE               ->push_back(photon.isEE                 ());
    isEBGap            ->push_back(photon.isEBGap              ());
    isEEGap            ->push_back(photon.isEEGap              ());
    isEBEEGap          ->push_back(photon.isEBEEGap            ());
  } // end loop over photons


  iEvent.put(px                 , prefix + "Px"                  + suffix);
  iEvent.put(py                 , prefix + "Py"                  + suffix);
  iEvent.put(pz                 , prefix + "Pz"                  + suffix);
  iEvent.put(pt                 , prefix + "Pt"                  + suffix);
  iEvent.put(eta                , prefix + "Eta"                 + suffix);
  iEvent.put(phi                , prefix + "Phi"                 + suffix);
  iEvent.put(energy             , prefix + "Energy"              + suffix);
  iEvent.put(hasConversionTracks, prefix + "HasConversionTracks" + suffix);
  iEvent.put(hasPixelSeed       , prefix + "HasPixelSeed"        + suffix);
  iEvent.put(caloPositionX      , prefix + "CaloPositionX"       + suffix);
  iEvent.put(caloPositionY      , prefix + "CaloPositionY"       + suffix);
  iEvent.put(caloPositionZ      , prefix + "CaloPositionZ"       + suffix);
  iEvent.put(isEB               , prefix + "IsEB"                + suffix);
  iEvent.put(isEE               , prefix + "IsEE"                + suffix);
  iEvent.put(isEBGap            , prefix + "IsEBGap"             + suffix);
  iEvent.put(isEEGap            , prefix + "IsEEGap"             + suffix);
  iEvent.put(isEBEEGap          , prefix + "IsEBEEGap"           + suffix);
}
