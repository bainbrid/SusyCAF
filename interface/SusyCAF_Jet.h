#ifndef SUSY_CAF_JET
#define SUSY_CAF_JET

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackBase.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "PhysicsTools/PatUtils/interface/JetIDSelectionFunctor.h"


template< typename T >
class SusyCAF_Jet : public edm::EDProducer {
 public: 
  explicit SusyCAF_Jet(const edm::ParameterSet&);
 private: 
  typedef reco::TrackBase::Vector     Vector; 
  //
  void initTemplate(edm::Handle<reco::CaloJet> &);
  void initTemplate(edm::Handle<pat::Jet> &);
  void initRECO();
  void initPAT();
  //
  void produce(edm::Event &, const edm::EventSetup & );
  void produceTemplate(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<reco::CaloJet> > &, edm::Handle<reco::VertexCollection>& vertices);
  void produceTemplate(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<pat::Jet> > &, edm::Handle<reco::VertexCollection>& vertices);
  void produceRECO(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &);
  void producePAT(edm::Event &, const edm::EventSetup &, edm::Handle<std::vector<T> > &, edm::Handle<reco::VertexCollection>& vertices);

  const edm::InputTag inputTag, primaryVertexTag;
  const double maxD0trk,minPttrk,maxPttrk,maxChi2trk;
  const std::string Prefix,Suffix;
  JetIDSelectionFunctor   minimalJetID, looseJetID, tightJetID;
};

template< typename T >
SusyCAF_Jet<T>::SusyCAF_Jet(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
  primaryVertexTag(iConfig.getParameter<edm::InputTag>("PrimaryVertexTag")),
  maxD0trk(iConfig.getParameter<double>("MaxD0Trk")),
  minPttrk(iConfig.getParameter<double>("MinPtTrk")),
  maxPttrk(iConfig.getParameter<double>("MaxPtTrk")),
  maxChi2trk(iConfig.getParameter<double>("MaxChi2Trk")),
  Prefix(iConfig.getParameter<std::string>("Prefix")),
  Suffix(iConfig.getParameter<std::string>("Suffix")),
  minimalJetID(JetIDSelectionFunctor::CRAFT08, JetIDSelectionFunctor::MINIMAL),
  looseJetID(JetIDSelectionFunctor::CRAFT08, JetIDSelectionFunctor::LOOSE),
  tightJetID(JetIDSelectionFunctor::CRAFT08, JetIDSelectionFunctor::TIGHT)
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
  produces <std::vector<reco::Candidate::LorentzVector> > ( Prefix + "CorrectedP4"  + Suffix );
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
  produces <std::vector<int> > ( Prefix + "N60Towers"  + Suffix ); 
  produces <std::vector<int> > ( Prefix + "N90Towers"  + Suffix ); 
}

// extra information stored for PAT data
template< typename T >
void SusyCAF_Jet<T>::initPAT()
{
  produces <std::vector<double> > ( Prefix + "CorrFactor"  + Suffix );
  produces <std::vector<int> > ( Prefix + "NAssoTracksEverything"  + Suffix );
  produces <std::vector<int> > ( Prefix + "NAssoTracksAll"  + Suffix );
  produces <std::vector<int> > ( Prefix + "NAssoTracksLoose"  + Suffix );
  produces <std::vector<int> > ( Prefix + "NAssoTracksTight"  + Suffix );
  produces <std::vector<int> > ( Prefix + "NAssoTracksHighPurity"  + Suffix );
  produces <std::vector<int> > ( Prefix + "NAssoTracksConfirmed"  + Suffix );
  produces <std::vector<int> > ( Prefix + "NAssoTracksGoodIterative"  + Suffix );
  produces <Vector> ( Prefix + "MPTwithEverything"  + Suffix );
  produces <Vector> ( Prefix + "MPTwithAllTracks"  + Suffix );
  produces <Vector> ( Prefix + "MPTwithLooseTracks"  + Suffix );
  produces <Vector> ( Prefix + "MPTwithTightTracks"  + Suffix );
  produces <Vector> ( Prefix + "MPTwithHighPurityTracks"  + Suffix );
  produces <Vector> ( Prefix + "MPTwithConfirmedTracks"  + Suffix );
  produces <Vector> ( Prefix + "MPTwithGoodIterativeTracks"  + Suffix );
  produces <std::vector<double> > ( Prefix + "JetIDFHPD"  + Suffix );
  produces <std::vector<double> > ( Prefix + "JetIDFRBX"  + Suffix );
  produces <std::vector<double> > ( Prefix + "JetIDFSubDet1"  + Suffix );
  produces <std::vector<double> > ( Prefix + "JetIDFSubDet2"  + Suffix );
  produces <std::vector<double> > ( Prefix + "JetIDFSubDet3"  + Suffix );
  produces <std::vector<double> > ( Prefix + "JetIDFSubDet4"  + Suffix );
  produces <std::vector<double> > ( Prefix + "JetIDResEMF"  + Suffix );
  produces <std::vector<int> > ( Prefix + "JetIDN90Hits"  + Suffix );
  produces <std::vector<int> > ( Prefix + "NECALTowers"  + Suffix );
  produces <std::vector<int> > ( Prefix + "NHCALTowers"  + Suffix );

}

