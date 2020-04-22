cmake_minimum_required(VERSION 3.5)
#My Stuff

add_llvm_library( LLVMCheckPureFunction MODULE
  CheckPureFunction.cpp

  PLUGIN_TOOL
  opt
  )
