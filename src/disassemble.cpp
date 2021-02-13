#include "disassemble.h"
#include "capstoneDisassembler.h"
#include "dynamicDisassembler.h"

namespace {
std::unique_ptr<AbstractDisassembler> pickDisam(Archtype archType,
                                                DisassemblerType disamType) {
  switch (disamType) {
  case DisassemblerType::CAPSTONE: {
    return std::make_unique<CapstoneDisassembler>(archType);
  }
  case DisassemblerType::DYNAMIC: {
    return std::make_unique<DynamicDisassembler>(archType);
  }
  }
  return nullptr;
}
} // namespace

Disassembler::Disassembler(Archtype archtype, DisassemblerType disamType)
    : InterfaceDisassembler() {
  pDisasm = pickDisam(archtype, disamType);
}

void Disassembler::Decode(const unsigned char *code, size_t size) {
  pDisasm->Decode(code, size);
}

void Disassembler::Clear() { pDisasm->Clear(); }