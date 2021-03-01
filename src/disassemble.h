#ifndef __Disassembler_H__
#define __Disassembler_H__

#include "interfaces/instruction.h"
#include "interfaces/interfaceDisassembler.h"
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

enum class DisassemblerType { CAPSTONE, DYNAMIC };

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
  virtual void Clear() final;

private:
  std::unique_ptr<AbstractDisassembler> pDisasm;
};

template <typename T>
inline std::ostream &operator<<(std::ostream &out, const std::vector<T> &v) {
  if (!v.empty()) {
    out << '[';
    std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
    out << "\b\b]";
  }
  return out;
}

inline std::ostream &operator<<(std::ostream &out, const Disassembler &aDis) {
  if (aDis.pDisasm.get()) {
    out << *(aDis.pDisasm.get()) << std::endl;
  }
  return out;
}

/*inline std::ostream &operator<<(std::ostream &out,
                                const Disassembler &aDis) {
  auto instructions = aDis.pDisasm->getInstructions();
  out << "Instruction count: " << instructions.size() << std::endl;
  for (size_t i = 0; i < instructions.size(); i++) {
    out << instructions[i] << std::endl;
  }
  return out;
}*/

#endif // __Disassembler_H__
