#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_HcalNoiseRBX.h"
#include "FWCore/Framework/interface/Event.h"

SusyCAF_HcalNoiseRBX::SusyCAF_HcalNoiseRBX(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
  Prefix(iConfig.getParameter<std::string>("Prefix")),
  Suffix(iConfig.getParameter<std::string>("Suffix")),
  outputHpdVariables(iConfig.getParameter<bool>("OutputHpdVariables")),
  energyThresholdForRecHitCount(iConfig.getParameter<double>("EnergyThresholdForRecHitCount")),
  energyThresholdForRecHitTimeRbx(iConfig.getParameter<double>("EnergyThresholdForRecHitTimeRbx")),
  energyThresholdForRecHitTimeHpd(iConfig.getParameter<double>("EnergyThresholdForRecHitTimeHpd"))
{
  //descriptions of variables here: http://cmslxr.fnal.gov/lxr/source/DataFormats/METReco/interface/HcalNoiseRBX.h
  produces < bool >                ( Prefix + "handleValid"          + Suffix);
  produces < std::vector<int>    > ( Prefix + "idnumber"             + Suffix);
  produces < std::vector<float>  > ( Prefix + "allChargeTotal"       + Suffix);
  produces < std::vector<float>  > ( Prefix + "allChargeHighest2TS"  + Suffix);
  produces < std::vector<float>  > ( Prefix + "allChargeHighest3TS"  + Suffix);
  produces < std::vector<int>    > ( Prefix + "totalZeros"           + Suffix);
  produces < std::vector<int>    > ( Prefix + "maxZeros"             + Suffix);
  produces < std::vector<double> > ( Prefix + "recHitEnergy"         + Suffix);
  produces < std::vector<double> > ( Prefix + "minRecHitTime"        + Suffix);
  produces < std::vector<double> > ( Prefix + "maxRecHitTime"        + Suffix);
  produces < std::vector<int>    > ( Prefix + "numRecHits"           + Suffix);
  produces < std::vector<double> > ( Prefix + "caloTowerHadE"        + Suffix);
  produces < std::vector<double> > ( Prefix + "caloTowerEmE"         + Suffix);
  produces < std::vector<double> > ( Prefix + "caloTowerTotalE"      + Suffix);
  produces < std::vector<double> > ( Prefix + "caloTowerEmFraction"  + Suffix);

  if (outputHpdVariables) {
    produces < bool >              ( Prefix + "hpdVariablesValid"    + Suffix);

    for (unsigned int iHpd=0;iHpd<nHpdsPerHbheRbx;iHpd++) {
      std::stringstream tempss;
      tempss << iHpd;
      std::string hpdString=tempss.str();
      
      produces < std::vector<int>    > ( Prefix + "hpd"+hpdString+"idnumber"              + Suffix );
      produces < std::vector<float>  > ( Prefix + "hpd"+hpdString+"bigChargeTotal"        + Suffix );
      produces < std::vector<float>  > ( Prefix + "hpd"+hpdString+"bigChargeHighest2TS"   + Suffix );
      produces < std::vector<float>  > ( Prefix + "hpd"+hpdString+"bigChargeHighest3TS"   + Suffix );

      produces < std::vector<float>  > ( Prefix + "hpd"+hpdString+"big5ChargeTotal"       + Suffix );
      produces < std::vector<float>  > ( Prefix + "hpd"+hpdString+"big5ChargeHighest2TS"  + Suffix );
      produces < std::vector<float>  > ( Prefix + "hpd"+hpdString+"big5ChargeHighest3TS"  + Suffix );

      produces < std::vector<int>    > ( Prefix + "hpd"+hpdString+"totalZeros"            + Suffix );
      produces < std::vector<int>    > ( Prefix + "hpd"+hpdString+"maxZeros"              + Suffix );

      produces < std::vector<float>  > ( Prefix + "hpd"+hpdString+"recHitEnergy"          + Suffix );

      produces < std::vector<float>  > ( Prefix + "hpd"+hpdString+"minRecHitTime"         + Suffix );
      produces < std::vector<float>  > ( Prefix + "hpd"+hpdString+"maxRecHitTime"         + Suffix );

      produces < std::vector<int>    > ( Prefix + "hpd"+hpdString+"numRecHits"            + Suffix );

      produces < std::vector<double> > ( Prefix + "hpd"+hpdString+"caloTowerHadE"         + Suffix );
      produces < std::vector<double> > ( Prefix + "hpd"+hpdString+"caloTowerEmE"          + Suffix );
      produces < std::vector<double> > ( Prefix + "hpd"+hpdString+"caloTowerTotalE"       + Suffix );
      produces < std::vector<double> > ( Prefix + "hpd"+hpdString+"caloTowerEmFraction"   + Suffix );
    }
  }

}

void SusyCAF_HcalNoiseRBX::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {

  //declare RBX variables
  std::auto_ptr<bool>                  handleValid          ( new bool() );
  std::auto_ptr< std::vector<int>    > idnumber             ( new std::vector<int>   () );
  std::auto_ptr< std::vector<float>  > allChargeTotal	    ( new std::vector<float> () );
  std::auto_ptr< std::vector<float>  > allChargeHighest2TS  ( new std::vector<float> () );
  std::auto_ptr< std::vector<float>  > allChargeHighest3TS  ( new std::vector<float> () );
  std::auto_ptr< std::vector<int>    > totalZeros	    ( new std::vector<int>   () );
  std::auto_ptr< std::vector<int>    > maxZeros		    ( new std::vector<int>   () );
  std::auto_ptr< std::vector<double> > recHitEnergy	    ( new std::vector<double>() );
  std::auto_ptr< std::vector<double> > minRecHitTime	    ( new std::vector<double>() );
  std::auto_ptr< std::vector<double> > maxRecHitTime	    ( new std::vector<double>() );
  std::auto_ptr< std::vector<int>    > numRecHits	    ( new std::vector<int>   () );
  std::auto_ptr< std::vector<double> > caloTowerHadE	    ( new std::vector<double>() );
  std::auto_ptr< std::vector<double> > caloTowerEmE	    ( new std::vector<double>() );
  std::auto_ptr< std::vector<double> > caloTowerTotalE	    ( new std::vector<double>() );
  std::auto_ptr< std::vector<double> > caloTowerEmFraction  ( new std::vector<double>() );

  //assign RBX variables
  edm::Handle<reco::HcalNoiseRBXCollection> hcalNoiseRBX;
  iEvent.getByLabel("hcalnoise", hcalNoiseRBX);

  *handleValid.get()=hcalNoiseRBX.isValid();
  if (*handleValid) {
    for(reco::HcalNoiseRBXCollection::const_iterator it=hcalNoiseRBX->begin(); it!=hcalNoiseRBX->end(); ++it) {

      idnumber->push_back(it->idnumber());
      allChargeTotal->push_back(it->allChargeTotal());
      allChargeHighest2TS->push_back(it->allChargeHighest2TS());
      allChargeHighest3TS->push_back(it->allChargeHighest3TS());
      totalZeros->push_back(it->totalZeros());
      maxZeros->push_back(it->maxZeros());
      recHitEnergy->push_back(it->recHitEnergy(energyThresholdForRecHitCount));
      minRecHitTime->push_back(it->minRecHitTime(energyThresholdForRecHitTimeRbx));
      maxRecHitTime->push_back(it->maxRecHitTime(energyThresholdForRecHitTimeRbx));
      numRecHits->push_back(it->numRecHits(energyThresholdForRecHitCount));
      caloTowerHadE->push_back(it->caloTowerHadE());
      caloTowerEmE->push_back(it->caloTowerEmE());
      caloTowerTotalE->push_back(it->caloTowerTotalE());
      caloTowerEmFraction->push_back(it->caloTowerEmFraction());
    }

    //HPD variables here
    if (outputHpdVariables) doHpdVariables(iEvent,hcalNoiseRBX);
  }

  //put RBX variables
  iEvent.put( handleValid         , Prefix + "handleValid"          + Suffix );
  iEvent.put( idnumber            , Prefix + "idnumber"             + Suffix );
  iEvent.put( allChargeTotal      , Prefix + "allChargeTotal"       + Suffix );
  iEvent.put( allChargeHighest2TS , Prefix + "allChargeHighest2TS"  + Suffix );
  iEvent.put( allChargeHighest3TS , Prefix + "allChargeHighest3TS"  + Suffix );
  iEvent.put( totalZeros          , Prefix + "totalZeros"           + Suffix );
  iEvent.put( maxZeros            , Prefix + "maxZeros"             + Suffix );
  iEvent.put( recHitEnergy        , Prefix + "recHitEnergy"         + Suffix );
  iEvent.put( minRecHitTime       , Prefix + "minRecHitTime"        + Suffix );
  iEvent.put( maxRecHitTime       , Prefix + "maxRecHitTime"        + Suffix );
  iEvent.put( numRecHits          , Prefix + "numRecHits"           + Suffix );
  iEvent.put( caloTowerHadE       , Prefix + "caloTowerHadE"        + Suffix );
  iEvent.put( caloTowerEmE        , Prefix + "caloTowerEmE"         + Suffix );
  iEvent.put( caloTowerTotalE     , Prefix + "caloTowerTotalE"      + Suffix );
  iEvent.put( caloTowerEmFraction , Prefix + "caloTowerEmFraction"  + Suffix );
}

void SusyCAF_HcalNoiseRBX::
doHpdVariables(edm::Event& iEvent, edm::Handle<reco::HcalNoiseRBXCollection> hcalNoiseRBX) {

  std::auto_ptr<bool> hpdVariablesValid ( new bool(true) );

  //declare, assign, put HPD variables
  for(unsigned int iHpd=0;iHpd<nHpdsPerHbheRbx;++iHpd) {
    std::auto_ptr<std::vector <int>    >  hpdidnumber              ( new std::vector<int>    () );
    std::auto_ptr<std::vector <float>  >  hpdbigChargeTotal        ( new std::vector<float>  () );
    std::auto_ptr<std::vector <float>  >  hpdbigChargeHighest2TS   ( new std::vector<float>  () );
    std::auto_ptr<std::vector <float>  >  hpdbigChargeHighest3TS   ( new std::vector<float>  () );
    std::auto_ptr<std::vector <float>  >  hpdbig5ChargeTotal       ( new std::vector<float>  () );
    std::auto_ptr<std::vector <float>  >  hpdbig5ChargeHighest2TS  ( new std::vector<float>  () );
    std::auto_ptr<std::vector <float>  >  hpdbig5ChargeHighest3TS  ( new std::vector<float>  () );
    std::auto_ptr<std::vector <int>    >  hpdtotalZeros            ( new std::vector<int>    () );
    std::auto_ptr<std::vector <int>    >  hpdmaxZeros              ( new std::vector<int>    () );
    std::auto_ptr<std::vector <float>  >  hpdrecHitEnergy          ( new std::vector<float>  () );
    std::auto_ptr<std::vector <float>  >  hpdminRecHitTime         ( new std::vector<float>  () );
    std::auto_ptr<std::vector <float>  >  hpdmaxRecHitTime         ( new std::vector<float>  () );
    std::auto_ptr<std::vector <int>    >  hpdnumRecHits            ( new std::vector<int>    () );
    std::auto_ptr<std::vector <double> >  hpdcaloTowerHadE         ( new std::vector<double> () );
    std::auto_ptr<std::vector <double> >  hpdcaloTowerEmE          ( new std::vector<double> () );
    std::auto_ptr<std::vector <double> >  hpdcaloTowerTotalE       ( new std::vector<double> () );
    std::auto_ptr<std::vector <double> >  hpdcaloTowerEmFraction   ( new std::vector<double> () );
    
    for(reco::HcalNoiseRBXCollection::const_iterator it=hcalNoiseRBX->begin(); it!=hcalNoiseRBX->end(); ++it) {
      //range check
      if (iHpd>=it->HPDs().size()) {
	*hpdVariablesValid.get()=false;
	continue;
      }

      reco::HcalNoiseHPD hpd=it->HPDs().at(iHpd);

      hpdidnumber              ->push_back( hpd.idnumber()                                     );
      hpdbigChargeTotal        ->push_back( hpd.bigChargeTotal()                               );
      hpdbigChargeHighest2TS   ->push_back( hpd.bigChargeHighest2TS()                          );
      hpdbigChargeHighest3TS   ->push_back( hpd.bigChargeHighest3TS()                          );
      hpdbig5ChargeTotal       ->push_back( hpd.big5ChargeTotal()                              );
      hpdbig5ChargeHighest2TS  ->push_back( hpd.big5ChargeHighest2TS()                         );
      hpdbig5ChargeHighest3TS  ->push_back( hpd.big5ChargeHighest3TS()                         );
      hpdtotalZeros            ->push_back( hpd.totalZeros()                                   );
      hpdmaxZeros              ->push_back( hpd.maxZeros()                                     );
      hpdrecHitEnergy          ->push_back( hpd.recHitEnergy(energyThresholdForRecHitCount)    );
      hpdminRecHitTime         ->push_back( hpd.minRecHitTime(energyThresholdForRecHitTimeHpd) );
      hpdmaxRecHitTime         ->push_back( hpd.maxRecHitTime(energyThresholdForRecHitTimeHpd) );
      hpdnumRecHits            ->push_back( hpd.numRecHits(energyThresholdForRecHitCount)      );
      hpdcaloTowerHadE         ->push_back( hpd.caloTowerHadE()                                );
      hpdcaloTowerEmE          ->push_back( hpd.caloTowerEmE()                                 );
      hpdcaloTowerTotalE       ->push_back( hpd.caloTowerTotalE()                              );
      hpdcaloTowerEmFraction   ->push_back( hpd.caloTowerEmFraction()                          );
    } //end loop over RBXes
    
    std::stringstream tempss;
    tempss << iHpd;
    std::string hpdString=tempss.str();

    iEvent.put( hpdidnumber              , Prefix + "hpd"+hpdString+"idnumber"              + Suffix );
    iEvent.put( hpdbigChargeTotal        , Prefix + "hpd"+hpdString+"bigChargeTotal"        + Suffix );
    iEvent.put( hpdbigChargeHighest2TS   , Prefix + "hpd"+hpdString+"bigChargeHighest2TS"   + Suffix );
    iEvent.put( hpdbigChargeHighest3TS   , Prefix + "hpd"+hpdString+"bigChargeHighest3TS"   + Suffix );
    iEvent.put( hpdbig5ChargeTotal       , Prefix + "hpd"+hpdString+"big5ChargeTotal"       + Suffix );
    iEvent.put( hpdbig5ChargeHighest2TS  , Prefix + "hpd"+hpdString+"big5ChargeHighest2TS"  + Suffix );
    iEvent.put( hpdbig5ChargeHighest3TS  , Prefix + "hpd"+hpdString+"big5ChargeHighest3TS"  + Suffix );
    iEvent.put( hpdtotalZeros            , Prefix + "hpd"+hpdString+"totalZeros"            + Suffix );
    iEvent.put( hpdmaxZeros              , Prefix + "hpd"+hpdString+"maxZeros"              + Suffix );
    iEvent.put( hpdrecHitEnergy          , Prefix + "hpd"+hpdString+"recHitEnergy"          + Suffix );
    iEvent.put( hpdminRecHitTime         , Prefix + "hpd"+hpdString+"minRecHitTime"         + Suffix );
    iEvent.put( hpdmaxRecHitTime         , Prefix + "hpd"+hpdString+"maxRecHitTime"         + Suffix );
    iEvent.put( hpdnumRecHits            , Prefix + "hpd"+hpdString+"numRecHits"            + Suffix );
    iEvent.put( hpdcaloTowerHadE         , Prefix + "hpd"+hpdString+"caloTowerHadE"         + Suffix );
    iEvent.put( hpdcaloTowerEmE          , Prefix + "hpd"+hpdString+"caloTowerEmE"          + Suffix );
    iEvent.put( hpdcaloTowerTotalE       , Prefix + "hpd"+hpdString+"caloTowerTotalE"       + Suffix );
    iEvent.put( hpdcaloTowerEmFraction   , Prefix + "hpd"+hpdString+"caloTowerEmFraction"   + Suffix );

  } //end loop over HPDs

  iEvent.put( hpdVariablesValid          , Prefix + "hpdVariablesValid"                     + Suffix );

}
