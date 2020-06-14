#ifndef __PURE_FUNCTION_INFO__
  #define __PURE_FUNCTION_INFO__ 1
  #include "llvm/IR/Function.h"
  using namespace llvm;

  #include <set>
  using namespace std;

  class PureFunctionInfo{
  private:
    Function* thisFuncton;
    set<Function*> Externals;
    set<Function*> GlobalFs;
    set<Value*> Globals;
    bool isPure;
    bool isExternal;
    bool isGlobal;
  public:
    PureFunctionInfo(Function* F);
    bool isPureFunction(){return isPure;}
    bool isExternalFunction(){return isExternal;}
    bool isGlobalFunction(){return isGlobal;}
    bool isDirectlyImpureFunction(){return !isPure && (isExternal || isGlobal);}
    Function* getFunction(){return thisFuncton;}
    bool hasGlobalFunctions(){return !GlobalFs.empty();}
    bool hasExternalFunctions(){return !Externals.empty();}
    void addExternal(PureFunctionInfo* F);
    void addExternal(Function* F);
    void addGlobal(Value* V);
    void addGlobal(Function* V);
    void addGlobal(PureFunctionInfo* V);
  };
#endif
