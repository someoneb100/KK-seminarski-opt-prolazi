#ifndef __PURE_CALL_GRAPH__
  #define __PURE_CALL_GRAPH__ 1
  #include <map>
  #include <set>
  using namespace std;

  #include "llvm/IR/Function.h"
  using namespace llvm;

  class PureCallGraph{
    private:
      map<Function*, set<Function*>> calledBy;
    public:
      void add(Function* F);
      void connect(Function* Caller, Function* Callee);
      set<Function*> getDependancies(Function* F);
  };
#endif
