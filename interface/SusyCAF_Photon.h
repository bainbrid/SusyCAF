#ifndef SUSY_CAF_PHOTON
#define SUSY_CAF_PHOTON

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"

#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Photon.h"



//=============================================================================
//  Interface
//=============================================================================

template< typename T >
class SusyCAF_Photon : public edm::EDProducer 
{
public: 
  explicit SusyCAF_Photon(const edm::ParameterSet&);

private: 
  void initTemplate();
  void initRECO();
  void initPAT();
  void produce(edm::Event &, const edm::EventSetup & );
  void produceTemplate(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<reco::Photon> > &);
  void produceTemplate(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<pat::Photon> > &);
  void produceRECO(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &);
  void producePAT(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &);

  const edm::InputTag   inputTag;
  const std::string     prefix,suffix;
  
  typedef reco::Candidate::LorentzVector  LorentzVector;
  typedef reco::Candidate::Point          Point;
};



//=============================================================================
//  Initialization
//=============================================================================

template< typename T >
SusyCAF_Photon<T>::SusyCAF_Photon(const edm::ParameterSet& iConfig) 
  : inputTag(iConfig.getParameter<edm::InputTag>("InputTag"))
  , prefix  (iConfig.getParameter<std::string>  ("Prefix"  ))
  , suffix  (iConfig.getParameter<std::string>  ("Suffix"  ))
{
  initTemplate();
}


template< typename T >
void SusyCAF_Photon<T>::initRECO()
{
  produces <std::vector<LorentzVector> >(prefix + "P4"                    + suffix);
  produces <std::vector<Point        > >(prefix + "CaloPosition"          + suffix);
  produces <std::vector<float        > >(prefix + "HadronicDepth1OverEm"  + suffix);
  produces <std::vector<float        > >(prefix + "HadronicDepth2OverEm"  + suffix);
  produces <std::vector<float        > >(prefix + "HadronicOverEm"        + suffix);
  produces <std::vector<bool         > >(prefix + "HasConversionTracks"   + suffix);
  produces <std::vector<bool         > >(prefix + "HasPixelSeed"          + suffix);
  produces <std::vector<bool         > >(prefix + "IsEB"                  + suffix);
  produces <std::vector<bool         > >(prefix + "IsEE"                  + suffix);
  produces <std::vector<bool         > >(prefix + "IsEBGap"               + suffix);
  produces <std::vector<bool         > >(prefix + "IsEEGap"               + suffix);
  produces <std::vector<bool         > >(prefix + "IsEBEEGap"             + suffix);
}

// extra information stored for PAT data
template< typename T >
void SusyCAF_Photon<T>::initPAT()
{
  produces <std::vector<float> >(prefix + "CaloIso"       + suffix);
  produces <std::vector<float> >(prefix + "EcalIso"       + suffix);
  produces <std::vector<float> >(prefix + "HcalIso"       + suffix);
  produces <std::vector<float> >(prefix + "SigmaEtaEta"   + suffix);
  produces <std::vector<float> >(prefix + "SigmaIetaIeta" + suffix);
}


//=============================================================================
//  Production
//=============================================================================

template< typename T >
void SusyCAF_Photon<T>::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) 
{
  edm::Handle<std::vector<T> > collection;
  iEvent.getByLabel(inputTag,collection);
  produceTemplate(iEvent, iSetup, collection);
}
// produce method in case of RECO data
template< typename T >
void SusyCAF_Photon<T>::produceTemplate(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<reco::Photon> >& collection) {
  produceRECO(iEvent, iSetup, collection);
}
// produce method in case of PAT data
template< typename T >
void SusyCAF_Photon<T>::produceTemplate(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<pat::Photon> >& collection) {
  produceRECO(iEvent, iSetup, collection);
  producePAT (iEvent, iSetup, collection);
}


