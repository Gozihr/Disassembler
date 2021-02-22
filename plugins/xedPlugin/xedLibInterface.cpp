#include "../dataPattern/singleton.h"
#include "libInterface.h"
#include "xedDisassembler.h"
#include <iostream>
#include <memory>
#include <mutex>

struct Singleton_XedDisassembler_Members {
  Singleton_XedDisassembler_Members(){};
  std::unique_ptr<XedDisassembler> pXedDisassembler;
};

typedef SingletonBase<Singleton_XedDisassembler_Members> Singleton;

std::vector<std::string> vecEmpty;

// FL TODO: This api is not used for safety reasons.
// However in perf testing it seems faster to pass a pointer
// than to call the class functions in a c wrapper
// like the functions below. Investigate if there is a
// safe way to pass a pointer that you don't want anyone outside
// the dll to own. Good resource maybe to lookup how com proxies work again.
EXPORT(AbstractDisassembler*) GetDisassembler() {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  return instance.pXedDisassembler.get();
}

EXPORT(void) Decode(const unsigned char *code, size_t size) {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  if (instance.pXedDisassembler == nullptr) {
    std::cerr << "XedDisassembler is not Initalize!" << std::endl;
    return;
  }
  instance.pXedDisassembler->Decode(code, size);
}

EXPORT(void) Clear() {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  if (instance.pXedDisassembler == nullptr) {
    std::cerr << "XedDisassembler is not Initalize!" << std::endl;
    return;
  }
  instance.pXedDisassembler->Clear();
}

EXPORT(const std::vector<std::string>&) GetOperands() {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  if (instance.pXedDisassembler == nullptr) {
    std::cerr << "XedDisassembler is not Initalize!" << std::endl;
    return vecEmpty;
  }
  return instance.pXedDisassembler->getOperands();
}

EXPORT(const std::vector<std::string>&) GetOpCodes() {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  if (instance.pXedDisassembler == nullptr) {
    std::cerr << "XedDisassembler is not Initalize!" << std::endl;
    return vecEmpty;
  }
  return instance.pXedDisassembler->getOpCodes();
}

EXPORT(void) Initalize(Archtype archType) {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  if (instance.pXedDisassembler == nullptr) {
    instance.pXedDisassembler = std::make_unique<XedDisassembler>(archType);
  }
}

EXPORT(bool) IsInitalized() {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  return instance.pXedDisassembler != nullptr;
}