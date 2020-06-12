#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "../includes/PureCallGraph.hpp"
#include "../includes/BasicPureFunctionAnalysis.hpp"
#include "../includes/PureFunctionInfo.hpp"
#include <map>
using namespace std;

PureCallGraph graf;

bool BasicPureFunctionAnalysis::runOnModule(Module &M) {
  //Punjenje memorije
  for (auto F = M.begin(); F != M.end(); F++){
    Function* f = &(*F);
    graf.addFunction(f);

    //Provera pojedinacnih instrukcija
    for(auto itBB = f->begin(); itBB != f->end(); itBB++){
      BasicBlock* BB = &(*itBB);
      for(auto itInst = BB->begin(); itInst != BB->end(); itInst++){
        if(isa<CallInst>(itInst)){
          CallInst *ci = cast<CallInst>(itInst);
          Function *callee = ci->getCalledFunction();
          graf.connect(f, callee);
        }
      }
    }
  }


  //TODO: provera povezanosti
  graf.sync();


  //Izlistavanje rezultata
  graf.printResults();
  return false;
}

void BasicPureFunctionAnalysis::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.setPreservesAll();
}

char BasicPureFunctionAnalysis::ID = 0;
static RegisterPass<BasicPureFunctionAnalysis> X("bpfa", "Osnovna analiza cistih funkcija", true, true);

static llvm::RegisterStandardPasses Y(
    llvm::PassManagerBuilder::EP_EarlyAsPossible,
    [](const llvm::PassManagerBuilder &Builder,
       llvm::legacy::PassManagerBase &PM) { PM.add(new BasicPureFunctionAnalysis()); });
