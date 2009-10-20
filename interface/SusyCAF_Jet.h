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
}

template< typename T >
void SusyCAF_Jet<T>::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {

  std::auto_ptr<std::vector<double> >  px   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  py   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  pt   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  phi   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  eta   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  e   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  m   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  emf   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  hadf   ( new std::vector<double>()  ) ;

  
  edm::Handle<std::vector<T> > jetcollection;
  iEvent.getByLabel(inputTag, jetcollection);

  for(typename std::vector<T>::const_iterator it = jetcollection->begin(); it != jetcollection->end(); ++it) {
    px->push_back(it->px());
    py->push_back(it->py());
    px->push_back(it->pt());
    py->push_back(it->phi());
    px->push_back(it->eta());
    py->push_back(it->e());
    px->push_back(it->m());
    py->push_back(it->emf());
    px->push_back(it->hadf());
  }
  
  iEvent.put( px,  Prefix + "px"  + Suffix );
  iEvent.put( py,  Prefix + "py"  + Suffix );
  iEvent.put( px,  Prefix + "pt"  + Suffix );
  iEvent.put( py,  Prefix + "phi"  + Suffix );
  iEvent.put( px,  Prefix + "eta"  + Suffix );
  iEvent.put( py,  Prefix + "e"  + Suffix );
  iEvent.put( px,  Prefix + "m"  + Suffix );
  iEvent.put( py,  Prefix + "emf"  + Suffix );
  iEvent.put( px,  Prefix + "hadf"  + Suffix );
}

#endif
