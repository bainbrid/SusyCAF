#ifndef Product_Reducer_h
#define Product_Reducer_h

/** \class ProductReducer
 * 
 *  Makes smaller versions of edm products
 *
 *  This class, which is an EDProducer, takes the same "keep" and
 *  "drop" outputCommands parameter as the PoolOutputSource, making 'reduced'
 *  versions of the selected variables, which it obtains from the EDM
 *  tree.  
 *
 *  $Date: 2011/01/11 $
 *  \author Burt Betchart - University of Rochester <burton.andrew.betchart@cern.ch>
 */

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include <string>
#include <vector>

#include "boost/mpl/if.hpp"
#include <boost/mpl/has_xxx.hpp>
#include <boost/detail/iterator.hpp>
namespace my_black_magic {
  BOOST_MPL_HAS_XXX_TRAIT_DEF(iterator)
}


class ProductReducer : public edm::EDProducer {
private:    
  virtual void produce(edm::Event&, const edm::EventSetup&);
  template<class A, class B> 
  void registerReducer(edm::BranchDescription const *);

  class Reducer { public: virtual void reduce(edm::Event&) = 0; };
  
  template <class A, class B>
  class TypedReducer : public Reducer {
  private:
    const std::string ml,pin,name;   //module label, product instance name, leaf name
  public:
    void reduce(edm::Event&);
    virtual std::auto_ptr<B> convert(const A& a) = 0;
    TypedReducer(edm::BranchDescription const* desc):  
      ml( desc->moduleLabel() ),  
      pin( desc->productInstanceName() ),
      name(pin==""?ml:pin) {}
  };
  
  template <class A, class B>
  class UnitTypedReducer : public TypedReducer<A,B> {
  public:
    virtual std::auto_ptr<B> convert(const A& a) {return static_convert(a);}
    static std::auto_ptr<B> static_convert(const A&);
    UnitTypedReducer(edm::BranchDescription const* sel) : TypedReducer<A,B>(sel) {}
  };

  template <class A, class B>
  class VectorTypedReducer : public TypedReducer<A,B> {
  public:
    virtual std::auto_ptr<B> convert(const A& a);
    VectorTypedReducer(edm::BranchDescription const* sel) : TypedReducer<A,B>(sel) {}
  };

  std::vector<Reducer*> reducers;
  edm::ParameterSet pset;

public:
  explicit ProductReducer(const edm::ParameterSet&);
  
  enum LEAFTYPE {BOOL=1,  BOOL_V,          
		 SHORT,   SHORT_V,           U_SHORT, U_SHORT_V,       
		 INT,     INT_V,             U_INT,   U_INT_V,
		 FLOAT,   FLOAT_V,           DOUBLE,  DOUBLE_V,
		 LONG,    LONG_V,	     U_LONG,  U_LONG_V,
		 LORENTZV,   LORENTZV2,   POINT,   VECTOR,
		 LORENTZV_V, LORENTZV2_V, POINT_V, VECTOR_V,
     STRING,     STRING_BOOL_M, STRING_INT_M, STRING_STRING_M };
};

#endif
