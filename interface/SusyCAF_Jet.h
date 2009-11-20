#ifndef SUSY_CAF_JET
#define SUSY_CAF_JET

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"

template< typename T >
class SusyCAF_Jet : public edm::EDProducer {
 public: 
  explicit SusyCAF_Jet(const edm::ParameterSet&);
 private: 
  //
  void initTemplate(edm::Handle<reco::CaloJet> &);
  void initTemplate(edm::Handle<pat::Jet> &);
  void initRECO();
  void initPAT();
  //
  void produce(edm::Event &, const edm::EventSetup & );
  void produceTemplate(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<reco::CaloJet> > &);
  void produceTemplate(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<pat::Jet> > &);
  void produceRECO(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &);
  void producePAT(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &);

  const edm::InputTag inputTag;
  const std::string Prefix,Suffix;
};

template< typename T >
SusyCAF_Jet<T>::SusyCAF_Jet(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
  Prefix(iConfig.getParameter<std::string>("Prefix")),
  Suffix(iConfig.getParameter<std::string>("Suffix"))
{
  edm::Handle<T> dataType;
  initTemplate(dataType);
}


// init method in case of RECO data
template< typename T >
void SusyCAF_Jet<T>::initTemplate(edm::Handle<reco::CaloJet>& dataType)
{
  initRECO();
}

// init method in case of PAT data
template< typename T >
void SusyCAF_Jet<T>::initTemplate(edm::Handle<pat::Jet>& dataType)
{
  initRECO();
  initPAT();
}

template< typename T >
void SusyCAF_Jet<T>::initRECO()
  {
  produces <std::vector<reco::Candidate::LorentzVector> > ( Prefix + "P4"  + Suffix );
  produces <std::vector<double> > ( Prefix + "EmEnergyFraction"  + Suffix );
  produces <std::vector<double> > ( Prefix + "EnergyFractionHadronic"  + Suffix );
  produces <std::vector<double> > ( Prefix + "TowersArea"  + Suffix );
  produces <std::vector<double> > ( Prefix + "MaxEInEmTowers"  + Suffix );
  produces <std::vector<double> > ( Prefix + "MaxEInHadTowers"  + Suffix );
  produces <std::vector<double> > ( Prefix + "HadEnergyInHB"  + Suffix );
  produces <std::vector<double> > ( Prefix + "HadEnergyInHE"  + Suffix );
  produces <std::vector<double> > ( Prefix + "HadEnergyInHO"  + Suffix );
  produces <std::vector<double> > ( Prefix + "HadEnergyInHF"  + Suffix );
  produces <std::vector<double> > ( Prefix + "EmEnergyInEB"  + Suffix );
  produces <std::vector<double> > ( Prefix + "EmEnergyInEE"  + Suffix );
  produces <std::vector<double> > ( Prefix + "EmEnergyInHF"  + Suffix );
  produces <std::vector<int> > ( Prefix + "N60"  + Suffix ); 
  produces <std::vector<int> > ( Prefix + "N90"  + Suffix ); 
}

// extra information stored for PAT data
template< typename T >
void SusyCAF_Jet<T>::initPAT()
{
  produces <std::vector<double> > ( Prefix + "CorrFactor"  + Suffix );
  produces <std::vector<int> > ( Prefix + "NAssoTracks"  + Suffix );
  produces <std::vector<double> > ( Prefix + "FHPD"  + Suffix );
  produces <std::vector<double> > ( Prefix + "FRBX"  + Suffix );
  produces <std::vector<double> > ( Prefix + "FSubDet1"  + Suffix );
  produces <std::vector<double> > ( Prefix + "FSubDet2"  + Suffix );
  produces <std::vector<double> > ( Prefix + "FSubDet3"  + Suffix );
  produces <std::vector<double> > ( Prefix + "FSubDet4"  + Suffix );
  produces <std::vector<double> > ( Prefix + "ResEMF"  + Suffix );
  produces <std::vector<int> > ( Prefix + "NECALTowers"  + Suffix );
  produces <std::vector<int> > ( Prefix + "NHCALTowers"  + Suffix );

}

template< typename T >
void SusyCAF_Jet<T>::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  edm::Handle<std::vector<T> > jetcollection;
  iEvent.getByLabel(inputTag, jetcollection);
  produceTemplate(iEvent, iSetup, jetcollection);
}

// produce method in case of RECO data
template< typename T >
void SusyCAF_Jet<T>::
produceTemplate(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<reco::CaloJet> >& collection) {
  produceRECO(iEvent, iSetup, collection);
}

// produce method in case of PAT data
template< typename T >
void SusyCAF_Jet<T>::
produceTemplate(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<pat::Jet> >& collection) {
  produceRECO(iEvent, iSetup, collection);
  producePAT(iEvent, iSetup, collection);
}

