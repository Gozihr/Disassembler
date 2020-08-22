#include "xedDisassembler.h"

namespace {
    void pickPlatform(Archtype archType) {
        switch(archType) {
            case Archtype::ARM64:
                throw;
                break;
            case Archtype::X86:
                break;
            case Archtype::X86_64:
                break;
        }
    }
}

XedDisassembler::XedDisassembler(Archtype archType)
{
    pickPlatform(archType);
}

XedDisassembler::~XedDisassembler(){
}

void XedDisassembler::Decode(const unsigned char *code, int size) {
}