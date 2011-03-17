#ifndef SUSY_CAF_MET
#define SUSY_CAF_MET

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/PatCandidates/interface/MET.h"

template< typename T >
class SusyCAF_MET : public edm::EDProducer {
 public: 
  explicit SusyCAF_MET(const edm::ParameterSet&);
 private: 
  void produce(edm::Event&, const edm::EventSetup& );
  void produceSpecial(edm::Event&, const T& );
  void produceCalo(edm::Event&, const T& );
  void produceGenMetMatch(edm::Event&, const T&);
  void initSpecial();
  void initCalo();
  void initGenMetMatch();
  const edm::InputTag inputTag;
  const bool special, caloSpecific;
  const std::string Prefix,Suffix;
};


template< typename T >
SusyCAF_MET<T>::SusyCAF_MET(const edm::ParameterSet& cfg) :
  inputTag(cfg.getParameter<edm::InputTag>("InputTag")),
  special(cfg.getParameter<bool>("ProduceSpecial")),
  caloSpecific(cfg.getParameter<bool>("Calo")),
  Prefix(cfg.getParameter<std::string>("Prefix")),
  Suffix(cfg.getParameter<std::string>("Suffix"))
{
  produces <reco::Candidate::LorentzVector> ( Prefix + "P4"  + Suffix );
  produces <double>                         ( Prefix + "SumEt" + Suffix );
  /* Methods not available or const correct in 3_3_4
  produces <double>                         ( Prefix + "Significance"  + Suffix );
  produces <std::vector<double> >           ( Prefix + "DmEx" + Suffix );
  produces <std::vector<double> >           ( Prefix + "DmEy" + Suffix );
  produces <std::vector<double> >           ( Prefix + "DsumEt" + Suffix );
  produces <std::vector<double> >           ( Prefix + "Dsignificance" + Suffix );
  */
  if(special) initSpecial();
 
}

template<> void SusyCAF_MET<reco::CaloMET>::initSpecial() { initCalo(); }
template<> void SusyCAF_MET<pat::MET>::initSpecial() { 
  initCalo();
  initGenMetMatch();  
  }

template<> void SusyCAF_MET<reco::PFMET>::initSpecial() {
  /* Methods not available in 3_3_4 
  produces<double>(Prefix+ "NeutralEMEtFraction"+Suffix);  
  produces<double>(Prefix+ "NeutralHadEtFraction"+Suffix);
  produces<double>(Prefix+ "ChargedEMEtFraction"+Suffix);
  produces<double>(Prefix+ "ChargedHadEtFraction"+Suffix);
  produces<double>(Prefix+ "MuonEtFraction"+Suffix);
  produces<double>(Prefix+ "Type6EtFraction"+Suffix);
  produces<double>(Prefix+ "Type7EtFraction"+Suffix);
  */
}

template<class T>
void SusyCAF_MET<T>::
initCalo() {
  if(!caloSpecific) return;
  produces <double> ( Prefix + "CaloMETInmHF"  + Suffix );
  produces <double> ( Prefix + "CaloMETInpHF"  + Suffix );
  produces <double> ( Prefix + "CaloMETPhiInmHF"  + Suffix );
  produces <double> ( Prefix + "CaloMETPhiInpHF"  + Suffix );
  produces <double> ( Prefix + "CaloSETInmHF"  + Suffix );
  produces <double> ( Prefix + "CaloSETInpHF"  + Suffix );

  produces <double> ( Prefix + "EmEtFraction"  + Suffix );
  produces <double> ( Prefix + "EtFractionHadronic"  + Suffix );
  produces <double> ( Prefix + "MaxEtInEmTowers"  + Suffix );
  produces <double> ( Prefix + "MaxEtInHadTowers"  + Suffix );
  produces <double> ( Prefix + "EmEtInEB"  + Suffix );
  produces <double> ( Prefix + "EmEtInEE"  + Suffix );
  produces <double> ( Prefix + "EmEtInHF"  + Suffix );
  produces <double> ( Prefix + "HadEtInHB"  + Suffix );
  produces <double> ( Prefix + "HadEtInHE"  + Suffix );
  produces <double> ( Prefix + "HadEtInHF"  + Suffix );
  produces <double> ( Prefix + "HadEtInHO"  + Suffix ); 
  
}


template< typename T >
void SusyCAF_MET<T>::
produce(edm::Event& event, const edm::EventSetup& setup) {
  edm::Handle<std::vector<T> > metcollection;
  event.getByLabel(inputTag, metcollection);
  const T& met = metcollection->at(0);

  event.put(std::auto_ptr<reco::Candidate::LorentzVector>( new reco::Candidate::LorentzVector(met.p4()) ), Prefix+"P4"+Suffix);
  event.put(std::auto_ptr<double>( new double(     met.sumEt() )),         Prefix+"SumEt"        +Suffix);
  /* Methods not available or  const correct in 3_3_4
  event.put(std::auto_ptr<double>( new double(     met.significance() )),  Prefix+"Significance" +Suffix);
  event.put(std::auto_ptr<std::vector<double> >( &(met.dmEx()) ),          Prefix+"DmEx"         +Suffix);
  event.put(std::auto_ptr<std::vector<double> >( &(met.dmEy()) ),          Prefix+"DmEy"         +Suffix);
  event.put(std::auto_ptr<std::vector<double> >( &(met.dsumEt()) ),        Prefix+"DsumEt"       +Suffix);
  event.put(std::auto_ptr<std::vector<double> >( &(met.dsignificance()) ), Prefix+"Dsignificance"+Suffix);
  */
if(special) produceSpecial(event, met);
  
}

