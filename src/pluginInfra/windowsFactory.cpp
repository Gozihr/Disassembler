#include <Windows.h>
#include <cassert>

#include "windowsFactory.h"

Load_ptr WindowsFactory::getLoadLib() {
    return Helper::makeShared<WindowsDLibLoad>();
}

bool WindowsDLibLoad::LoadLibraryFromPath(std::string sLoadPath) {
    if(AbstractOSFactory::doesFileExist(sLoadPath)) {
        return false;
    }
    mProcHinstance = LoadLibraryA(sLoadPath.c_str());
    if(mProcHinstance == nullptr) {
        return false;
    }

    for(int i = 0; i < disasmImpl::NUM_FUNCTIONS; i++) {
        mDllFunctions.func_ptr[i] =  reinterpret_cast<func_ptr_t>(GetProcAddress(mProcHinstance, DynamicLibMgr::getDynamicLibFunctionName(i)));
        assert(mDllFunctions.func_ptr[i] != nullptr);
    }
    mDllFunctions.by_type.initalize();
    return mDllFunctions.by_type.isInitalized();
}

function_union& WindowsDLibLoad::getLoadedLibrary() {
    return mDllFunctions;
}

WindowsDLibLoad::~WindowsDLibLoad() {
    if(mProcHinstance != nullptr) {
        mDllFunctions.by_type.shutdown();
        assert(mDllFunctions.by_type.isInitalized() == false);
        FreeLibrary(mProcHinstance);
    }
}