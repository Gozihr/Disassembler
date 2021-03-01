#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include "helpers.h"
#include <iomanip>
#include <string>
#include <vector>

struct Instruction {
  uint64_t address;
  std::string opcode;
  std::string operandsStr;
  std::vector<std::string> operands;
  Instruction(uint64_t address, std::string opcode, std::string operandsStr)
      : address(address), opcode(opcode), operandsStr(operandsStr) {
    using namespace std::placeholders;
    StringHelpers::stringFunc trim = std::bind(StringHelpers::trim, _1);
    StringHelpers::Split(operandsStr, operands, trim);
  }
};

inline std::ostream &operator<<(std::ostream &out,
                                const Instruction &instruction) {
  out << std::left << "0x" << std::setw(8) << std::hex << instruction.address
      << std::setw(9) << instruction.opcode << instruction.operandsStr;
  return out;
}

#endif // __INSTRUCTION_H__