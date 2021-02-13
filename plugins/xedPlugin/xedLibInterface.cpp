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

// FL TODO: This api is not used for safety reasons.
// However in perf testing it seems faster to pass a pointer
// than to call the class functions in a c wrapper
// like the functions below. Investigate if there is a
// safe way to pass a pointer that you don't want anyone outside
// the dll to own. Good resource maybe to lookup how com proxies work again.
extern "C" AbstractDisassembler *GetDisassembler() {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  return instance.pXedDisassembler.get();
}

extern "C" void Decode(const unsigned char *code, size_t size) {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  if (instance.pXedDisassembler == nullptr) {
    std::cerr << "XedDisassembler is not Initalize!" << std::endl;
    return;
  }
  instance.pXedDisassembler->Decode(code, size);
}

extern "C" void Clear() {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  if (instance.pXedDisassembler == nullptr) {
    std::cerr << "XedDisassembler is not Initalize!" << std::endl;
    return;
  }
  instance.pXedDisassembler->Clear();
}

extern "C" void GetOperands(std::vector<std::string> &operands) {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  if (instance.pXedDisassembler == nullptr) {
    std::cerr << "XedDisassembler is not Initalize!" << std::endl;
    return;
  }
  auto xedOperands = instance.pXedDisassembler->getOperands();
  operands.assign(xedOperands.begin(), xedOperands.end());
}

extern "C" void GetOpCodes(std::vector<std::string> &opCodes) {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  if (instance.pXedDisassembler == nullptr) {
    std::cerr << "XedDisassembler is not Initalize!" << std::endl;
    return;
  }
  auto xedOpCodes = instance.pXedDisassembler->getOpCodes();
  opCodes.assign(xedOpCodes.begin(), xedOpCodes.end());
}

extern "C" void Initalize(Archtype archType) {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  if (instance.pXedDisassembler == nullptr) {
    instance.pXedDisassembler = std::make_unique<XedDisassembler>(archType);
  }
}

// extern "C" void Shutdown() {
//     auto &instance = Singleton::get();
//     auto lock(instance.getLock());
//     if(instance.pXedDisassembler){
//        delete instance.pXedDisassembler;
//        instance.pXedDisassembler = nullptr;
//     }
//}

extern "C" bool IsInitalized() {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  return instance.pXedDisassembler != nullptr;
}