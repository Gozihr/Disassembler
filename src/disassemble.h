/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __Disassembler_H__
#define __Disassembler_H__

#include "interfaces/instruction.h"
#include "interfaces/interfaceDisassembler.h"
#include "interfaces/pch.h"
#include <iterator>
#include <memory>

class Disassembler : public InterfaceDisassembler {
public:
  Disassembler(Archtype Archtype,
               DisassemblerType type = DisassemblerType::CAPSTONE);
  virtual void Decode(const unsigned char *code, size_t size) final;
  virtual ~Disassembler() {}
  friend std::ostream &operator<<(std::ostream &out, const Disassembler &aDis);
  const std::vector<Instruction> &getInstructions() const final {
    return pDisasm->getInstructions();
  }
  void moveInstructions(std::vector<Instruction> &instructions) {
    pDisasm->moveInstructions(instructions);
  }
  virtual void Clear() final;
  void setStartAddress(uint64_t address);
  static DisassemblerType
  checkAndInitDynamicDisassemblers(const std::string &dynamicLibPaths);
  std::unique_ptr<AbstractDisassembler> getDisam() {
    return std::move(pDisasm);
  }

private:
  std::unique_ptr<AbstractDisassembler> pDisasm;
};

inline std::ostream &operator<<(std::ostream &out, const Disassembler &aDis) {
  if (aDis.pDisasm.get()) {
    out << *(aDis.pDisasm.get()) << std::endl;
  }
  return out;
}

#endif // __Disassembler_H__