template< typename T >
void SusyCAF_Jet<T>::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  edm::Handle<std::vector<T> > jetcollection;
  iEvent.getByLabel(inputTag, jetcollection);
  //
  edm::Handle<reco::VertexCollection> vertices;   
  iEvent.getByLabel(primaryVertexTag, vertices);
  //
  produceTemplate(iEvent, iSetup, jetcollection, vertices);
}

// produce method in case of RECO data
template< typename T >
void SusyCAF_Jet<T>::
produceTemplate(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<reco::CaloJet> >& collection, edm::Handle<reco::VertexCollection>& vertices) {
  produceRECO(iEvent, iSetup, collection);
}

// produce method in case of PAT data
template< typename T >
void SusyCAF_Jet<T>::
produceTemplate(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<pat::Jet> >& collection, edm::Handle<reco::VertexCollection>& vertices) {
  produceRECO(iEvent, iSetup, collection);
  producePAT(iEvent, iSetup, collection, vertices);
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


  if (collection.isValid()){
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
  }

  iEvent.put( p4,  Prefix + "CorrectedP4"  + Suffix );
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
  iEvent.put( n60,  Prefix + "N60Towers"  + Suffix ); 
  iEvent.put( n90,  Prefix + "N90Towers"  + Suffix ); 

}


