#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_HcalNoiseSummary.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/METReco/interface/HcalNoiseSummary.h"

SusyCAF_HcalNoiseSummary::SusyCAF_HcalNoiseSummary(const edm::ParameterSet& iConfig) :
  inputTag(iConfig.getParameter<edm::InputTag>("InputTag")),
  Prefix(iConfig.getParameter<std::string>("Prefix")),
  Suffix(iConfig.getParameter<std::string>("Suffix"))
{
  produces <bool>  ( Prefix + "handleValid" + Suffix);

  //descriptions of variables here: http://cmslxr.fnal.gov/lxr/source/DataFormats/METReco/interface/HcalNoiseSummary.h

  produces <bool>  ( Prefix + "passLooseNoiseFilter" + Suffix);
  produces <bool>  ( Prefix + "passTightNoiseFilter" + Suffix);
  produces <bool>  ( Prefix + "passHighLevelNoiseFilter" + Suffix);

  produces <int>   ( Prefix + "noiseFilterStatus" + Suffix);
  produces <int>   ( Prefix + "noiseType" + Suffix);

  produces <float> ( Prefix + "eventEMEnergy" + Suffix);
  produces <float> ( Prefix + "eventHadEnergy" + Suffix);
  produces <float> ( Prefix + "eventTrackEnergy" + Suffix);
  produces <float> ( Prefix + "eventEMFraction" + Suffix);
  produces <float> ( Prefix + "eventChargeFraction" + Suffix);

  produces <float> ( Prefix + "min10GeVHitTime" + Suffix);
  produces <float> ( Prefix + "max10GeVHitTime" + Suffix);
  produces <float> ( Prefix + "rms10GeVHitTime" + Suffix);
  produces <float> ( Prefix + "min25GeVHitTime" + Suffix);
  produces <float> ( Prefix + "max25GeVHitTime" + Suffix);
  produces <float> ( Prefix + "rms25GeVHitTime" + Suffix);

  produces <int>   ( Prefix + "num10GeVHits" + Suffix);
  produces <int>   ( Prefix + "num25GeVHits" + Suffix);

  produces <float> ( Prefix + "minE2TS" + Suffix);
  produces <float> ( Prefix + "minE10TS" + Suffix);
  produces <float> ( Prefix + "minE2Over10TS" + Suffix);

  produces <int>   ( Prefix + "maxZeros" + Suffix);

  produces <int>   ( Prefix + "maxHPDHits" + Suffix);
  produces <int>   ( Prefix + "maxRBXHits" + Suffix);

  produces <float> ( Prefix + "minHPDEMF" + Suffix);
  produces <float> ( Prefix + "minRBXEMF" + Suffix);

  produces <int>   ( Prefix + "numProblematicRBXs" + Suffix);
}

