#ifndef __Xed_Disassembler_H__
#define __Xed_Disassembler_H__

#include "interfaceDisassembler.h"

struct XedInternal;

class XedDisassembler : public AbstractDisassembler {
    public:
        XedDisassembler(Archtype archType);
        virtual ~XedDisassembler();
        virtual void Decode(const unsigned char *code, int size) final;
    private:
        int decodeInstruction(const unsigned char *code, int size);
        std::unique_ptr<XedInternal> xedInternal;
};

#endif // __Xed_Disassembler_H__
