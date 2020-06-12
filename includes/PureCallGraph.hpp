#ifndef __PURE_CALL_GRAPH__
  #define __PURE_CALL_GRAPH__ 1
  #include <map>
  using namespace std;

  #include "../includes/PureFunctionInfo.hpp"

  class PureCallGraph{
    private:
      map<Function*, PureFunctionInfo*> information;
    public:
      void addFunction(Function* F);
      PureFunctionInfo* getFunction(Function* F);
      void connect(Function* Caller, Function* Callee);
      void sync();
      void printResults() const;
  };
#endif
