// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "disassemble.h"
#include "capstoneDisassembler.h"
#include "dynamicDisassembler.h"
#include "pluginInfra/dynamicLibMgr.h"

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

void Disassembler::setStartAddress(uint64_t address) {
  pDisasm->setStartAddress(address);
}

void Disassembler::Clear() { pDisasm->Clear(); }

DisassemblerType Disassembler::checkAndInitDynamicDisassemblers(
    const std::string &dynamicLibPaths) {
  DisassemblerType dType = DisassemblerType::CAPSTONE;
  if (!dynamicLibPaths.empty()) {
    std::vector<std::string> vecDynamicLibPaths;
    StringHelpers::Split(dynamicLibPaths, vecDynamicLibPaths, ',');
    DynamicLibMgr::loadDynamicLibs(vecDynamicLibPaths);
    dType = DisassemblerType::DYNAMIC;
  }
  return dType;
}