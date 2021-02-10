#ifndef __Capstone_Disassembler_H__
#define __Capstone_Disassembler_H__

#include "disassemble.h"

struct cs_insn;
class CapstoneDisassembler : public AbstractDisassembler {
public:
  CapstoneDisassembler(Archtype archType);
  virtual ~CapstoneDisassembler();
  virtual void Decode(const unsigned char *code, size_t size) final;

private:
  size_t decodeInstruction(const unsigned char *code, size_t size,
                           cs_insn *&insn);
  void freeInstruction(cs_insn *insn, size_t count);
  size_t handle; // csh
};

#endif // __Capstone_Disassembler_H__
