
#ifndef __Dynamic_Lib_Mgr_H__
#define __Dynamic_Lib_Mgr_H__

#if defined(_WIN32) || defined(_WIN64)
#define CALL_CONV __stdcall
#else
#define CALL_CONV
#endif

typedef int(CALL_CONV *func_ptr_t)();

typedef struct disasmImpl {
  int (*initalize)();
  int (*shutdown)();
  bool (*isInitalized)();
  bool (*isEnabled)();

  static const int NUM_FUNCTIONS = 4;
} disasmImpl;

typedef union {
  disasmImpl by_type;
  func_ptr_t func_ptr[disasmImpl::NUM_FUNCTIONS];
} function_union;

class DynamicLibMgr {
private:
  DynamicLibMgr() = delete;

public:
  static int loadDynamicLibs(std::vector<std::string> &dylibPaths);
  static bool loadDynamicLib(const std::string &sLoadPath);
  static void unloadDynamicLib(const std::string &dylibPath);
  static void setDefaultDynamicLib(const std::string &dylibPath);
  static const char *getDynamicLibFunctionName(int index);
  static bool isInitalized();
  static bool isEnabled();
  static int initalize();
  static int shutdown();
};

#endif // __Dynamic_Lib_Mgr_H__