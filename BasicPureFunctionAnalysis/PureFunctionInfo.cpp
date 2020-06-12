#include "../includes/PureFunctionInfo.hpp"


PureFunctionInfo::PureFunctionInfo(Function* F){
  thisFuncton = F;
  isExternal = F->empty();
  isPure = !isExternal;
}

void PureFunctionInfo::addCalledBy(PureFunctionInfo* F){
  CalledBy.insert(F->getFunction());
}

void PureFunctionInfo::addCalls(PureFunctionInfo* F){
  Calls.insert(F->getFunction());
}

bool PureFunctionInfo::addExternal(PureFunctionInfo* F){
  if((F->isExternal or F->hasExternalFunctions())){
    Function* f = F->getFunction();
    if(Externals.find(f) == Externals.end()){
      Externals.insert(f);
      isPure = false;
      return true;
    }
  }
  return false;
}
