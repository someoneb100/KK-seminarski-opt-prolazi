#include "../includes/PureFunctionInfo.hpp"


PureFunctionInfo::PureFunctionInfo(Function* F){
  thisFuncton = F;
  isExternal = F->empty();
  isPure = !isExternal;
  isGlobal = false;
  PointerArguments = 0;
}

void PureFunctionInfo::setPointerAttributes(unsigned i){
  PointerArguments = i;
  isPure = !i;
}

void PureFunctionInfo::addExternal(PureFunctionInfo* F){
  this->addExternal(F->getFunction());
}

void PureFunctionInfo::addExternal(Function* F){
  Externals.insert(F);
  isPure = false;
}
void PureFunctionInfo::addGlobal(Value* V){
  Globals.insert(V);
  isPure = false;
  isGlobal = true;
}


void PureFunctionInfo::addGlobal(Function* F){
    GlobalFs.insert(F);
    isPure = false;
}
void PureFunctionInfo::addGlobal(PureFunctionInfo* F){
  this->addGlobal(F->getFunction());
}
