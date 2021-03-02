// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "capstoneDisassembler.h"
#include "interfaces/instruction.h"
#include <capstone/capstone.h>
struct platform {
  cs_arch arch;
  cs_mode mode;
};

namespace {
void pickPlatform(Archtype archType, platform &pf) {
  switch (archType) {
  case Archtype::ARM64:
    pf = {CS_ARCH_ARM64, CS_MODE_ARM};
    break;
  case Archtype::X86:
    pf = {CS_ARCH_X86, CS_MODE_32};
    break;
  case Archtype::X86_64:
    pf = {CS_ARCH_X86, CS_MODE_64};
    break;
  default:
    std::cerr << "unsupported arch" << std::endl;
    throw;
  }
}
} // namespace

CapstoneDisassembler::CapstoneDisassembler(Archtype archType) {
  platform pf;
  pickPlatform(archType, pf);
  cs_err err = cs_open(pf.arch, pf.mode, &handle);
  if (err) {
    std::cerr << "Failed on cs_open with error: " << err << std::endl;
    return;
  }
  cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);
}

CapstoneDisassembler::~CapstoneDisassembler() { cs_close(&handle); }

void CapstoneDisassembler::Decode(const unsigned char *code, size_t size) {

  cs_insn *insn = nullptr;
  size_t count = decodeInstruction(code, size, insn);
  if (count > 0) {
    for (size_t i = 0; i < count; i++) {
      instructions.push_back(
          Instruction(insn[i].address, insn[i].mnemonic, insn[i].op_str));
    }
  }
  freeInstruction(insn, count);
}

size_t CapstoneDisassembler::decodeInstruction(const unsigned char *code,
                                               size_t size, cs_insn *&insn) {
  size_t count;
  count = cs_disasm(handle, code, size, 0, 0, &insn);
  return count;
}
void CapstoneDisassembler::freeInstruction(cs_insn *insn, size_t count) {
  cs_free(insn, count);
}