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
    InterfaceDisassembler() {
    pDisasm = std::unique_ptr<AbstractDisassembler>(pickDisam(archtype, disamType));
}

void Disassembler::Decode(const unsigned char *code, size_t size) {
    pDisasm->Decode(code,size);
}

void Disassembler::Clear() {
    pDisasm->Clear();
}