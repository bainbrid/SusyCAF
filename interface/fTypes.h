#include <map>
#include <string>
#include "Math/LorentzVector.h"
#include "Math/PtEtaPhiE4D.h"
#include "Math/Vector3D.h"
#include "Math/Point3D.h"

struct fTypes {

  typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> >   dXYZLorentzV;
  typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<double> > dPolarLorentzV;
  typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<float> >  fPolarLorentzV;

  enum LEAFTYPE {BOOL=1,  BOOL_V,          
		 SHORT,   SHORT_V,           U_SHORT, U_SHORT_V,       
		 INT,     INT_V,             U_INT,   U_INT_V,
		 FLOAT,   FLOAT_V,           DOUBLE,  DOUBLE_V,
		 LONG,    LONG_V,	     U_LONG,  U_LONG_V,
		 LORENTZV,   LORENTZV2,   POINT,   VECTOR,
		 LORENTZV_V, LORENTZV2_V, POINT_V, VECTOR_V,
		 STRING,     STRING_BOOL_M, STRING_INT_M, STRING_STRING_M };

  static const std::map<std::string, LEAFTYPE> dict;
  static std::map<std::string,LEAFTYPE> init_dict();
};

const std::map<std::string,fTypes::LEAFTYPE> fTypes::dict = fTypes::init_dict();

std::map<std::string,fTypes::LEAFTYPE> fTypes::init_dict() {
  std::map<std::string,LEAFTYPE> dict;

  dict["bool"]      = BOOL;       dict["bools"]     = BOOL_V;
  dict["short int"] = SHORT;      dict["shorts"]    = SHORT_V;
  dict["ushort int"]= U_SHORT;    dict["ushorts"]   = U_SHORT_V;
  dict["int"]       = INT;        dict["ints"]      = INT_V;
  dict["uint"]      = U_INT;      dict["uints"]     = U_INT_V;
  dict["float"]     = FLOAT;      dict["floats"]    = FLOAT_V;
  dict["double"]    = DOUBLE;     dict["doubles"]   = DOUBLE_V;
  dict["lint"]      = LONG;       dict["longs"]     = LONG_V;
  dict["ulint"]     = U_LONG;     dict["ulongs"]    = U_LONG_V;
  dict["String"] = STRING;
  dict["Stringboolstdmap"] = STRING_BOOL_M;
  dict["Stringintstdmap"]  = STRING_INT_M;
  dict["StringStringstdmap"]  = STRING_STRING_M;
  dict["doubleROOTMathPxPyPzE4DROOTMathLorentzVector"] = LORENTZV;
  dict["doubleROOTMathPxPyPzE4DROOTMathLorentzVectors"] = LORENTZV_V;
  dict["doubleROOTMathPtEtaPhiE4DROOTMathLorentzVector"] = LORENTZV2;
  dict["doubleROOTMathPtEtaPhiE4DROOTMathLorentzVectors"] = LORENTZV2_V;
  dict["doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathPositionVector3D"] = POINT;
  dict["doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathPositionVector3Ds"] = POINT_V;
  dict["doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3D"] = VECTOR;
  dict["doubleROOTMathCartesian3DROOTMathDefaultCoordinateSystemTagROOTMathDisplacementVector3Ds"] = VECTOR_V;

  return dict;
}
