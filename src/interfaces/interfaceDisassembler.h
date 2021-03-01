#ifndef __Interface_Disassembler_H__
#define __Interface_Disassembler_H__

#include "instruction.h"
#include "types.h"
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

class InterfaceDisassembler {
public:
  virtual void Decode(const unsigned char *code, size_t size) = 0;
  virtual void Clear() = 0;
  virtual ~InterfaceDisassembler(){};
  virtual const std::vector<Instruction> &getInstructions() const = 0;
};

class AbstractDisassembler : public InterfaceDisassembler {
public:
  virtual ~AbstractDisassembler() {}
  friend std::ostream &operator<<(std::ostream &out,
                                  const AbstractDisassembler &aDis);

  virtual const std::vector<Instruction> &getInstructions() const {
    return instructions;
  }

  virtual void Clear() { instructions.clear(); }

protected:
  std::vector<Instruction> instructions;
};

inline std::ostream &operator<<(std::ostream &out,
                                const AbstractDisassembler &aDis) {
  auto instructions = aDis.instructions;
  out << "Instruction count: " << instructions.size() << std::endl;
  out << "address | opcode | operands" << std::endl;
  out << "---------------------------" << std::endl;
  for (size_t i = 0; i < instructions.size(); i++) {
    out << instructions[i] << std::endl;
  }
  return out;
}

#endif // __Interface_Disassembler_H__
