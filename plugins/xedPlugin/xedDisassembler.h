#ifndef __Xed_Disassembler_H__
#define __Xed_Disassembler_H__

#include "interfaceDisassembler.h"

class XedDisassembler : public AbstractDisassembler {
    public:
        XedDisassembler(Archtype archType);
        virtual ~XedDisassembler();
        virtual void Decode(const unsigned char *code, int size) final;
};

#endif // __Xed_Disassembler_H__
