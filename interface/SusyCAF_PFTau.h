#ifndef SUSY_CAF_PFTAU
#define SUSY_CAF_PFTAU

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/TauReco/interface/PFTau.h"
#include <string>


template< typename T >
class SusyCAF_PFTau : public edm::EDProducer {
 public: 
  explicit SusyCAF_PFTau(const edm::ParameterSet&);
 private:
  void initTemplate();
  void initRECO();
  void initPAT();
  void produce(edm::Event &, const edm::EventSetup & );
  void produceTemplate(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &);
  void produceRECO(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &);
  void producePAT(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &);

  typedef reco::Candidate::LorentzVector LorentzVector;
  const edm::InputTag inputTag;
  const std::string Prefix,Suffix;
};

template< typename T >
SusyCAF_PFTau<T>::SusyCAF_PFTau(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
  Prefix(iConfig.getParameter<std::string>("Prefix")),
  Suffix(iConfig.getParameter<std::string>("Suffix"))
{

  initTemplate();
}

template< typename T >
void SusyCAF_PFTau<T>::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  edm::Handle<std::vector<T> > collection;
  iEvent.getByLabel(inputTag,collection);

  produceTemplate(iEvent, iSetup, collection);
}

template<typename T>
void SusyCAF_PFTau<T>::initRECO()
{
  produces <bool> (Prefix + "HandleValid" + Suffix);
  produces <std::vector<LorentzVector> > ( Prefix + "P4" + Suffix );
  produces <std::vector<int> > (  Prefix + "Charge" + Suffix);
  produces <std::vector<math::XYZPoint> > (Prefix + "Vertex" + Suffix);

  produces <std::vector<int> > (Prefix + "NumSigTrks" + Suffix);
  produces <std::vector<int> > (Prefix + "NumIsoTrks" + Suffix);
  produces <std::vector<int> > (Prefix + "NumSigPFNeutHadrCands" + Suffix);  

  produces <std::vector<double> > (Prefix + "SumPtIsoPFNeutCands" + Suffix);
  produces <std::vector<double> > (Prefix + "NeutCandsTotEnergy" + Suffix);
  produces <std::vector<double> > (Prefix + "NeutCandsHoverHPlusE" + Suffix);

  //sigtrk 1 vars
  produces <std::vector<math::XYZVector> > (Prefix + "SigTrk1MomVect" + Suffix);
  produces <std::vector<int> > (Prefix + "SigTrk1Charge" + Suffix);
  produces <std::vector<double> > (Prefix + "SigTrk1Chi2" + Suffix);
  produces <std::vector<double> > (Prefix + "SigTrk1QoverPErr" + Suffix);
  produces <std::vector<int> > (Prefix + "SigTrk1ValHits" + Suffix);
  produces <std::vector<int> > (Prefix + "SigTrk1LostHits" + Suffix);

  //sigtrk 2 vars
  produces <std::vector<math::XYZVector> > (Prefix + "SigTrk2MomVect" + Suffix);
  produces <std::vector<int> > (Prefix + "SigTrk2Charge" + Suffix);
  produces <std::vector<double> > (Prefix + "SigTrk2Chi2" + Suffix);
  produces <std::vector<double> > (Prefix + "SigTrk2QoverPErr" + Suffix);
  produces <std::vector<int> > (Prefix + "SigTrk2ValHits" + Suffix);
  produces <std::vector<int> > (Prefix + "SigTrk2LostHits" + Suffix);

  //sigtrk 3 vars
  produces <std::vector<math::XYZVector> > (Prefix + "SigTrk3MomVect" + Suffix);
  produces <std::vector<int> > (Prefix + "SigTrk3Charge" + Suffix);
  produces <std::vector<double> > (Prefix + "SigTrk3Chi2" + Suffix);
  produces <std::vector<double> > (Prefix + "SigTrk3QoverPErr" + Suffix);
  produces <std::vector<int> > (Prefix + "SigTrk3ValHits" + Suffix);
  produces <std::vector<int> > (Prefix + "SigTrk3LostHits" + Suffix);
 
}

