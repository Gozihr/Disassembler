#ifndef __Disassembler_H__
#define __Disassembler_H__

#include "interfaces/pch.h"
#include "interfaces/interfaceDisassembler.h"
#include "interfaces/instruction.h"
#include <iterator>
#include <memory>

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
  void moveInstructions(std::vector<Instruction> &instructions) {
    // pDisasm->moveInstructions(Instructions);
  }
  virtual void Clear() final;

  static DisassemblerType
  checkAndInitDynamicDisassemblers(const std::string &dynamicLibPaths);

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

#endif // __Disassembler_H__
