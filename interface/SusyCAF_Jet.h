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
  produces <std::vector<double> > ( Prefix + "px"  + Suffix );
  produces <std::vector<double> > ( Prefix + "py"  + Suffix );
  produces <std::vector<double> > ( Prefix + "pt"  + Suffix );
  produces <std::vector<double> > ( Prefix + "phi"  + Suffix );
  produces <std::vector<double> > ( Prefix + "eta"  + Suffix );
  produces <std::vector<double> > ( Prefix + "e"  + Suffix );
  produces <std::vector<double> > ( Prefix + "m"  + Suffix );
  produces <std::vector<double> > ( Prefix + "emf"  + Suffix );
  produces <std::vector<double> > ( Prefix + "hadf"  + Suffix );
}

template< typename T >
void SusyCAF_Jet<T>::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {

  std::auto_ptr<std::vector<double> >  px   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  py   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  pt   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  phi  ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  eta  ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  e    ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  m    ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  emf  ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  hadf ( new std::vector<double>()  ) ;

  
  edm::Handle<std::vector<T> > jetcollection;
  iEvent.getByLabel(inputTag, jetcollection);

  for(typename std::vector<T>::const_iterator it = jetcollection->begin(); it != jetcollection->end(); ++it) {
    px->push_back(it->px());
    py->push_back(it->py());
    pt->push_back(it->pt());
    phi->push_back(it->phi());
    eta->push_back(it->eta());
    e->push_back(it->energy());
    m->push_back(it->mass());
    emf->push_back(it->emEnergyFraction());
    hadf->push_back(it->energyFractionHadronic());
  }
  
  iEvent.put( px,  Prefix + "px"  + Suffix );
  iEvent.put( py,  Prefix + "py"  + Suffix );
  iEvent.put( pt,  Prefix + "pt"  + Suffix );
  iEvent.put( phi,  Prefix + "phi"  + Suffix );
  iEvent.put( eta,  Prefix + "eta"  + Suffix );
  iEvent.put( e,  Prefix + "e"  + Suffix );
  iEvent.put( m,  Prefix + "m"  + Suffix );
  iEvent.put( emf,  Prefix + "emf"  + Suffix );
  iEvent.put( hadf,  Prefix + "hadf"  + Suffix );
}

#endif
