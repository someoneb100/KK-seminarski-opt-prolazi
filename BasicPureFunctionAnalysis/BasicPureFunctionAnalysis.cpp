#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "../includes/PureCallGraph.hpp"
#include "../includes/BasicPureFunctionAnalysis.hpp"
#include "../includes/PureFunctionInfo.hpp"
#include <map>

using namespace std;

PureCallGraph graf;
map<Function*, PureFunctionInfo*> podaci;

bool BasicPureFunctionAnalysis::runOnModule(Module &M) {
  //Punjenje memorije
  for (auto F = M.begin(); F != M.end(); F++){
    Function* f = &(*F);
    graf.add(f);
    if(podaci.find(f) == podaci.end()) podaci[f] = new PureFunctionInfo(f);

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


  //Provera povezanosti
  for(auto it = podaci.begin(); it != podaci.end(); it++){
    PureFunctionInfo* F= it->second;
    if(F->isExternalFunction()){
      set<Function*> zavisnosti = graf.getDependancies(F->getFunction());
      for(auto it2 = zavisnosti.begin(); it2 != zavisnosti.end(); it2++)
        podaci[*it2]->addExternal(podaci[F->getFunction()]);
    }
  }

  //Izlistavanje rezultata
  for(auto it = podaci.begin(); it != podaci.end(); it++){
    PureFunctionInfo* F= it->second;
    errs()<<">-------------------------------------------------------|\n";
    errs()<<"Ime funkcije: ";
    errs().write_escaped(F->getFunction()->getName()) << '\n';
    if(F->isPureFunction())
      errs()<<"Cista funkcija!\n";
    if(F->isExternalFunction())
      errs()<<"Funkcija nije definisana, ne moze se ustanoviti cistost pre linkovanja\n";
    if(F->hasExternalFunctions())
      errs()<<"Funkcija poziva nedefinisane funkcije, ne moze se ustanoviti cistost pre linkovanja\n";
    errs()<<">-------------------------------------------------------|\n";
  }


  //Oslobadjanje memorije
  for(auto it = podaci.begin(); it != podaci.end(); it++) delete it->second;

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
