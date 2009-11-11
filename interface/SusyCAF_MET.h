#ifndef SUSY_CAF_MET
#define SUSY_CAF_MET

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"

template< typename T >
class SusyCAF_MET : public edm::EDProducer {
 public: 
  explicit SusyCAF_MET(const edm::ParameterSet&);
 private: 
  void produce(edm::Event &, const edm::EventSetup & );

  const edm::InputTag inputTag;
  const std::string Prefix,Suffix;
};

template< typename T >
SusyCAF_MET<T>::SusyCAF_MET(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
  Prefix(iConfig.getParameter<std::string>("Prefix")),
  Suffix(iConfig.getParameter<std::string>("Suffix"))
{
  produces <std::vector<reco::Candidate::LorentzVector> > ( Prefix + "P4"  + Suffix );
  produces <std::vector<double> > ( Prefix + "MetSignificance"  + Suffix );
  produces <std::vector<double> > ( Prefix + "CaloMETInmHF"  + Suffix );
  produces <std::vector<double> > ( Prefix + "CaloMETInpHF"  + Suffix );
  produces <std::vector<double> > ( Prefix + "CaloMETPhiInmHF"  + Suffix );
  produces <std::vector<double> > ( Prefix + "CaloMETPhiInpHF"  + Suffix );
  produces <std::vector<double> > ( Prefix + "CaloSETInmHF"  + Suffix );
  produces <std::vector<double> > ( Prefix + "CaloSETInpHF"  + Suffix );
  produces <std::vector<double> > ( Prefix + "EmEtFraction"  + Suffix );
  produces <std::vector<double> > ( Prefix + "EtFractionHadronic"  + Suffix );
  produces <std::vector<double> > ( Prefix + "MaxEtInEmTowers"  + Suffix );
  produces <std::vector<double> > ( Prefix + "MaxEtInHadTowers"  + Suffix );
  produces <std::vector<double> > ( Prefix + "EmEtInEB"  + Suffix );
  produces <std::vector<double> > ( Prefix + "EmEtInEE"  + Suffix );
  produces <std::vector<double> > ( Prefix + "EmEtInHF"  + Suffix );
  produces <std::vector<double> > ( Prefix + "HadEtInHB"  + Suffix );
  produces <std::vector<double> > ( Prefix + "HadEtInHE"  + Suffix );
  produces <std::vector<double> > ( Prefix + "HadEtInHF"  + Suffix );
  produces <std::vector<double> > ( Prefix + "HadEtInHO"  + Suffix );
  }

template< typename T >
void SusyCAF_MET<T>::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  std::auto_ptr<std::vector<reco::Candidate::LorentzVector> >  p4  ( new std::vector<reco::Candidate::LorentzVector>()  ) ;
  std::auto_ptr<std::vector<double> >  metSignificance    ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  CaloMETInmHF       ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  CaloMETInpHF       ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  CaloMETPhiInmHF    ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  CaloMETPhiInpHF    ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  CaloSETInmHF       ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  CaloSETInpHF       ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  emEtFraction       ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  etFractionHadronic ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  maxEtInEmTowers    ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  maxEtInHadTowers   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  emEtInEB           ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  emEtInEE           ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  emEtInHF           ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  hadEtInHB          ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  hadEtInHE          ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  hadEtInHF          ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<double> >  hadEtInHO          ( new std::vector<double>()  ) ;

  edm::Handle<std::vector<T> > metcollection;
  iEvent.getByLabel(inputTag, metcollection);

  for(typename std::vector<T>::const_iterator it = metcollection->begin(); it != metcollection->end(); ++it) {
    p4->push_back(it->p4());
    metSignificance->push_back(it->metSignificance());
    CaloMETInmHF->push_back(it->CaloMETInmHF());
    CaloMETInpHF->push_back(it->CaloMETInpHF());
    CaloMETPhiInmHF->push_back(it->CaloMETPhiInmHF());
    CaloMETPhiInpHF->push_back(it->CaloMETPhiInpHF());
    CaloSETInmHF->push_back(it->CaloSETInmHF());
    CaloSETInpHF->push_back(it->CaloSETInpHF());
    emEtFraction->push_back(it->emEtFraction());
    etFractionHadronic->push_back(it->etFractionHadronic());
    maxEtInEmTowers->push_back(it->maxEtInEmTowers());
    maxEtInHadTowers->push_back(it->maxEtInHadTowers());
    emEtInEB->push_back(it->emEtInEB());
    emEtInEE->push_back(it->emEtInEE());
    emEtInHF->push_back(it->emEtInHF());
    hadEtInHB->push_back(it->hadEtInHB());
    hadEtInHE->push_back(it->hadEtInHE());
    hadEtInHF->push_back(it->hadEtInHF());
    hadEtInHO->push_back(it->hadEtInHO());         
  }

  iEvent.put( p4,  Prefix + "P4"  + Suffix );
  iEvent.put( metSignificance   ,  Prefix + "MetSignificance"  + Suffix );
  iEvent.put( CaloMETInmHF      ,  Prefix + "CaloMETInmHF"  + Suffix );
  iEvent.put( CaloMETInpHF      ,  Prefix + "CaloMETInpHF"  + Suffix );
  iEvent.put( CaloMETPhiInmHF   ,  Prefix + "CaloMETPhiInmHF"  + Suffix );
  iEvent.put( CaloMETPhiInpHF   ,  Prefix + "CaloMETPhiInpHF"  + Suffix );
  iEvent.put( CaloSETInmHF      ,  Prefix + "CaloSETInmHF"  + Suffix );
  iEvent.put( CaloSETInpHF      ,  Prefix + "CaloSETInpHF"  + Suffix );
  iEvent.put( emEtFraction      ,  Prefix + "EmEtFraction"  + Suffix );
  iEvent.put( etFractionHadronic,  Prefix + "EtFractionHadronic"  + Suffix );
  iEvent.put( maxEtInEmTowers   ,  Prefix + "MaxEtInEmTowers"  + Suffix );
  iEvent.put( maxEtInHadTowers  ,  Prefix + "MaxEtInHadTowers"  + Suffix );
  iEvent.put( emEtInEB          ,  Prefix + "EmEtInEB"  + Suffix );
  iEvent.put( emEtInEE          ,  Prefix + "EmEtInEE"  + Suffix );
  iEvent.put( emEtInHF          ,  Prefix + "EmEtInHF"  + Suffix );
  iEvent.put( hadEtInHB         ,  Prefix + "HadEtInHB"  + Suffix );
  iEvent.put( hadEtInHE         ,  Prefix + "HadEtInHE"  + Suffix );
  iEvent.put( hadEtInHF         ,  Prefix + "HadEtInHF"  + Suffix );
  iEvent.put( hadEtInHO         ,  Prefix + "HadEtInHO"  + Suffix );
}

#endif
