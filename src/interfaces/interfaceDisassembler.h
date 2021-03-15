/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __Interface_Disassembler_H__
#define __Interface_Disassembler_H__

#include "instruction.h"
#include "pch.h"
#include "types.h"
#include <iterator>

class InterfaceDisassembler {
public:
  virtual void Decode(const unsigned char *code, size_t size) = 0;
  virtual void Clear() = 0;
  virtual ~InterfaceDisassembler(){};
  virtual const std::vector<Instruction> &getInstructions() const = 0;
  virtual void setStartAddress(uint64_t address) = 0;
};

class AbstractDisassembler : public InterfaceDisassembler {
public:
  AbstractDisassembler() : startAddress(0) {}
  virtual ~AbstractDisassembler() {}
  friend std::ostream &operator<<(std::ostream &out,
                                  const AbstractDisassembler &aDis);

  virtual const std::vector<Instruction> &getInstructions() const {
    return mInstructions;
  }

  void moveInstructions(std::vector<Instruction> &instructions) {
    this->mInstructions.swap(instructions);
  }

  virtual void Clear() { mInstructions.clear(); }
  virtual void setStartAddress(uint64_t address) { startAddress = address; }

protected:
  std::vector<Instruction> mInstructions;
  uint64_t startAddress;
};

inline std::ostream &operator<<(std::ostream &out,
                                const AbstractDisassembler &aDis) {
  auto instructions = aDis.mInstructions;
  out << "Instruction count: " << instructions.size() << std::endl;
  out << "  address  |  opcode  |  operands" << std::endl;
  out << "---------------------------------" << std::endl;
  out << instructions << std::endl;
  return out;
}

#endif // __Interface_Disassembler_H__
