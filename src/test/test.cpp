
#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "disassemble.h"

TEST_CASE( "test 2 instructions" ) {
    unsigned char assembly[] = "\x55\x48\x8b\x05\xb8\x13\x00\x00";
    Disassembler disasm(Archtype::X86_64, DisassemblerType::CAPSTONE);
    disasm.Decode(assembly, sizeof(assembly)-1);
    auto operands = disasm.getOperands();
    auto opCodes  = disasm.getOpCodes();
    REQUIRE( opCodes[0] == "push" );
    REQUIRE( operands[0] == "rbp" );
    REQUIRE( opCodes[1] == "mov" );
    REQUIRE( operands[1] == "rax, qword ptr [rip + 0x13b8]" );
}

TEST_CASE( "test more instructions" ) {
    unsigned char assembly[] = "\x55\x31\xd2\x89\xe5\x8b\x45\x08\x56\x8b\x75\x0c\x53\x8d\x58\xff\x0f\xb6\x0c\x16\x88\x4c\x13\x01\x83\xc2\x01\x84\xc9\x75\xf1\x5b\x5e\x5d\xc3";
    Disassembler disasm(Archtype::X86_64, DisassemblerType::CAPSTONE);
    disasm.Decode(assembly, sizeof(assembly)-1);
    std::cout << disasm << std::endl;
}