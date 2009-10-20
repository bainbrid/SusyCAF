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
  void produce(edm::Event &, const edm::EventSetup & );

  const edm::InputTag inputTag;
  const std::string Prefix,Suffix;
};

template< typename T >
SusyCAF_Jet<T>::SusyCAF_Jet(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
  Prefix(iConfig.getParameter<std::string>("Prefix")),
  Suffix(iConfig.getParameter<std::string>("Suffix"))
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
  //  produces <std::vector<double> > ( Prefix + "N60"  + Suffix ); 
  //  produces <std::vector<double> > ( Prefix + "N90"  + Suffix ); 
}

template< typename T >
void SusyCAF_Jet<T>::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {

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
  //  std::auto_ptr<std::vector<double> >  n60   ( new std::vector<double>()  ) ; 
  //  std::auto_ptr<std::vector<double> >  n90   ( new std::vector<double>()  ) ; 

  
  edm::Handle<std::vector<T> > jetcollection;
  iEvent.getByLabel(inputTag, jetcollection);

  for(typename std::vector<T>::const_iterator it = jetcollection->begin(); it != jetcollection->end(); ++it) {
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
    //    n60->push_back(it->n60()); 
    //    n90->push_back(it->n90()); 
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
  //  iEvent.put( n60,  Prefix + "N60"  + Suffix ); 
  //  iEvent.put( n90,  Prefix + "N90"  + Suffix ); 
}

#endif
