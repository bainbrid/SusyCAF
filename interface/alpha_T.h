#ifndef ALPHA_T_H
#define ALPHA_T_H

#include <cmath>
#include <vector>
#include <numeric>
#include <Math/LorentzVector.h>

namespace alphaT {
  typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzV;
  
  std::vector<double> deltaSumPt_permutations(std::vector<LorentzV>& p4s) 
  {
    std::vector<std::vector<double> > ht( 1<<(p4s.size()-1) , std::vector<double>( 2, 0.) );
    for(unsigned i=0; i < ht.size(); i++) {
      for(unsigned j=0; j < p4s.size(); j++) {
	ht [i] [(i/(1<<j))%2] += p4s[j].pt();
      }
    }
    std::vector<double> deltaHT;  for(unsigned i=0; i<ht.size(); i++) deltaHT.push_back(fabs(ht[i][0]-ht[i][1]));
    return deltaHT;
  }
  
  double alpha_T(std::vector<LorentzV>& p4s) 
  {
    if(p4s.size()<2) return 0;
    
    std::vector<double> pTs; for(unsigned i=0; i<p4s.size(); i++) pTs.push_back(p4s[i].pt());
    for(unsigned i=0; i<p4s.size(); i++) pTs.push_back(p4s[i].pt());
    const std::vector<double> DHTper( deltaSumPt_permutations(p4s) );
    
    const double mDHT = *(std::min_element( DHTper.begin(), DHTper.end() ));
    const double sumPT = accumulate( pTs.begin(), pTs.end(), double(0) );
    const LorentzV sumP4 = accumulate( p4s.begin(), p4s.end(), LorentzV() );
    
    return 0.5 * ( sumPT - mDHT ) / sqrt( sumPT*sumPT - sumP4.perp2() );
  }
}

double alpha_T(std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >& p4s) {return alphaT::alpha_T(p4s);}

#endif