// extra information stored for PAT data
template< typename T >
void SusyCAF_Jet<T>::
producePAT(edm::Event& iEvent, const edm::EventSetup& iSetup, edm::Handle<std::vector<T> >& collection, edm::Handle<reco::VertexCollection>& vertices) {

  std::auto_ptr<std::vector<double> >  corrfactor   ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<int> >  nAssoTracksEverything  ( new std::vector<int>()  ) ;
  std::auto_ptr<std::vector<int> >  nAssoTracksAll  ( new std::vector<int>()  ) ;
  std::auto_ptr<std::vector<int> >  nAssoTracksLoose  ( new std::vector<int>()  ) ;
  std::auto_ptr<std::vector<int> >  nAssoTracksTight  ( new std::vector<int>()  ) ;
  std::auto_ptr<std::vector<int> >  nAssoTracksHighPurity  ( new std::vector<int>()  ) ;
  std::auto_ptr<std::vector<int> >  nAssoTracksConfirmed  ( new std::vector<int>()  ) ;
  std::auto_ptr<std::vector<int> >  nAssoTracksGoodIterative  ( new std::vector<int>()  ) ;
  std::auto_ptr<Vector>  jetMPTwithEverything  ( new Vector ) ;
  std::auto_ptr<Vector>  jetMPTwithAllTracks  ( new Vector  ) ;
  std::auto_ptr<Vector>  jetMPTwithLooseTracks  ( new Vector ) ;
  std::auto_ptr<Vector>  jetMPTwithTightTracks  ( new Vector ) ;
  std::auto_ptr<Vector>  jetMPTwithHighPurityTracks  ( new Vector ) ;
  std::auto_ptr<Vector>  jetMPTwithConfirmedTracks  ( new Vector ) ;
  std::auto_ptr<Vector>  jetMPTwithGoodIterativeTracks  ( new Vector ) ;
  std::auto_ptr<std::vector<double> >  fHPD  ( new std::vector<double>() ) ;
  std::auto_ptr<std::vector<double> >  fRBX  ( new std::vector<double>() ) ;
  std::auto_ptr<std::vector<double> >  fSubDet1  ( new std::vector<double>() ) ;
  std::auto_ptr<std::vector<double> >  fSubDet2  ( new std::vector<double>() ) ;
  std::auto_ptr<std::vector<double> >  fSubDet3  ( new std::vector<double>() ) ;
  std::auto_ptr<std::vector<double> >  fSubDet4  ( new std::vector<double>() ) ;
  std::auto_ptr<std::vector<double> >  resEMF  ( new std::vector<double>()  ) ;
  std::auto_ptr<std::vector<int> >  n90Hits  ( new std::vector<int>()  ) ;
  std::auto_ptr<std::vector<int> >  NECALTowers  ( new std::vector<int>()  ) ;
  std::auto_ptr<std::vector<int> >  NHCALTowers  ( new std::vector<int>()  ) ;

  const reco::Vertex PrimaryVertex = vertices->front();
  if (collection.isValid()){
    for(typename std::vector<T>::const_iterator it = collection->begin(); it != collection->end(); ++it) {
      //set to zero the vectorial sum of associated tracks momenta
      jetMPTwithEverything->SetCoordinates(0., 0., 0.);
      jetMPTwithAllTracks->SetCoordinates(0., 0., 0.);
      jetMPTwithLooseTracks->SetCoordinates(0., 0., 0.);
      jetMPTwithTightTracks->SetCoordinates(0., 0., 0.);
      jetMPTwithHighPurityTracks->SetCoordinates(0., 0., 0.);
      jetMPTwithConfirmedTracks->SetCoordinates(0., 0., 0.);
      jetMPTwithGoodIterativeTracks->SetCoordinates(0., 0., 0.);
      //
      const pat::Jet pJunc = (static_cast<const pat::Jet*>(&(*it)))->correctedJet("RAW"); 
      corrfactor->push_back(it->energy()/pJunc.energy());
      nAssoTracksEverything->push_back(it->associatedTracks().size());
      int nATAll=0;
      int nATLoose=0;
      int nATTight=0;
      int nATHighPurity=0;
      int nATConfirmed=0;
      int nATGoodIterative=0;
      for (reco::TrackRefVector::iterator trk = it->associatedTracks().begin(); trk != it->associatedTracks().end(); ++trk) {
	 *jetMPTwithEverything += (*trk)->momentum();
	//preselection cuts
	if((*trk)->pt()>minPttrk && (*trk)->pt()<maxPttrk && fabs((*trk)->dxy(PrimaryVertex.position()))<maxD0trk && (*trk)->chi2()<maxChi2trk){
	  //undefined
	  if((*trk)->quality(reco::Track::undefQuality)){
	    nATAll++;
	    *jetMPTwithAllTracks += (*trk)->momentum();
	  }
	  //loose
	  if((*trk)->quality(reco::Track::loose)) {
	    nATLoose++;
	    *jetMPTwithLooseTracks += (*trk)->momentum();
	  }
	  //tight
	  if((*trk)->quality(reco::Track::tight)) {
	    nATTight++;
	    *jetMPTwithTightTracks += (*trk)->momentum();
	  }
	  //highpurity
	  if((*trk)->quality(reco::Track::highPurity)) {
	    nATHighPurity++;
	    *jetMPTwithHighPurityTracks+= (*trk)->momentum();
	  }
	  //confirmed
	  if((*trk)->quality(reco::Track::confirmed)) {
	    nATConfirmed++;
	    *jetMPTwithConfirmedTracks+= (*trk)->momentum();
	  }
	  //gooditerative
	  if((*trk)->quality(reco::Track::goodIterative)) {
	    nATGoodIterative++;
	    *jetMPTwithGoodIterativeTracks+= (*trk)->momentum();
	  }
	}
      }
      
      nAssoTracksAll->push_back(nATAll);
      nAssoTracksLoose->push_back(nATLoose);
      nAssoTracksTight->push_back(nATTight);
      nAssoTracksHighPurity->push_back(nATHighPurity);
      nAssoTracksConfirmed->push_back(nATConfirmed);
      nAssoTracksGoodIterative->push_back(nATGoodIterative);
      fHPD->push_back(it->jetID().fHPD);
      fRBX->push_back(it->jetID().fRBX);
      fSubDet1->push_back(it->jetID().fSubDetector1);
      fSubDet2->push_back(it->jetID().fSubDetector2);
      fSubDet3->push_back(it->jetID().fSubDetector3);
      fSubDet4->push_back(it->jetID().fSubDetector4);
      resEMF->push_back(it->jetID().restrictedEMF);
      n90Hits->push_back(it->jetID().n90Hits);
      NECALTowers->push_back(it->jetID().nECALTowers);
      NHCALTowers->push_back(it->jetID().nHCALTowers);  

      //std::strbitset    passMinimalCuts, passLooseCuts, passTightCuts;
      //minimalJetID.print(std::cout);
      //looseJetID  .print(std::cout);
      //tightJetID  .print(std::cout);
      //bool              passMinimal = minimalJetID(*it, passMinimalCuts);
      //bool              passLoose   = looseJetID  (*it, passLooseCuts  );
      //bool              passTight   = tightJetID  (*it, passTightCuts  );
      //std::cout << " Minimal ID : " << (passMinimal ? "yes" : "no") << std::endl;  passMinimalCuts.print(std::cout);
      //std::cout << " Loose ID   : " << (passLoose   ? "yes" : "no") << std::endl;  passLooseCuts  .print(std::cout);
      //std::cout << " Tight ID   : " << (passTight   ? "yes" : "no") << std::endl;  passTightCuts  .print(std::cout);
    }
  }

  iEvent.put( corrfactor,  Prefix + "CorrFactor"  + Suffix );
  iEvent.put( nAssoTracksEverything,  Prefix + "NAssoTracksEverything"  + Suffix );
  iEvent.put( nAssoTracksAll,  Prefix + "NAssoTracksAll"  + Suffix );
  iEvent.put( nAssoTracksLoose,  Prefix + "NAssoTracksLoose"  + Suffix );
  iEvent.put( nAssoTracksTight,  Prefix + "NAssoTracksTight"  + Suffix );
  iEvent.put( nAssoTracksHighPurity,  Prefix + "NAssoTracksHighPurity"  + Suffix );
  iEvent.put( nAssoTracksConfirmed,  Prefix + "NAssoTracksConfirmed"  + Suffix );
  iEvent.put( nAssoTracksGoodIterative,  Prefix + "NAssoTracksGoodIterative"  + Suffix );
  iEvent.put( jetMPTwithEverything,  Prefix + "MPTwithEverything"  + Suffix );
  iEvent.put( jetMPTwithAllTracks,  Prefix + "MPTwithAllTracks"  + Suffix );
  iEvent.put( jetMPTwithLooseTracks,  Prefix + "MPTwithLooseTracks"  + Suffix );
  iEvent.put( jetMPTwithTightTracks,  Prefix + "MPTwithTightTracks"  + Suffix );
  iEvent.put( jetMPTwithHighPurityTracks,  Prefix + "MPTwithHighPurityTracks"  + Suffix );
  iEvent.put( jetMPTwithConfirmedTracks,  Prefix + "MPTwithConfirmedTracks"  + Suffix );
  iEvent.put( jetMPTwithGoodIterativeTracks,  Prefix + "MPTwithGoodIterativeTracks"  + Suffix );
  iEvent.put( fHPD,  Prefix + "JetIDFHPD"  + Suffix );
  iEvent.put( fRBX,  Prefix + "JetIDFRBX"  + Suffix );
  iEvent.put( fSubDet1,  Prefix + "JetIDFSubDet1"  + Suffix );
  iEvent.put( fSubDet2,  Prefix + "JetIDFSubDet2"  + Suffix );
  iEvent.put( fSubDet3,  Prefix + "JetIDFSubDet3"  + Suffix );
  iEvent.put( fSubDet4,  Prefix + "JetIDFSubDet4"  + Suffix );
  iEvent.put( resEMF,  Prefix + "JetIDResEMF"  + Suffix );
  iEvent.put( n90Hits,  Prefix + "JetIDN90Hits"  + Suffix );
  iEvent.put( NECALTowers,  Prefix + "NECALTowers"  + Suffix );
  iEvent.put( NHCALTowers,  Prefix + "NHCALTowers"  + Suffix );

}

#endif
