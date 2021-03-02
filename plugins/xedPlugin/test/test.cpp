// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.


#define CATCH_CONFIG_MAIN

#include "xedDisassembler.h"
#include <catch2/catch.hpp>

TEST_CASE("test 2 instructions") {
  unsigned char assembly[] = "\x55\x48\x8b\x05\xb8\x13\x00\x00";
  XedDisassembler disasm(Archtype::X86_64);
  disasm.Decode(assembly, sizeof(assembly) - 1);
  auto instructions = disasm.getInstructions();
  REQUIRE(instructions[0].opcode == "pushq");
  REQUIRE(instructions[0].operandsStr == "%rbp");
  REQUIRE(instructions[1].opcode == "movq");
  REQUIRE(instructions[1].operandsStr == "0x13b8(%rip), %rax");
}

TEST_CASE("test more instructions") {
  unsigned char assembly[] =
      "\x55\x31\xd2\x89\xe5\x8b\x45\x08\x56\x8b\x75\x0c\x53\x8d\x58\xff\x0f\xb6"
      "\x0c\x16\x88\x4c\x13\x01\x83\xc2\x01\x84\xc9\x75\xf1\x5b\x5e\x5d\xc3";
  XedDisassembler disasm(Archtype::X86_64);
  disasm.Decode(assembly, sizeof(assembly) - 1);
  std::cout << disasm << std::endl;
}