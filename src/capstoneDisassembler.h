#ifndef __Capstone_Disassembler_H__
#define __Capstone_Disassembler_H__

#include "disassemble.h"

struct cs_insn;
class CapstoneDisassembler : public AbstractDisassembler {
    public:
        CapstoneDisassembler(Archtype archType);
        virtual ~CapstoneDisassembler();
        virtual void Decode(const unsigned char *code, int size) final;
    private:
        int decodeInstruction(const unsigned char *code, int size, cs_insn *&insn);
        void freeInstruction(cs_insn *insn, int count);
        size_t handle; //csh
};

#endif // __Capstone_Disassembler_H__
