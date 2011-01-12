#include "SUSYBSMAnalysis/SusyCAF/interface/ProductReducer.h"
#include "SUSYBSMAnalysis/SusyCAF/interface/fTypes.h"

#include "FWCore/Framework/interface/ConstProductRegistry.h" 
#include "FWCore/Framework/interface/GroupSelector.h"
#include "FWCore/Framework/interface/GroupSelectorRules.h"
#include "DataFormats/Provenance/interface/Selections.h"

#include "boost/foreach.hpp"

void ProductReducer::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  BOOST_FOREACH( Reducer* reducer, reducers)
    reducer->reduce(iEvent);
}

template<class A, class B> 
void ProductReducer::registerReducer(edm::BranchDescription const * desc) {
  const std::string name = desc->productInstanceName()==""?desc->moduleLabel():desc->productInstanceName();
  produces<B>(name);
  typedef typename boost::mpl::if_<my_black_magic::has_iterator<A>, 
    VectorTypedReducer<A,B>, 
    UnitTypedReducer<A,B> >::type   tr_type;
  reducers.push_back(new tr_type(desc));
}

template <class A, class B>
void ProductReducer::TypedReducer<A,B>::
reduce(edm::Event& iEvent) {
  edm::Handle<A> handle_;
  iEvent.getByLabel(ml, pin, handle_);
  iEvent.put( convert(*handle_), name);
}

template <class A, class B>
std::auto_ptr<B> ProductReducer::UnitTypedReducer<A,B>::
static_convert(const A& a) { return std::auto_ptr<B>(new B(a));}

template <class A, class B>
std::auto_ptr<B> ProductReducer::VectorTypedReducer<A,B>::
convert(const A& a) {
  std::auto_ptr<B> b(new B());
  for( typename A::const_iterator it(a.begin()), end(a.end()); it!=end; ++it) {
    b->push_back(*((UnitTypedReducer<typename A::value_type, typename B::value_type>::static_convert(*it)).release()));
  }
  return b;
}

template <>
std::auto_ptr<fTypes::fPolarLorentzV> ProductReducer::UnitTypedReducer<fTypes::dXYZLorentzV,fTypes::fPolarLorentzV>::
static_convert(const fTypes::dXYZLorentzV& a) {
  return std::auto_ptr<fTypes::fPolarLorentzV>(new fTypes::fPolarLorentzV(a.Pt(), a.Eta(), a.Phi(), a.M()));
}

template<>
std::auto_ptr<fTypes::fPolarLorentzV> ProductReducer::UnitTypedReducer<fTypes::dPolarLorentzV,fTypes::fPolarLorentzV>::
static_convert(const fTypes::dPolarLorentzV& a) {
  return std::auto_ptr<fTypes::fPolarLorentzV>(new fTypes::fPolarLorentzV(a.Pt(), a.Eta(), a.Phi(), a.M()));
}

  
ProductReducer::ProductReducer(const edm::ParameterSet& conf) : pset(conf) {

  edm::Service<edm::ConstProductRegistry> reg;
  edm::Selections allBranches = reg->allBranchDescriptions();
  edm::GroupSelector groupSelector_;
  groupSelector_.initialize(edm::GroupSelectorRules(pset, "selectionCommands", "ProductReducer"), allBranches);
  
  std::set<std::string> branchnames;
  BOOST_FOREACH( const edm::Selections::value_type& selection, allBranches) {
    if(groupSelector_.selected(*selection)) {

      //Check for duplicate branch names
      const std::string name = selection->productInstanceName()==""? selection->moduleLabel() : selection->productInstanceName();
      if (branchnames.find(name) != branchnames.end() )
	throw edm::Exception(edm::errors::Configuration)
	  << "More than one branch named: " << name << std::endl
	  << "Exception thrown from ProductReducer::beginJob" << std::endl;
      else 
	branchnames.insert(name);
      
      switch(fTypes::dict.find(selection->friendlyClassName())->second) {
      case fTypes::DOUBLE :  registerReducer<double,float>(selection); break;
      case fTypes::LONG   :  registerReducer<long,int>(selection); break;
      case fTypes::DOUBLE_V: registerReducer<std::vector<double>,std::vector<float> >(selection); break;
      case fTypes::BOOL_V:   registerReducer<std::vector<bool>, std::vector<int> >(selection); break;
      case fTypes::LORENTZV: registerReducer<fTypes::dXYZLorentzV,fTypes::fPolarLorentzV>(selection); break;
      case fTypes::LORENTZV_V: registerReducer<std::vector<fTypes::dXYZLorentzV>,std::vector<fTypes::fPolarLorentzV> >(selection); break; 
      case fTypes::LORENTZV2: registerReducer<fTypes::dPolarLorentzV,fTypes::fPolarLorentzV>(selection); break;
      case fTypes::LORENTZV2_V: registerReducer<std::vector<fTypes::dPolarLorentzV>,std::vector<fTypes::fPolarLorentzV> >(selection); break; 

      case fTypes::BOOL: case fTypes::SHORT: case fTypes::SHORT_V: case fTypes::U_SHORT: case fTypes::U_SHORT_V:
      case fTypes::INT: case fTypes::INT_V: case fTypes::U_INT: case fTypes::U_INT_V: case fTypes::FLOAT: case fTypes::FLOAT_V:
      case fTypes::U_LONG: case fTypes::U_LONG_V: case fTypes::POINT: case fTypes::VECTOR:
      case fTypes::POINT_V: case fTypes::VECTOR_V:
      case fTypes::STRING: case fTypes::STRING_BOOL_M: case fTypes::STRING_INT_M: case fTypes::STRING_STRING_M:
      default : 
	throw edm::Exception(edm::errors::Configuration) << "ProductReducer does not handle leaves of type " << selection->className();
      }
    }
  }
}
