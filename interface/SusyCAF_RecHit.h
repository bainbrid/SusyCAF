#ifndef SUSY_CAF_RECHIT
#define SUSY_CAF_RECHIT

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"

template< typename T >
class SusyCAF_RecHit : public edm::EDProducer {
 public: 
  explicit SusyCAF_RecHit(const edm::ParameterSet&);
 private: 
  void produce(edm::Event &, const edm::EventSetup & );

  const edm::InputTag inputTag;
  const std::string Prefix,Suffix;
};

template< typename T >
SusyCAF_RecHit<T>::SusyCAF_RecHit(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
  Prefix(iConfig.getParameter<std::string>("Prefix")),
  Suffix(iConfig.getParameter<std::string>("Suffix"))
{
  produces <float> ( Prefix + "e1" + Suffix );
  produces <float> ( Prefix + "t1" + Suffix );
  produces <int>   ( Prefix + "ieta1" + Suffix );
  produces <int>   ( Prefix + "iphi1" + Suffix );
  produces <int>   ( Prefix + "depth1" + Suffix );
}

template< typename T >
void SusyCAF_RecHit<T>::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  std::auto_ptr<float > e1     ( new float()  ) ;
  std::auto_ptr<float > t1     ( new float()  ) ;
  std::auto_ptr<int   > ieta1  ( new int()    ) ;
  std::auto_ptr<int   > iphi1  ( new int()    ) ;
  std::auto_ptr<int   > depth1 ( new int()    ) ;
  
  edm::Handle<T> rechitcollection;
  iEvent.getByLabel(inputTag, rechitcollection);

  float eMax=-1000.0;
  typename T::const_iterator specialit;
  for(typename T::const_iterator it = rechitcollection->begin(); it != rechitcollection->end(); ++it) {
    float energy=it->energy();
    if (energy>eMax) {
      eMax=energy;
      specialit=it;
    }
  }

  //need to use some value if collection is empty (not yet coded)

  *e1.get()=specialit->energy();
  *t1.get()=specialit->time();
  *ieta1.get()=specialit->id().ieta();
  *iphi1.get()=specialit->id().iphi();
  *depth1.get()=specialit->id().depth();

  iEvent.put( e1    ,  Prefix + "e1"     + Suffix );
  iEvent.put( t1    ,  Prefix + "t1"     + Suffix );
  iEvent.put( ieta1 ,  Prefix + "ieta1"  + Suffix );
  iEvent.put( iphi1 ,  Prefix + "iphi1"  + Suffix );
  iEvent.put( depth1,  Prefix + "depth1" + Suffix );
}

#endif
