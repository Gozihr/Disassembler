
#ifndef __Dynamic_Lib_Mgr_H__
#define __Dynamic_Lib_Mgr_H__

#if defined(_WIN32) || defined(_WIN64)
#define CALL_CONV __stdcall
#else
#define CALL_CONV
#endif

#include "interfaces/types.h"
#include <memory>

class AbstractDisassembler;
typedef int(CALL_CONV *func_ptr_t)();

typedef struct disasmImpl {
  void (*Initalize)(Archtype archType);
  bool (*IsInitalized)();
  AbstractDisassembler *(*GetDisassembler)();
  void (*Decode)(const unsigned char *, size_t);
  void (*Clear)();
  void (*GetOperands)(std::vector<std::string> &);
  void (*GetOpCodes)(std::vector<std::string> &);

  static const int NUM_FUNCTIONS = 7;
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
  static void initalize(Archtype archType);
  static AbstractDisassembler *getDisassembler();
  static void decode(const unsigned char *code, size_t size);
  static void clear();
  static void getOperands(std::vector<std::string> &operands);
  static void getOpCodes(std::vector<std::string> &opCodes);
};

#endif // __Dynamic_Lib_Mgr_H__