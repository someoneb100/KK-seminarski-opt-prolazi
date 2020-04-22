#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;


namespace {
  struct CheckPureFunction : public FunctionPass {
    static char ID;
    CheckPureFunction() : FunctionPass(ID) {}
    bool runOnFunction(Function &F) override {
      errs() << ">-----------------------|\n";
      errs() << "Ime funkcije: ";
      errs().write_escaped(F.getName()) << '\n';
      //TODO Odrediti da li je u pitanju definisana ili samo deklarisana f-ja
      //TODO Odrediti da li medju argumentima postoji argument po referenci
      //TODO Napraviti mapu zavisnosti cistoce f-ja
      //TODO Napraviti mapu globalnih promenljivih u funciji
      errs() << ">-----------------------|\n";
      return false;
    }
  };
}


char CheckPureFunction::ID = 0;
static RegisterPass<CheckPureFunction> X("cpf", "Proverava da li je funkcija cista", false, true);