template< typename T >
void SusyCAF_PFTau<T>::initPAT()
{

  produces <std::vector<double> > (Prefix + "TrkIso" + Suffix);
  produces <std::vector<double> >(Prefix + "EcalIso" + Suffix);
  produces <std::vector<double> >(Prefix + "HcalIso" +Suffix);
  produces <std::vector<double> >(Prefix + "CaloIso" + Suffix);

  produces <std::vector<float> > (Prefix + "ParticleIso" + Suffix);
  produces <std::vector<float> > (Prefix + "ChargedHadronIso" + Suffix);
  produces <std::vector<float> > (Prefix + "NeutralHadronIso" + Suffix);
  produces <std::vector<float> > (Prefix + "PhotonIso" + Suffix);

  produces <std::vector<float> > (Prefix + "TauIdagainstElectron" + Suffix);
  produces <std::vector<float> > (Prefix + "TauIdagainstMuon" + Suffix);
  produces <std::vector<float> > (Prefix + "TauIdbyIsolation" + Suffix);
  produces <std::vector<float> > (Prefix + "TauIdbyTaNC" + Suffix);
  produces <std::vector<float> > (Prefix + "TauIdbyTaNCfrHalfPercent" + Suffix);
  produces <std::vector<float> > (Prefix + "TauIdbyTaNCfrOnePercent" + Suffix);
  produces <std::vector<float> > (Prefix + "TauIdbyTaNCfrQuarterPercent" + Suffix);
  produces <std::vector<float> > (Prefix + "TauIdbyTaNCfrTenthPercent" + Suffix);
  produces <std::vector<float> > (Prefix + "TauIdecalIsolation" + Suffix);
  produces <std::vector<float> > (Prefix + "TauIdecalIsolationUsingLeadingPion" + Suffix);
  produces <std::vector<float> > (Prefix + "TauIdleadingPionPtCut" + Suffix);
  produces <std::vector<float> > (Prefix + "TauIdleadingTrackFinding" + Suffix);
  produces <std::vector<float> > (Prefix + "TauIdleadingTrackPtCut" + Suffix);
  produces <std::vector<float> > (Prefix + "TauIdtrackIsolation" + Suffix);
  produces <std::vector<float> > (Prefix + "TauIdtrackIsolationUsingLeadingPion" + Suffix);
  produces <std::vector<float> > (Prefix + "TauIdbyIsolationUsingLeadingPion" + Suffix);

}




