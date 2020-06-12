#include "../includes/PureCallGraph.hpp"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#include <set>
using namespace std;


 void PureCallGraph::addFunction(Function* F){
  if(information.find(F) == information.end()) information[F] = new PureFunctionInfo(F);
}

PureFunctionInfo* PureCallGraph::getFunction(Function* F){
  this->addFunction(F);
  return information[F];
}

void PureCallGraph::connect(Function* Caller,Function* Callee){
  PureFunctionInfo* callee =  this->getFunction(Callee);
  PureFunctionInfo* caller =  this->getFunction(Caller);
  callee->addCalledBy(caller);
  caller->addCalls(callee);
}

void PureCallGraph::sync(){

}

void PureCallGraph::printResults() const{
  for (auto F = information.begin(); F != information.end(); F++){
    errs() << ">-----------------------|\n";
    PureFunctionInfo* Funkcija =  F->second;
    errs() << "Ime funkcije: ";
    errs().write_escaped(Funkcija->getFunction()->getName()) << '\n';

    if(Funkcija->isPureFunction())
      errs() << "Cista funkcija!\n";
    if(Funkcija->isExternalFunction())
      errs() << "Funkcija nije definisana\n";
    if(Funkcija->hasExternalFunctions())
      errs() << "Funkcija poseduje nedefinisane funkcije\n";
    errs() << ">-----------------------|\n";
  }
}
