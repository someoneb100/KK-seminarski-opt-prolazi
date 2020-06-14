#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "../includes/PureCallGraph.hpp"
#include "../includes/BasicPureFunctionAnalysis.hpp"
#include "../includes/PureFunctionInfo.hpp"
#include <map>

using namespace std;

PureCallGraph graf;
map<Function*, PureFunctionInfo*> podaci;
set<Value*> globalne;
bool BasicPureFunctionAnalysis::runOnModule(Module &M) {
  //provera postojanja globalnih promenljivih
  auto krajGlobalnih = M.getGlobalList().end();
  for(auto it = M.getGlobalList().begin(); it!=krajGlobalnih; it++)
    if(!it->isConstant()) globalne.insert(&(*it));


  //Punjenje memorije
  for (auto F = M.begin(); F != M.end(); F++){
    Function* f = &(*F);
    graf.add(f);
    if(podaci.find(f) == podaci.end()) podaci[f] = new PureFunctionInfo(f);

    //Provera pojedinacnih instrukcija
    for (const BasicBlock &BB : *F){
      for (const Instruction &I : BB){
        if(isa<CallInst>(I)){
          Function *callee = cast<CallInst>(I).getCalledFunction();
          graf.connect(f, callee);
        }
        for(auto it = I.op_begin(); it!=I.op_end();it++){
          Value* Op = it->get();
          if (globalne.find(Op) != globalne.end()){
            podaci[f]->addGlobal(Op);
          }
        }
      }
    }
  }


  //Provera povezanosti
  auto krajPodataka = podaci.end();
  for(auto it = podaci.begin(); it != krajPodataka; it++){
    PureFunctionInfo* F= it->second;
    if(F->isDirectlyImpureFunction()){
      set<Function*> zavisnosti = graf.getDependancies(F->getFunction());
      auto krajZavisnosti = zavisnosti.end();
      for(auto it2 = zavisnosti.begin(); it2 != krajZavisnosti; it2++){
        if(F->isExternalFunction()) podaci[*it2]->addExternal(F);
        if(F->isGlobalFunction()) podaci[*it2]->addGlobal(F);
      }
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
    if(F->isGlobalFunction())
      errs()<<"Funkcija koristi globalne promenljive\n";
    if(F->hasGlobalFunctions())
      errs()<<"Funkcija poziva funkcije koje koriste globalne promenljive\n";
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
