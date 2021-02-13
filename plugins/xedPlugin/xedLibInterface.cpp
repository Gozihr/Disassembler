#include "libInterface.h"
#include "xedDisassembler.h"
#include <mutex>
#include <iostream>

typedef const std::lock_guard<std::mutex> Lock;
AbstractDisassembler* pXedDisassembler = nullptr;
std::mutex gMutex;

extern "C" AbstractDisassembler* GetDisassembler() {
     Lock lock(gMutex);
     return pXedDisassembler;
}

extern "C" void Decode(const unsigned char *code, size_t size) {
     Lock lock(gMutex);
     if(pXedDisassembler == nullptr){
         std::cerr << "XedDisassembler is not Initalize!" << std::endl;
         return;
     }
     pXedDisassembler->Decode(code,size);
}

extern "C" void Clear() {
     Lock lock(gMutex);
     if(pXedDisassembler == nullptr){
         std::cerr << "XedDisassembler is not Initalize!" << std::endl;
         return;
     }
     pXedDisassembler->Clear();
}

extern "C" void GetOperands(std::vector<std::string> &operands) {
     Lock lock(gMutex);
     if(pXedDisassembler == nullptr){
         std::cerr << "XedDisassembler is not Initalize!" << std::endl;
         return;
     }
    auto xedOperands = pXedDisassembler->getOperands();
    operands.assign(xedOperands.begin(), xedOperands.end());
}

extern "C" void GetOpCodes(std::vector<std::string> &opCodes) {
     Lock lock(gMutex);
     if(pXedDisassembler == nullptr){
         std::cerr << "XedDisassembler is not Initalize!" << std::endl;
         return;
     }
     auto xedOpCodes = pXedDisassembler->getOpCodes();
     opCodes.assign(xedOpCodes.begin(), xedOpCodes.end());
}

extern "C" void Initalize(Archtype archType) {
     Lock lock(gMutex);
     if(pXedDisassembler == nullptr) {
         pXedDisassembler = new XedDisassembler(archType);
     }
}

extern "C" void Shutdown() {
     Lock lock(gMutex);
     if(pXedDisassembler){
        delete pXedDisassembler;
        pXedDisassembler = nullptr;
     }
}

extern "C" bool IsInitalized() {
     Lock lock(gMutex);
     return pXedDisassembler != nullptr;
}