template< typename T >
void SusyCAF_Photon<T>::
produceRECO(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<T> >& collection) {
  std::auto_ptr<std::vector<LorentzVector> >  p4                  ( new std::vector<LorentzVector>() );
  std::auto_ptr<std::vector<Point        > >  caloPosition        ( new std::vector<Point        >() );
  std::auto_ptr<std::vector<float        > >  hadronicDepth1OverEm( new std::vector<float        >() );
  std::auto_ptr<std::vector<float        > >  hadronicDepth2OverEm( new std::vector<float        >() );
  std::auto_ptr<std::vector<float        > >  hadronicOverEm      ( new std::vector<float        >() );
  std::auto_ptr<std::vector<bool         > >  hasConversionTracks ( new std::vector<bool         >() );
  std::auto_ptr<std::vector<bool         > >  hasPixelSeed        ( new std::vector<bool         >() );
  std::auto_ptr<std::vector<bool         > >  isEB                ( new std::vector<bool         >() );
  std::auto_ptr<std::vector<bool         > >  isEE                ( new std::vector<bool         >() );
  std::auto_ptr<std::vector<bool         > >  isEBGap             ( new std::vector<bool         >() );
  std::auto_ptr<std::vector<bool         > >  isEEGap             ( new std::vector<bool         >() );
  std::auto_ptr<std::vector<bool         > >  isEBEEGap           ( new std::vector<bool         >() );


  const typename std::vector<T>::const_iterator   endOfStuff  = collection->end();
  for (typename std::vector<T>::const_iterator it = collection->begin(); it != endOfStuff; ++it) {
    const reco::Photon&                             photon      = *it;
    p4                  ->push_back(photon.p4                   ());
    caloPosition        ->push_back(photon.caloPosition         ());
    hadronicDepth1OverEm->push_back(photon.hadronicDepth1OverEm ());
    hadronicDepth2OverEm->push_back(photon.hadronicDepth2OverEm ());
    hadronicOverEm      ->push_back(photon.hadronicOverEm       ());
    hasConversionTracks ->push_back(photon.hasConversionTracks  ());
    hasPixelSeed        ->push_back(photon.hasPixelSeed         ());
    isEB                ->push_back(photon.isEB                 ());
    isEE                ->push_back(photon.isEE                 ());
    isEBGap             ->push_back(photon.isEBGap              ());
    isEEGap             ->push_back(photon.isEEGap              ());
    isEBEEGap           ->push_back(photon.isEBEEGap            ());
  } // end loop over photons


  iEvent.put(p4                   , prefix + "P4"                   + suffix);
  iEvent.put(caloPosition         , prefix + "CaloPosition"         + suffix);
  iEvent.put(hadronicDepth1OverEm , prefix + "HadronicDepth1OverEm" + suffix);
  iEvent.put(hadronicDepth2OverEm , prefix + "HadronicDepth2OverEm" + suffix);
  iEvent.put(hadronicOverEm       , prefix + "HadronicOverEm"       + suffix);
  iEvent.put(hasConversionTracks  , prefix + "HasConversionTracks"  + suffix);
  iEvent.put(hasPixelSeed         , prefix + "HasPixelSeed"         + suffix);
  iEvent.put(isEB                 , prefix + "IsEB"                 + suffix);
  iEvent.put(isEE                 , prefix + "IsEE"                 + suffix);
  iEvent.put(isEBGap              , prefix + "IsEBGap"              + suffix);
  iEvent.put(isEEGap              , prefix + "IsEEGap"              + suffix);
  iEvent.put(isEBEEGap            , prefix + "IsEBEEGap"            + suffix);
}

// extra information stored for PAT data
template< typename T >
void SusyCAF_Photon<T>::
producePAT(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<T> >& collection) {
  std::auto_ptr<std::vector<float> >  caloIso       ( new std::vector<float>() );
  std::auto_ptr<std::vector<float> >  ecalIso       ( new std::vector<float>() );
  std::auto_ptr<std::vector<float> >  hcalIso       ( new std::vector<float>() );
  std::auto_ptr<std::vector<float> >  sigmaEtaEta   ( new std::vector<float>() );
  std::auto_ptr<std::vector<float> >  sigmaIetaIeta ( new std::vector<float>() );


  const typename std::vector<T>::const_iterator   endOfStuff  = collection->end();
  for (typename std::vector<T>::const_iterator it = collection->begin(); it != endOfStuff; ++it) {
    const pat::Photon&                              photon      = *it;
    caloIso      ->push_back(photon.caloIso      ());
    ecalIso      ->push_back(photon.ecalIso      ());
    hcalIso      ->push_back(photon.hcalIso      ());
    sigmaEtaEta  ->push_back(photon.sigmaEtaEta  ());
    sigmaIetaIeta->push_back(photon.sigmaIetaIeta());

    // The following is for printing out the available IDs for inspection purposes.
    const std::vector<pat::Photon::IdPair>&         ids         = photon.photonIDs();
    const unsigned int                              numIDs      = ids.size();
    for (unsigned int iID = 0; iID < numIDs; ++iID)
      std::cout << ids[iID].first << std::endl;
  } // end loop over photons


  iEvent.put(caloIso      , prefix + "CaloIso"        + suffix);
  iEvent.put(ecalIso      , prefix + "EcalIso"        + suffix);
  iEvent.put(hcalIso      , prefix + "HcalIso"        + suffix);
  iEvent.put(sigmaEtaEta  , prefix + "SigmaEtaEta"    + suffix);
  iEvent.put(sigmaIetaIeta, prefix + "SigmaIetaIeta"  + suffix);
}



#endif
