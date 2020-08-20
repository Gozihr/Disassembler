#include "disassemble.h"
#include "capstoneDisassembler.h"

namespace {
    AbstractDisassembler* pickDisam(Archtype archType, DisassemblerType disamType) {
        switch(disamType) {
            case DisassemblerType::CAPSTONE: {
                return new CapstoneDisassembler(archType);
            }
        }
        return nullptr;
    }
}

Disassembler::Disassembler(Archtype archtype, DisassemblerType disamType) :
    InterFaceDisassembler() {
    pDisasm = std::unique_ptr<AbstractDisassembler>(pickDisam(archtype, disamType));
}

void Disassembler::Decode(const unsigned char *code, int size) {
    pDisasm->Decode(code,size);
}

void Disassembler::Clear() {
    pDisasm->Clear();
}

void AbstractDisassembler::Clear() {
    mnemonic.clear();
    opCodes.clear();
}