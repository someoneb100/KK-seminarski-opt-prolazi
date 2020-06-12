cmake_minimum_required(VERSION 3.5)
#My Stuff

add_llvm_library( LLVMBasicPureFunctionAnalysis MODULE
  BasicPureFunctionAnalysis.cpp
  PureFunctionInfo.cpp
  PureCallGraph.cpp
  PLUGIN_TOOL
  opt
  )
