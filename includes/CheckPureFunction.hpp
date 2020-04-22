#include "llvm/Pass.h"
#include "llvm/IR/Function.h"

using namespace llvm;

class CheckPureFunction : public FunctionPass {
  public:
     static char ID;
     CheckPureFunction() : FunctionPass(ID) {}
     bool runOnFunction(Function &F);
     void getAnalysisUsage(AnalysisUsage &AU) const;
};
