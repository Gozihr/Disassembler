/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include "helpers.h"
#include "pch.h"

struct Instruction {
  uint64_t address;
  std::string opcode;
  std::string operandsStr;
  std::vector<std::string> operands;
  Instruction(uint64_t address, std::string opcode, std::string operandsStr)
      : address(address), opcode(opcode), operandsStr(operandsStr) {

    StringHelpers::stringFunc trim = StringHelpers::trim;
    StringHelpers::Split(operandsStr, operands, ',', trim);
  }
};

typedef std::vector<Instruction> Instructions;

inline std::ostream &operator<<(std::ostream &out,
                                const Instruction &instruction) {
  out << std::left << "0x" << std::setw(11) << std::hex << instruction.address
      << std::setw(9) << instruction.opcode << instruction.operandsStr;
  return out;
}
inline std::ostream &operator<<(std::ostream &out,
                                const Instructions &instructions) {
  for (size_t i = 0; i < instructions.size(); i++) {
    out << instructions[i] << std::endl;
  }
  return out;
}

#endif // __INSTRUCTION_H__