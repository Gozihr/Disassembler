
#ifndef __Dynamic_Lib_Mgr_H__
#define __Dynamic_Lib_Mgr_H__

#if defined(_WIN32) || defined(_WIN64)
#define CALL_CONV __stdcall
#else
#define CALL_CONV
#endif

typedef int(CALL_CONV* func_ptr_t)();

typedef struct disasmImpl {
    int(*initalize)();
    int(*shutdown)();
    bool(*isInitalized)();
    bool(*isEnabled)();

    static const int NUM_FUNCTIONS = 3;
} disasmImpl;

typedef union {
    disasmImpl by_type;
    func_ptr_t func_ptr[disasmImpl::NUM_FUNCTIONS];
}

class DynamicLibMgr {
    private:
        DynamicLibMgr() = delete;
    public 
        static int loadDynamicLibs();
        // returns an id 
        static std::string loadDynamicLib(std::string sLoadPath);
        static void unloadDynamicLib(std::string  id);
        static void setDefaultDynamicLib(std::string  id);
        static const char* getDynamicLibFunctionName(int index);

        static bool isInitialized();
        static bool isEnabled();
        static int initalize():
        static int shutdown();
};

#endif // __Dynamic_Lib_Mgr_H__