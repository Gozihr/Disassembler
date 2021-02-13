#include "macFactory.h"
#include <cassert>
#include <dlfcn.h>
#include <iostream>

Load_ptr MacFactory::getLoadLib() {
  return Helpers::makeShared<MacDylibLoad>();
}

bool MacDylibLoad::LoadLibraryFromPath(std::string sLoadPath) {
  // if (AbstractOSFactory::doesFileExist(sLoadPath)) {
  //  return false;
  //}
  mDylib = dlopen(sLoadPath.c_str(), RTLD_LAZY);
  if (mDylib == nullptr) {
    std::cerr << dlerror() << std::endl;
    return false;
  }

  for (int i = 0; i < disasmImpl::NUM_FUNCTIONS; i++) {
    mDyLibFunctions.func_ptr[i] = reinterpret_cast<func_ptr_t>(
        dlsym(mDylib, DynamicLibMgr::getDynamicLibFunctionName(i)));
    assert(mDyLibFunctions.func_ptr[i] != nullptr);
    if (mDyLibFunctions.func_ptr[i] == nullptr) {
      return false;
    }
  }

  return true;
}

function_union &MacDylibLoad::getLoadedLibrary() { return mDyLibFunctions; }

MacDylibLoad::~MacDylibLoad() {
  if (mDylib != nullptr) {
    dlclose(mDylib);
    mDylib = nullptr;
  }
}