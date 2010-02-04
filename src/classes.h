#ifndef SUSYCAF_CLASSES_H
#define SUSYCAF_CLASSES_H

#include "DataFormats/Common/interface/Wrapper.h"
#include <string>
#include <map>

namespace {
  struct dictionary {
    std::map<std::string,bool> dummy0;
    edm::Wrapper<std::map<std::string,bool> > dummy1;

    std::map<std::string,int> dummi0;
    edm::Wrapper<std::map<std::string,int> > dummi1;
  };
}

#endif 