template< typename T >
void SusyCAF_PFTau<T>::
produceRECO(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<T> >& collection) {
  std::auto_ptr<bool> isHandleValid (new bool(collection.isValid()) );
  std::auto_ptr<std::vector<LorentzVector> > p4 ( new std::vector<LorentzVector>() );
  std::auto_ptr<std::vector<int> >  charge   ( new std::vector<int>()  ) ;
  std::auto_ptr<std::vector<math::XYZPoint> > vertex (new std::vector<math::XYZPoint>() );

  std::auto_ptr<std::vector<int> > numSigTrks (new std::vector<int>() );
  std::auto_ptr<std::vector<int> > numIsoTrks (new std::vector<int>() );
  std::auto_ptr<std::vector<int> > numSigPFNeuHadCands (new std::vector<int> () );
  std::auto_ptr<std::vector<double> > SumPtIsoTrks (new std::vector<double> () );
  std::auto_ptr<std::vector<double> > NeutCandstotE (new std::vector<double> () );
  std::auto_ptr<std::vector<double> > NeutCandsHoHplusE (new std::vector<double> () );
 
  reco::TrackRefVector SigTrks;// IsoTrks;
  // reco::PFCandidateRefVector SigPFNeutHadCands;

  //sigtrk 1
  std::auto_ptr<std::vector<math::XYZVector> >SigTrk1Mom (new std::vector<math::XYZVector>() );
  //eta, phi,d0, dz etc. can be got from momentum with a bit of manipulation
  std::auto_ptr<std::vector<int> > SigTrk1Charge (new std::vector<int>() );
  std::auto_ptr<std::vector<double> > SigTrk1Chi2 (new std::vector<double>() );
  std::auto_ptr<std::vector<double> > SigTrk1QoverPErr (new std::vector<double>());
  std::auto_ptr<std::vector<int > >SigTrk1ValHits (new std::vector<int> () );
  std::auto_ptr<std::vector<int> > SigTrk1LostHits (new std::vector<int> () );

  //sigtrk 2
 std::auto_ptr<std::vector<math::XYZVector> >SigTrk2Mom (new std::vector<math::XYZVector>() );
  //eta, phi,d0, dz etc. can be got from momentum with a bit of manipulation
  std::auto_ptr<std::vector<int> > SigTrk2Charge (new std::vector<int>() );
  std::auto_ptr<std::vector<double> > SigTrk2Chi2 (new std::vector<double>() );
  std::auto_ptr<std::vector<double> > SigTrk2QoverPErr (new std::vector<double>());
  std::auto_ptr<std::vector<int > >SigTrk2ValHits (new std::vector<int> () );
  std::auto_ptr<std::vector<int> > SigTrk2LostHits (new std::vector<int> () );

  //sigtrk 3
 std::auto_ptr<std::vector<math::XYZVector> >SigTrk3Mom (new std::vector<math::XYZVector>() );
  //eta, phi,d0, dz etc. can be got from momentum with a bit of manipulation
  std::auto_ptr<std::vector<int> > SigTrk3Charge (new std::vector<int>() );
  std::auto_ptr<std::vector<double> > SigTrk3Chi2 (new std::vector<double>() );
  std::auto_ptr<std::vector<double> > SigTrk3QoverPErr (new std::vector<double>());
  std::auto_ptr<std::vector<int > >SigTrk3ValHits (new std::vector<int> () );
  std::auto_ptr<std::vector<int> > SigTrk3LostHits (new std::vector<int> () );

  
  for(typename std::vector<T>::const_iterator it = collection->begin(); it!=collection->end(); it++) {
   
    if(collection.isValid()){
    p4->push_back(it->p4());
    charge->push_back(it->charge());
    vertex->push_back(it->vertex());

    SigTrks=it->signalTracks();
//     IsoTrks=it->isolationTracks();
//     SigPFNeutHadCands=it->signalPFNeutrHadrCands();

    numSigTrks->push_back(SigTrks.size());
    numIsoTrks->push_back((it->isolationTracks()).size());
    numSigPFNeuHadCands->push_back((it->signalPFNeutrHadrCands()).size());

    double sumptisotrks=0.0;
    for(reco::track_iterator isotrk = (it->isolationTracks()).begin(); isotrk!=(it->isolationTracks()).end(); isotrk++){
      sumptisotrks+=(*isotrk)->pt();
    }

    SumPtIsoTrks->push_back(sumptisotrks);

    double ecaltauen = 0.0, hcaltauen = 0.0;

    if(it->signalPFNeutrHadrCands().isAvailable()){
	for(reco::PFCandidateRefVector::const_iterator sigNCands = (it->signalPFNeutrHadrCands()).begin(); sigNCands!=(it->signalPFNeutrHadrCands()).end(); sigNCands++){
	  ecaltauen += (*sigNCands)->ecalEnergy();
	  hcaltauen += (*sigNCands)->hcalEnergy();
	}
      }
      NeutCandstotE->push_back(ecaltauen+hcaltauen);
      if(ecaltauen+hcaltauen>0.0){
	NeutCandsHoHplusE->push_back(hcaltauen/(hcaltauen+ecaltauen));
      }
      
      if(SigTrks.size()>0){
	SigTrk1Mom->push_back(SigTrks[0]->momentum());
	SigTrk1Charge->push_back(SigTrks[0]->charge());
	SigTrk1Chi2->push_back(SigTrks[0]->chi2());
	SigTrk1QoverPErr->push_back(SigTrks[0]->qoverpError());
	SigTrk1ValHits->push_back(SigTrks[0]->numberOfValidHits());
	SigTrk1LostHits->push_back(SigTrks[0]->numberOfLostHits());
      }
      if(SigTrks.size()>1){
	SigTrk2Mom->push_back(SigTrks[1]->momentum());
	SigTrk2Charge->push_back(SigTrks[1]->charge());
	SigTrk2Chi2->push_back(SigTrks[1]->chi2());
	SigTrk2QoverPErr->push_back(SigTrks[1]->qoverpError());
	SigTrk2ValHits->push_back(SigTrks[1]->numberOfValidHits());
	SigTrk2LostHits->push_back(SigTrks[1]->numberOfLostHits());
      }
      if(SigTrks.size()>2){
	SigTrk3Mom->push_back(SigTrks[2]->momentum());
	SigTrk3Charge->push_back(SigTrks[2]->charge());
	SigTrk3Chi2->push_back(SigTrks[2]->chi2());
	SigTrk3QoverPErr->push_back(SigTrks[2]->qoverpError());
	SigTrk3ValHits->push_back(SigTrks[2]->numberOfValidHits());
	SigTrk3LostHits->push_back(SigTrks[2]->numberOfLostHits());
      }
      
      
      
      }
    }
    
    iEvent.put(isHandleValid, Prefix + "HandleValid" + Suffix);
    iEvent.put( p4,  Prefix + "P4" + Suffix );
    iEvent.put(charge,  Prefix + "Charge" + Suffix);
    iEvent.put(vertex ,Prefix + "Vertex" + Suffix);
    iEvent.put(numSigTrks, Prefix + "NumSigTrks" + Suffix);
    iEvent.put(numIsoTrks, Prefix + "NumIsoTrks" + Suffix);
    iEvent.put(numSigPFNeuHadCands, Prefix + "NumSigPFNeutHadrCands" + Suffix);  
    iEvent.put(SumPtIsoTrks, Prefix + "SumPtIsoPFNeutCands" + Suffix);
    iEvent.put(NeutCandstotE, Prefix + "NeutCandsTotEnergy" + Suffix);
    iEvent.put(NeutCandsHoHplusE, Prefix + "NeutCandsHoverHPlusE" + Suffix);
    
    iEvent.put(SigTrk1Mom, Prefix + "SigTrk1MomVect" + Suffix);
    iEvent.put(SigTrk1Charge,Prefix + "SigTrk1Charge" + Suffix);
    iEvent.put(SigTrk1Chi2, Prefix + "SigTrk1Chi2" + Suffix);
    iEvent.put(SigTrk1QoverPErr, Prefix + "SigTrk1QoverPErr" + Suffix);
    iEvent.put(SigTrk1ValHits, Prefix + "SigTrk1ValHits" + Suffix);
    iEvent.put(SigTrk1LostHits, Prefix + "SigTrk1LostHits" + Suffix);
    
    iEvent.put(SigTrk2Mom, Prefix + "SigTrk2MomVect" + Suffix);
    iEvent.put(SigTrk2Charge,Prefix + "SigTrk2Charge" + Suffix);
    iEvent.put(SigTrk2Chi2, Prefix + "SigTrk2Chi2" + Suffix);
    iEvent.put(SigTrk2QoverPErr, Prefix + "SigTrk2QoverPErr" + Suffix);
    iEvent.put(SigTrk2ValHits, Prefix + "SigTrk2ValHits" + Suffix);
    iEvent.put(SigTrk2LostHits, Prefix + "SigTrk2LostHits" + Suffix);
    
    iEvent.put(SigTrk3Mom, Prefix + "SigTrk3MomVect" + Suffix);
    iEvent.put(SigTrk3Charge,Prefix + "SigTrk3Charge" + Suffix);
    iEvent.put(SigTrk3Chi2, Prefix + "SigTrk3Chi2" + Suffix);
    iEvent.put(SigTrk3QoverPErr, Prefix + "SigTrk3QoverPErr" + Suffix);
    iEvent.put(SigTrk3ValHits, Prefix + "SigTrk3ValHits" + Suffix);
    iEvent.put(SigTrk3LostHits, Prefix + "SigTrk3LostHits" + Suffix);
    
  }
  
  // extra information stored for PAT data
  template< typename T >
    void SusyCAF_PFTau<T>::
    producePAT(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<T> >& collection) {
    
    std::auto_ptr<std::vector<double> > trkiso (new std::vector<double>());
    std::auto_ptr<std::vector<double> > ecaliso (new std::vector<double>());
    std::auto_ptr<std::vector<double> > hcaliso (new std::vector<double>());
    std::auto_ptr<std::vector<double> > caloiso (new std::vector<double>());
    
    std::auto_ptr<std::vector<float> > partIso (new std::vector<float>() );
    std::auto_ptr<std::vector<float> > charHadIso (new std::vector<float>() );
    std::auto_ptr<std::vector<float> > neutHadIso (new std::vector<float>() );
    std::auto_ptr<std::vector<float> > photIso (new std::vector<float>() );

    //tau disciminators
//     std::auto_ptr<std::vector<float> > againstEl (new std::vector<float>());
//     std::auto_ptr<std::vector<float> > againstMu (new std::vector<float>());
//     std::auto_ptr<std::vector<float> > byIso (new std::vector<float>());
//     std::auto_ptr<std::vector<float> > byIsoleadPion (new std::vector<float>());
//     std::auto_ptr<std::vector<float> > byTaNC (new std::vector<float>());
//     std::auto_ptr<std::vector<float> > byTaNCfrHalfPercent (new std::vector<float>());
//     std::auto_ptr<std::vector<float> > byTaNCfrQuartPercent (new std::vector<float>());
//     std::auto_ptr<std::vector<float> > byTaNCfrTenthPercent (new std::vector<float>());
//     std::auto_ptr<std::vector<float> > ecalIso (new std::vector<float>());
//     std::auto_ptr<std::vector<float> > ecalIsoleadPion (new std::vector<float>());
//     std::auto_ptr<std::vector<float> > leadPionptCut (new std::vector<float>());
//     std::auto_ptr<std::vector<float> > leadTrkFinding (new std::vector<float>());
//     std::auto_ptr<std::vector<float> > trkIso (new std::vector<float>());
//     std::auto_ptr<std::vector<float> > trkIsoleadPion (new std::vector<float>());
    
    std::map<std::string, std::vector<float> *> TauDiscs; //fill map with pointers rather than auto_ptr
    TauDiscs["againstElectron"] = new std::vector<float>();
    TauDiscs["againstMuon"] = new std::vector<float>();
    TauDiscs["byIsolation"] = new std::vector<float>();
    TauDiscs["byTaNC"] = new std::vector<float>();
    TauDiscs["byTaNCfrHalfPercent"] = new std::vector<float>();
    TauDiscs["byTaNCfrOnePercent"] = new std::vector<float>();
    TauDiscs ["byTaNCfrQuarterPercent"] = new std::vector<float>();
    TauDiscs ["byTaNCfrTenthPercent"] = new std::vector<float>();
    TauDiscs ["ecalIsolation"] = new std::vector<float>();
    TauDiscs ["ecalIsolationUsingLeadingPion"] = new std::vector<float>();
    TauDiscs ["leadingPionPtCut"] = new std::vector<float>();
    TauDiscs ["leadingTrackFinding"] = new std::vector<float>();
    TauDiscs ["leadingTrackPtCut"] = new std::vector<float>();
    TauDiscs ["trackIsolation"] = new std::vector<float>();
    TauDiscs ["trackIsolationUsingLeadingPion"] = new std::vector<float>();
    TauDiscs ["byIsolationUsingLeadingPion"] = new std::vector<float>();
    
    for(std::vector<pat::Tau>::const_iterator it = collection->begin(); it!=collection->end(); it++){
      
      trkiso->push_back(it->trackIso());
      ecaliso->push_back(it->ecalIso());
      hcaliso->push_back(it->hcalIso());
      caloiso->push_back(it->caloIso());
      
      partIso->push_back(it->particleIso());
      charHadIso->push_back(it->chargedHadronIso());
      neutHadIso->push_back(it->neutralHadronIso());
      photIso->push_back(it->photonIso());
      
      
      for(std::vector<std::pair<std::string, float> >::const_iterator tauid=it->tauIDs().begin(); tauid!=it->tauIDs().end(); tauid++)
	{
	  if(TauDiscs.count(tauid->first)){

	    TauDiscs[tauid->first]->push_back(tauid->second);

	  }
	  else{
	    std::cout<<"Unrecoginsed TauDiscriminator =" << tauid->first << std::endl;
	  }
	  
	}
      
      
    }
    
    iEvent.put(trkiso, Prefix + "TrkIso" + Suffix);
    iEvent.put(ecaliso, Prefix + "EcalIso" + Suffix);
    iEvent.put(hcaliso, Prefix + "HcalIso"+ Suffix);
    iEvent.put(caloiso, Prefix + "CaloIso" + Suffix);
    iEvent.put(partIso, Prefix + "ParticleIso" + Suffix);
    iEvent.put(charHadIso, Prefix + "ChargedHadronIso" + Suffix);
    iEvent.put(neutHadIso, Prefix + "NeutralHadronIso" + Suffix);
    iEvent.put(photIso, Prefix + "PhotonIso" + Suffix);
    for(std::map<std::string, std::vector<float> *>::iterator tauid = TauDiscs.begin();
	tauid != TauDiscs.end(); tauid++){
	  iEvent.put(std::auto_ptr<std::vector<float> >(tauid->second), Prefix + "TauId" + tauid->first + Suffix);
    }

  }
  
#endif
  
