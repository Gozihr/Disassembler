#include <cassert>

#include "linuxFactory.h"

Load_ptr LinuxFactory::getLoadLib() {
  return Helper::makeShared<LinuxSOLoad>();
}

bool LinuxSOLoad::LoadLibraryFromPath(std::string sLoadPath) {
  if (AbstractOSFactory::doesFileExist(sLoadPath)) {
    return false;
  }
  mGmodule = g_module_open(sLoadPath.c_str(), G_MODULE_BIND_LAZY);
  if (mGmodule == nullptr) {
    return false;
  }
  for (int i = 0; i < disasmImpl::NUM_FUNCTIONS; i++) {
    g_module_symbol(mGmodule, DynamicLibMgr::getDynamicLibFunctionName(i),
                    (gpointer *)&mSOLibFunctions.func_ptr[i]);
    assert(mSOLibFunctions.func_ptr[i] != nullptr);
  }
  mSOLibFunctions.by_type.initalize();
  return mSOLibFunctions.by_type.isInitalized();
}

function_union &LinuxSOLoad::getLoadedLibrary() { return mSOLibFunctions; }

LinuxSOLoad::~LinuxSOLoad() {
  if (mGmodule != nullptr) {
    mSOLibFunctions.by_type.shutdown();
    assert(mSOLibFunctions.by_type.isInitalized() == false);
    g_module_close(mGmodule);
    mGmodule = nullptr;
  }
}