void SusyCAF_HcalNoiseSummary::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {

  //declare
  std::auto_ptr<bool> handleValid             ( new bool() );

  std::auto_ptr<bool>  passLooseNoiseFilter ( new bool() );
  std::auto_ptr<bool>  passTightNoiseFilter ( new bool() );
  std::auto_ptr<bool>  passHighLevelNoiseFilter ( new bool() ); 

  std::auto_ptr<int>   noiseFilterStatus ( new int() );
  std::auto_ptr<int>   noiseType ( new int() );

  std::auto_ptr<float> eventEMEnergy ( new float() );
  std::auto_ptr<float> eventHadEnergy ( new float() );
  std::auto_ptr<float> eventTrackEnergy ( new float() );
  std::auto_ptr<float> eventEMFraction ( new float() );
  std::auto_ptr<float> eventChargeFraction ( new float() );

  std::auto_ptr<float> min10GeVHitTime ( new float() );
  std::auto_ptr<float> max10GeVHitTime ( new float() );
  std::auto_ptr<float> rms10GeVHitTime ( new float() );
  std::auto_ptr<float> min25GeVHitTime ( new float() );
  std::auto_ptr<float> max25GeVHitTime ( new float() );
  std::auto_ptr<float> rms25GeVHitTime ( new float() );

  std::auto_ptr<int>   num10GeVHits ( new int() );
  std::auto_ptr<int>   num25GeVHits ( new int() );

  std::auto_ptr<float> minE2TS ( new float() );
  std::auto_ptr<float> minE10TS ( new float() );
  std::auto_ptr<float> minE2Over10TS ( new float() );

  std::auto_ptr<int>   maxZeros ( new int() );

  std::auto_ptr<int>   maxHPDHits ( new int() );
  std::auto_ptr<int>   maxRBXHits ( new int() );

  std::auto_ptr<float> minHPDEMF ( new float() );
  std::auto_ptr<float> minRBXEMF ( new float() );

  std::auto_ptr<int>   numProblematicRBXs ( new int() );

  //assign
  edm::Handle<HcalNoiseSummary> hcalNoiseSummary;
  iEvent.getByLabel(inputTag,hcalNoiseSummary);

  *handleValid.get()=hcalNoiseSummary.isValid();
  if (*handleValid) {
    *passLooseNoiseFilter.get()=hcalNoiseSummary->passLooseNoiseFilter();
    *passTightNoiseFilter.get()=hcalNoiseSummary->passTightNoiseFilter();
    *passHighLevelNoiseFilter.get()=hcalNoiseSummary->passHighLevelNoiseFilter();

    *noiseFilterStatus.get()=hcalNoiseSummary->noiseFilterStatus();
    *noiseType.get()=hcalNoiseSummary->noiseType();

    *eventEMEnergy.get()=hcalNoiseSummary->eventEMEnergy();
    *eventHadEnergy.get()=hcalNoiseSummary->eventHadEnergy();
    *eventTrackEnergy.get()=hcalNoiseSummary->eventTrackEnergy();
    *eventEMFraction.get()=hcalNoiseSummary->eventEMFraction();
    *eventChargeFraction.get()=hcalNoiseSummary->eventChargeFraction();

    *min10GeVHitTime.get()=hcalNoiseSummary->min10GeVHitTime();
    *max10GeVHitTime.get()=hcalNoiseSummary->max10GeVHitTime();
    *rms10GeVHitTime.get()=hcalNoiseSummary->rms10GeVHitTime();
    *min25GeVHitTime.get()=hcalNoiseSummary->min25GeVHitTime();
    *max25GeVHitTime.get()=hcalNoiseSummary->max25GeVHitTime();
    *rms25GeVHitTime.get()=hcalNoiseSummary->rms25GeVHitTime();

    *num10GeVHits.get()=hcalNoiseSummary->num10GeVHits();
    *num25GeVHits.get()=hcalNoiseSummary->num25GeVHits();

    *minE2TS.get()=hcalNoiseSummary->minE2TS();
    *minE10TS.get()=hcalNoiseSummary->minE10TS();
    *minE2Over10TS.get()=hcalNoiseSummary->minE2Over10TS();

    *maxZeros.get()=hcalNoiseSummary->maxZeros();

    *maxHPDHits.get()=hcalNoiseSummary->maxHPDHits();
    *maxRBXHits.get()=hcalNoiseSummary->maxRBXHits();

    *minHPDEMF.get()=hcalNoiseSummary->minHPDEMF();
    *minRBXEMF.get()=hcalNoiseSummary->minRBXEMF();

    *numProblematicRBXs.get()=hcalNoiseSummary->numProblematicRBXs();
  }

  //put
  iEvent.put( handleValid, Prefix + "handleValid" + Suffix );

  iEvent.put( passLooseNoiseFilter, Prefix + "passLooseNoiseFilter" + Suffix );
  iEvent.put( passTightNoiseFilter, Prefix + "passTightNoiseFilter" + Suffix );
  iEvent.put( passHighLevelNoiseFilter, Prefix + "passHighLevelNoiseFilter" + Suffix );
  
  iEvent.put( noiseFilterStatus, Prefix + "noiseFilterStatus" + Suffix );
  iEvent.put( noiseType, Prefix + "noiseType" + Suffix );

  iEvent.put( eventEMEnergy, Prefix + "eventEMEnergy" + Suffix );
  iEvent.put( eventHadEnergy, Prefix + "eventHadEnergy" + Suffix );
  iEvent.put( eventTrackEnergy, Prefix + "eventTrackEnergy" + Suffix );
  iEvent.put( eventEMFraction, Prefix + "eventEMFraction" + Suffix );
  iEvent.put( eventChargeFraction, Prefix + "eventChargeFraction" + Suffix );

  iEvent.put( min10GeVHitTime, Prefix + "min10GeVHitTime" + Suffix );
  iEvent.put( max10GeVHitTime, Prefix + "max10GeVHitTime" + Suffix );
  iEvent.put( rms10GeVHitTime, Prefix + "rms10GeVHitTime" + Suffix );
  iEvent.put( min25GeVHitTime, Prefix + "min25GeVHitTime" + Suffix );
  iEvent.put( max25GeVHitTime, Prefix + "max25GeVHitTime" + Suffix );
  iEvent.put( rms25GeVHitTime, Prefix + "rms25GeVHitTime" + Suffix );

  iEvent.put( num10GeVHits, Prefix + "num10GeVHits" + Suffix );
  iEvent.put( num25GeVHits, Prefix + "num25GeVHits" + Suffix );

  iEvent.put( minE2TS, Prefix + "minE2TS" + Suffix );
  iEvent.put( minE10TS, Prefix + "minE10TS" + Suffix );
  iEvent.put( minE2Over10TS, Prefix + "minE2Over10TS" + Suffix );

  iEvent.put( maxZeros, Prefix + "maxZeros" + Suffix );

  iEvent.put( maxHPDHits, Prefix + "maxHPDHits" + Suffix );
  iEvent.put( maxRBXHits, Prefix + "maxRBXHits" + Suffix );

  iEvent.put( minHPDEMF, Prefix + "minHPDEMF" + Suffix );
  iEvent.put( minRBXEMF, Prefix + "minRBXEMF" + Suffix );

  iEvent.put( numProblematicRBXs, Prefix + "numProblematicRBXs" + Suffix );
}