template<> void SusyCAF_MET<reco::CaloMET>::produceSpecial(edm::Event& event, const reco::CaloMET& met) { produceCalo(event,met);}
template<> void SusyCAF_MET<pat::MET>::produceSpecial(edm::Event& event, const pat::MET& met) { 
  produceCalo(event,met);
  produceGenMetMatch(event,met);


}
template<> void SusyCAF_MET<reco::PFMET>::produceSpecial(edm::Event& event, const reco::PFMET& met) {
  /* Methods not available in 3_3_4 
  event.put( std::auto_ptr<double>( new double(met.NeutralEMEtFraction()) ) , Prefix+ "NeutralEMEtFraction"+Suffix);
  event.put( std::auto_ptr<double>( new double(met.NeutralHadEtFraction())),  Prefix+ "NeutralHadEtFraction"+Suffix); 
  event.put( std::auto_ptr<double>( new double(met.ChargedEMEtFraction())),   Prefix+ "ChargedEMEtFraction"+Suffix);  
  event.put( std::auto_ptr<double>( new double(met.ChargedHadEtFraction())),  Prefix+ "ChargedHadEtFraction"+Suffix); 
  event.put( std::auto_ptr<double>( new double(met.MuonEtFraction())),        Prefix+ "MuonEtFraction"+Suffix);	   
  event.put( std::auto_ptr<double>( new double(met.Type6EtFraction())),       Prefix+ "Type6EtFraction"+Suffix);	   
  event.put( std::auto_ptr<double>( new double(met.Type7EtFraction())),       Prefix+ "Type7EtFraction"+Suffix);	   
  */
}

template< typename T>
void SusyCAF_MET<T>::
produceCalo(edm::Event& event, const T& met) {
  if(!caloSpecific) return;
  event.put( std::auto_ptr<double>( new double(met.CaloMETInmHF())), Prefix+"CaloMETInmHF"+Suffix);
  event.put( std::auto_ptr<double>( new double(met.CaloMETInpHF())), Prefix+"CaloMETInpHF"+Suffix);
  event.put( std::auto_ptr<double>( new double(met.CaloMETPhiInmHF())), Prefix+"CaloMETPhiInmHF"+Suffix);
  event.put( std::auto_ptr<double>( new double(met.CaloMETPhiInpHF())), Prefix+"CaloMETPhiInpHF"+Suffix);
  event.put( std::auto_ptr<double>( new double(met.CaloSETInmHF())), Prefix+"CaloSETInmHF"+Suffix);
  event.put( std::auto_ptr<double>( new double(met.CaloSETInpHF())), Prefix+"CaloSETInpHF"+Suffix);

  event.put( std::auto_ptr<double>( new double(met.emEtFraction())), Prefix+"EmEtFraction"+Suffix);
  event.put( std::auto_ptr<double>( new double(met.etFractionHadronic())), Prefix+"EtFractionHadronic"+Suffix);
  event.put( std::auto_ptr<double>( new double(met.maxEtInEmTowers())), Prefix+"MaxEtInEmTowers"+Suffix);
  event.put( std::auto_ptr<double>( new double(met.maxEtInHadTowers())), Prefix+"MaxEtInHadTowers"+Suffix);

  event.put( std::auto_ptr<double>( new double(met.emEtInEB())), Prefix+"EmEtInEB"+Suffix);
  event.put( std::auto_ptr<double>( new double(met.emEtInEE())), Prefix+"EmEtInEE"+Suffix);
  event.put( std::auto_ptr<double>( new double(met.emEtInHF())), Prefix+"EmEtInHF"+Suffix);

  event.put( std::auto_ptr<double>( new double(met.hadEtInHB())), Prefix+"HadEtInHB"+Suffix);
  event.put( std::auto_ptr<double>( new double(met.hadEtInHE())), Prefix+"HadEtInHE"+Suffix);
  event.put( std::auto_ptr<double>( new double(met.hadEtInHF())), Prefix+"HadEtInHF"+Suffix);
  event.put( std::auto_ptr<double>( new double(met.hadEtInHF())), Prefix+"HadEtInHO"+Suffix);
}

template<class T> void SusyCAF_MET<T>::
initGenMetMatch() {//maybe add option to turn GenMetMatching on and off?
  produces <int> (Prefix + "GenMetMatchExists" + Suffix);
  produces <reco::Candidate::LorentzVector> (Prefix + "GenMetP4" + Suffix);
}

template<class T> void SusyCAF_MET<T>::
produceGenMetMatch(edm::Event& evt, const T& met){
  std::auto_ptr<int> GenMetMatchExists(new int());
  std::auto_ptr<reco::Candidate::LorentzVector> genMetP4 (new reco::Candidate::LorentzVector() );
  const reco::GenMET *genmet = met.genMET();
    if(genmet){
      *GenMetMatchExists=1;
      *genMetP4= (met.genMET())->p4();
    }
    else{
      *GenMetMatchExists=0;
    }
   

evt.put(GenMetMatchExists, Prefix + "GenMetMatchExists" + Suffix);
evt.put(genMetP4, Prefix + "GenMetP4" + Suffix);
}

#endif
