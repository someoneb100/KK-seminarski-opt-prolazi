#include "../includes/PureCallGraph.hpp"
using namespace llvm;

  void PureCallGraph::add(Function* F){
    if(calledBy.find(F) == calledBy.end()) calledBy[F] = set<Function*>();
  }

  void PureCallGraph::connect(Function* Caller, Function* Callee){
    this->add(Callee);
    this->add(Caller);
    calledBy[Callee].insert(Caller);
  }

  set<Function*> PureCallGraph::getDependancies(Function* F){
    set<Function*> dependancies = set<Function*>(calledBy[F]);
    set<Function*> open_list = set<Function*>(dependancies);
    set<Function*> closed_list = set<Function*>();
    closed_list.insert(F);
    while(!open_list.empty()){
      Function* i = *(open_list.begin());
      open_list.erase(i);
      if(closed_list.find(i) != closed_list.end()) continue;
      auto e = calledBy[i].end();
      for(auto it = calledBy[i].begin(); it != e; it++){
        Function* aaaa = *it;
        dependancies.insert(aaaa);
        open_list.insert(aaaa);
      }
      closed_list.insert(i);
    }
    return dependancies;
  }