template< typename T >
void SusyCAF_Jet<T>::
produceRECO(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<T> >& collection) {
  std::auto_ptr<std::vector<reco::Candidate::LorentzVector> >  p4  ( new std::vector<reco::Candidate::LorentzVector>()  ) ;
  std::auto_ptr<std::vector<double> >  emEnergyFraction  ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  energyFractionHadronic ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  towersArea   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  maxEInEmTowers   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  maxEInHadTowers   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  hadEnergyInHB   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  hadEnergyInHE   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  hadEnergyInHO   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  hadEnergyInHF   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  emEnergyInEB   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  emEnergyInEE   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  emEnergyInHF   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<int> >  n60   ( new std::vector<int>()  ) ; 
  std::auto_ptr<std::vector<int> >  n90   ( new std::vector<int>()  ) ; 

  

  for(typename std::vector<T>::const_iterator it = collection->begin(); it != collection->end(); ++it) {
    p4->push_back(it->p4());
    emEnergyFraction->push_back(it->emEnergyFraction());
    energyFractionHadronic->push_back(it->energyFractionHadronic());
    towersArea->push_back(it->towersArea());
    maxEInEmTowers->push_back(it->maxEInEmTowers());
    maxEInHadTowers->push_back(it->maxEInHadTowers());
    hadEnergyInHB->push_back(it->hadEnergyInHB());
    hadEnergyInHE->push_back(it->hadEnergyInHE());
    hadEnergyInHO->push_back(it->hadEnergyInHO());
    hadEnergyInHF->push_back(it->hadEnergyInHF());
    emEnergyInEB->push_back(it->emEnergyInEB());
    emEnergyInEE->push_back(it->emEnergyInEE());
    emEnergyInHF->push_back(it->emEnergyInHF());
    n60->push_back(it->n60()); 
    n90->push_back(it->n90()); 
  }
  
  iEvent.put( p4,  Prefix + "P4"  + Suffix );
  iEvent.put( emEnergyFraction,  Prefix + "EmEnergyFraction"  + Suffix );
  iEvent.put( energyFractionHadronic,  Prefix + "EnergyFractionHadronic"  + Suffix );
  iEvent.put( towersArea,  Prefix + "TowersArea"  + Suffix );
  iEvent.put( maxEInEmTowers,  Prefix + "MaxEInEmTowers"  + Suffix );
  iEvent.put( maxEInHadTowers,  Prefix + "MaxEInHadTowers"  + Suffix );
  iEvent.put( hadEnergyInHB,  Prefix + "HadEnergyInHB"  + Suffix );
  iEvent.put( hadEnergyInHE,  Prefix + "HadEnergyInHE"  + Suffix );
  iEvent.put( hadEnergyInHO,  Prefix + "HadEnergyInHO"  + Suffix );
  iEvent.put( hadEnergyInHF,  Prefix + "HadEnergyInHF"  + Suffix );
  iEvent.put( emEnergyInEB,  Prefix + "EmEnergyInEB"  + Suffix );
  iEvent.put( emEnergyInEE,  Prefix + "EmEnergyInEE"  + Suffix );
  iEvent.put( emEnergyInHF,  Prefix + "EmEnergyInHF"  + Suffix );
  iEvent.put( n60,  Prefix + "N60"  + Suffix ); 
  iEvent.put( n90,  Prefix + "N90"  + Suffix ); 
}


// extra information stored for PAT data
template< typename T >
void SusyCAF_Jet<T>::
producePAT(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<T> >& collection) {

  std::auto_ptr<std::vector<double> >  corrfactor   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<int> >  nAssoTracks  ( new std::vector<int>()  ) ;
  std::auto_ptr<std::vector<double> >  fHPD  ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  fRBX  ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  fSubDet1  ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  fSubDet2  ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  fSubDet3  ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  fSubDet4  ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  resEMS  ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<int> >  NECALTowers  ( new std::vector<int>()  ) ;
  std::auto_ptr<std::vector<int> >  NHCALTowers  ( new std::vector<int>()  ) ;

  for(typename std::vector<T>::const_iterator it = collection->begin(); it != collection->end(); ++it) {
    pat::Jet pJunc = (static_cast<const pat::Jet*>(&(*it)))->correctedJet("RAW"); 
    corrfactor->push_back(it->energy()/pJunc.energy());
    nAssoTracks->push_back(it->associatedTracks().size());
    fHPD->push_back(it->fHPD());
    fRBX->push_back(it->fRBX());
    fSubDet1->push_back(it->fSubDetector1());
    fSubDet2->push_back(it->fSubDetector2());
    fSubDet3->push_back(it->fSubDetector3());
    fSubDet4->push_back(it->fSubDetector4());
    resEMS->push_back(it->restrictedEMF());
    NECALTowers->push_back(it->nECALTowers());
    NHCALTowers->push_back(it->nHCALTowers());

  }
  iEvent.put( corrfactor,  Prefix + "CorrFactor"  + Suffix );
  iEvent.put( nAssoTracks,  Prefix + "NAssoTracks"  + Suffix );
  iEvent.put( fHPD,  Prefix + "FHPD"  + Suffix );
  iEvent.put( fRBX,  Prefix + "FRBX"  + Suffix );
  iEvent.put( fSubDet1,  Prefix + "FSubDet1"  + Suffix );
  iEvent.put( fSubDet2,  Prefix + "FSubDet2"  + Suffix );
  iEvent.put( fSubDet3,  Prefix + "FSubDet3"  + Suffix );
  iEvent.put( fSubDet4,  Prefix + "FSubDet4"  + Suffix );
  iEvent.put( resEMS,  Prefix + "ResEMF"  + Suffix );
  iEvent.put( NECALTowers,  Prefix + "NECALTowers"  + Suffix );
  iEvent.put( NHCALTowers,  Prefix + "NHCALTowers"  + Suffix );

}

#endif
