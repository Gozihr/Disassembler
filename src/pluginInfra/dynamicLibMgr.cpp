#include <cassert>
#include <map>
#include <vector>

#include "abstractOSFactory.h"
#include "dataPattern/singleton.h"
#include "dynamicLibMgr.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

namespace {
struct Singleton_DynamicLibMgr_Members {
  Singleton_DynamicLibMgr_Members();
  int loadDynamicLibs(std::vector<std::string> &dylibPaths);
  bool loadDynamicLib(const std::string &sLoadPath);
  function_union *getFunctions(const std::string &sChosenDylibPath = "");
  void unloadDynamicLib(const std::string &dylibPath);
  void setDefaultDynamicLib(const std::string &dylibPath);

private:
  std::string sCurrentDylibPath;
  std::map<std::string, Load_ptr> mapFilePathToDylibFunctions;
};
} // namespace

Singleton_DynamicLibMgr_Members::Singleton_DynamicLibMgr_Members() {}

typedef SingletonBase<Singleton_DynamicLibMgr_Members> Singleton;

const char *arrDylibFunctionNames[] = {
    "Initalize", "IsInitalized", "GetDisassembler", "Decode",
    "Clear",     "GetOperands",  "GetOpCodes"};

function_union *Singleton_DynamicLibMgr_Members::getFunctions(
    const std::string &sChosenDylibPath) {
  std::string sSelectedDylibPath = sChosenDylibPath;
  if (sSelectedDylibPath.empty()) {
    sSelectedDylibPath = sCurrentDylibPath;
  }
  assert(!sSelectedDylibPath.empty());
  assert(mapFilePathToDylibFunctions.begin() !=
         mapFilePathToDylibFunctions.end());

  std::map<std::string, Load_ptr>::iterator it;
  it = mapFilePathToDylibFunctions.find(sSelectedDylibPath);
  if (it != mapFilePathToDylibFunctions.end()) {
    return &it->second->getLoadedLibrary();
  }

  return nullptr;
}

int DynamicLibMgr::loadDynamicLibs(std::vector<std::string> &dylibPaths) {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  return instance.loadDynamicLibs(dylibPaths);
}

int Singleton_DynamicLibMgr_Members::loadDynamicLibs(
    std::vector<std::string> &dylibPaths) {
  int count = 0;
  for (auto iter = dylibPaths.begin(); iter != dylibPaths.end(); ++iter) {
    bool success = loadDynamicLib(*iter);
    if (success) {
      count++;
    }
  }
  assert(count == dylibPaths.size());
  return count;
}

bool DynamicLibMgr::loadDynamicLib(const std::string &sLoadPath) {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  return instance.loadDynamicLib(sLoadPath);
}

bool Singleton_DynamicLibMgr_Members::loadDynamicLib(
    const std::string &sLoadPath) {
  AbstractOSFactory_ptr factory = AbstractOSFactory::createFactory();
  Load_ptr dylibLoader = factory->getLoadLib();
  if (dylibLoader->LoadLibraryFromPath(sLoadPath)) {
    mapFilePathToDylibFunctions[sLoadPath] = dylibLoader;
    setDefaultDynamicLib(sLoadPath);
    return true;
  }
  return false;
}

void DynamicLibMgr::unloadDynamicLib(const std::string &dylibPath) {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  instance.unloadDynamicLib(dylibPath);
}

void Singleton_DynamicLibMgr_Members::unloadDynamicLib(
    const std::string &dylibPath) {
  std::map<std::string, Load_ptr>::iterator it;
  it = mapFilePathToDylibFunctions.find(dylibPath);
  if (it != mapFilePathToDylibFunctions.end()) {
    mapFilePathToDylibFunctions.erase(it);
  }
}

void DynamicLibMgr::setDefaultDynamicLib(const std::string &dylibPath) {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  instance.setDefaultDynamicLib(dylibPath);
}
void Singleton_DynamicLibMgr_Members::setDefaultDynamicLib(
    const std::string &dylibPath) {
  sCurrentDylibPath = dylibPath;
}

const char *DynamicLibMgr::getDynamicLibFunctionName(int index) {
  assert(disasmImpl::NUM_FUNCTIONS == ARRAY_SIZE(arrDylibFunctionNames));
  if (index >= 0 && index < disasmImpl::NUM_FUNCTIONS) {
    return arrDylibFunctionNames[index];
  }
  return "";
}

bool DynamicLibMgr::isInitalized() {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  function_union *dylibFunctions = instance.getFunctions();
  assert(dylibFunctions != nullptr);
  return dylibFunctions->by_type.IsInitalized();
}

void DynamicLibMgr::initalize(Archtype archType) {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  function_union *dylibFunctions = instance.getFunctions();
  assert(dylibFunctions != nullptr);
  dylibFunctions->by_type.Initalize(archType);
}

AbstractDisassembler *DynamicLibMgr::getDisassembler() {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  function_union *dylibFunctions = instance.getFunctions();
  assert(dylibFunctions != nullptr);
  return dylibFunctions->by_type.GetDisassembler();
}

void DynamicLibMgr::decode(const unsigned char *code, size_t size) {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  function_union *dylibFunctions = instance.getFunctions();
  assert(dylibFunctions != nullptr);
  dylibFunctions->by_type.Decode(code, size);
}

void DynamicLibMgr::clear() {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  function_union *dylibFunctions = instance.getFunctions();
  assert(dylibFunctions != nullptr);
  dylibFunctions->by_type.Clear();
}

void DynamicLibMgr::getOperands(std::vector<std::string> &operands) {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  function_union *dylibFunctions = instance.getFunctions();
  assert(dylibFunctions != nullptr);
  auto libOperands = dylibFunctions->by_type.GetOperands();
  if(libOperands) {
    operands.assign(libOperands->begin(), libOperands->end());
  }
}

void DynamicLibMgr::getOpCodes(std::vector<std::string> &opCodes) {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  function_union *dylibFunctions = instance.getFunctions();
  assert(dylibFunctions != nullptr);
  auto libOpCodes = dylibFunctions->by_type.GetOpCodes();
  if(libOpCodes) {
    opCodes.assign(libOpCodes->begin(), libOpCodes->end());
  }
}