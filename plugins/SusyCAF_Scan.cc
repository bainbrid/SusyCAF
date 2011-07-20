#include "SUSYBSMAnalysis/SusyCAF/interface/SusyCAF_Scan.h"
#include "FWCore/Framework/interface/Event.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "boost/lexical_cast.hpp"
#include "boost/foreach.hpp"

SusyCAF_Scan::SusyCAF_Scan(const edm::ParameterSet& cfg) :
  inputTag(cfg.getParameter<edm::InputTag>("InputTag")),
  Prefix  (cfg.getParameter<std::string>  ("Prefix"  )),
  Suffix  (cfg.getParameter<std::string>  ("Suffix"  )),
  scanFormat(cfg.getParameter<std::string>("ScanFormat")),
  scanPars(cfg.getParameter<std::vector<std::string> >("ScanParameters")),
  debug(cfg.getUntrackedParameter<bool>("Debug",false))
{
  BOOST_FOREACH(const std::string& par, scanPars) 
    produces<double>( Prefix + par + Suffix );
  produces <bool>   ( Prefix + "HandleValid" + Suffix );
}

void SusyCAF_Scan::
produce(edm::Event& event, const edm::EventSetup&) {

  boost::smatch matches;
  edm::Handle<LHEEventProduct> lhe;
  event.getByLabel(inputTag, lhe);

  if(lhe.isValid()) {
    const std::vector<std::string> comments(lhe->comments_begin(),lhe->comments_end());
    BOOST_FOREACH(const std::string& comment, comments) 
      if (boost::regex_match(comment, matches, scanFormat)) break;
  }
  
  bool valid = matches.size() && matches[0].matched;
  if(valid && debug) std::cout << matches[0].str() << std::endl;
  event.put( std::auto_ptr<bool>(new bool(valid)),  Prefix + "HandleValid" + Suffix );
  for(unsigned i=0; i<scanPars.size(); ++i) 
    event.put(std::auto_ptr<double>(new double(!valid ? 0.0 : convert(matches[i+1].str()))),  Prefix + scanPars[i] + Suffix );
}

double SusyCAF_Scan::convert(std::string s) {
  if(s[0]=='m') s[0] = '-';
  return boost::lexical_cast<double>(s);
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(SusyCAF_Scan);
