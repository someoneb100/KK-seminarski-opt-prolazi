#ifndef __BASIC_PURE_FUNCTION_ANALYSIS__
  #define __BASIC_PURE_FUNCTION_ANALYSIS__ 1
  #include "llvm/Pass.h"
  #include "llvm/IR/Module.h"
  #include "llvm/IR/Function.h"
  #include "llvm/IR/BasicBlock.h"
  #include "llvm/IR/Instructions.h"
  #include "llvm/Support/Casting.h"
  #include "llvm/IR/InstrTypes.h"
  #include "llvm/Support/raw_ostream.h"
  #include "llvm/IR/GlobalVariable.h"

  using namespace llvm;

  class BasicPureFunctionAnalysis : public ModulePass {
    public:
      static char ID;
      BasicPureFunctionAnalysis() : ModulePass(ID) {}
      bool runOnModule(Module &M);
      void getAnalysisUsage(AnalysisUsage &AU) const;
  };
#endif
