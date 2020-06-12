#ifndef __PURE_FUNCTION_INFO__
  #define __PURE_FUNCTION_INFO__ 1
  #include "llvm/IR/Function.h"
  using namespace llvm;

  #include <set>
  using namespace std;

  class PureFunctionInfo{
  private:
    Function* thisFuncton;
    set<Function*> CalledBy;
    set<Function*> Calls;
    set<Function*> Externals;
    bool isPure;
    bool isExternal;
  public:
    PureFunctionInfo(Function* F);
    bool isPureFunction(){return isPure;}
    bool isExternalFunction(){return isExternal;}
    Function* getFunction(){return thisFuncton;}
    bool hasExternalFunctions(){return !Externals.empty();}
    void addCalledBy(PureFunctionInfo* F);
    void addCalls(PureFunctionInfo* F);
    bool addExternal(PureFunctionInfo* F);
  };
#endif
