#include "../includes/PureFunctionInfo.hpp"


PureFunctionInfo::PureFunctionInfo(Function* F){
  thisFuncton = F;
  isExternal = F->empty();
  isPure = !isExternal;
}

void PureFunctionInfo::addExternal(PureFunctionInfo* F){
  Function* f = F->getFunction();
  Externals.insert(f);
  isPure = false;
}
