// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <iostream>

#include "instruction.h"
#include "xedDisassembler.h"

extern "C" {
#include "xed/xed-flags.h"
#include "xed/xed-interface.h"
}

struct XedInternal {
  xed_state_t state;
  xed_chip_enum_t chipType = XED_CHIP_ALL;
  XedInternal() {
    xed_state_zero(&state);
    state.mmode = XED_MACHINE_MODE_INVALID;
    state.stack_addr_width = XED_ADDRESS_WIDTH_INVALID;
  }
  XedInternal(xed_machine_mode_enum_t arch,
              xed_address_width_enum_t addr_width) {
    xed_state_zero(&state);
    state.mmode = arch;
    state.stack_addr_width = addr_width;
  }
};

namespace {
XedInternal *pickPlatform(Archtype archType) {
  switch (archType) {
  case Archtype::X86:
    return new XedInternal(XED_MACHINE_MODE_LONG_COMPAT_32,
                           XED_ADDRESS_WIDTH_32b);
    break;
  case Archtype::X86_64:
    return new XedInternal(XED_MACHINE_MODE_LONG_64, XED_ADDRESS_WIDTH_64b);
    break;
  default:
    std::cerr << "unsupported arch" << std::endl;
    throw;
  }
}

std::string printInstruction(const unsigned char *addr,
                             xed_decoded_inst_t *xinstr) {
  char buffer[10000] = {};

  xed_print_info_t pi = {};
  xed_init_print_info(&pi);

  pi.p = xinstr;
  pi.blen = sizeof(buffer);
  pi.buf = buffer;
  pi.runtime_address = (uint64_t)addr;
  pi.syntax = XED_SYNTAX_ATT;

  int ok = xed_format_generic(&pi);
  if (!ok) {
    std::cerr << "can't disassemble" << std::endl;
  }
  return buffer;
}

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string &s) {
  size_t start = s.find_first_not_of(WHITESPACE);
  return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s) {
  size_t end = s.find_last_not_of(WHITESPACE);
  return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s) { return rtrim(ltrim(s)); }

} // namespace

XedDisassembler::XedDisassembler(Archtype archType) {
  // initialize the XED tables -- one time.
  xed_tables_init();
  this->xedInternal = std::unique_ptr<XedInternal>(pickPlatform(archType));
}

XedDisassembler::~XedDisassembler() {}

int XedDisassembler::decodeInstruction(const unsigned char *code) {
  for (int currByte = 1; currByte <= XED_MAX_INSTRUCTION_BYTES; currByte++) {
    xed_decoded_inst_t xedd;
    xed_decoded_inst_zero_set_mode(&xedd, &this->xedInternal->state);
    xed_decoded_inst_set_input_chip(&xedd, this->xedInternal->chipType);
    xed_error_enum_t error = xed_decode(&xedd, code, currByte);
    if (error != XED_ERROR_NONE) {
      // std::cerr << "XED error: " << xed_error_enum_t2str(error) << std::endl;
      continue;
    }
    std::string instruction = ::printInstruction(code, &xedd);
    size_t split = instruction.find(' ');
    std::string opcode = instruction.substr(0, split);
    std::string strOperands = ::trim(instruction.substr(split + 1));
    instructions.push_back(Instruction(0, opcode, strOperands));
    return currByte;
  }
  return -1;
}

void XedDisassembler::Decode(const unsigned char *code, size_t size) {
  size_t currCount = 0;
  unsigned char *currInst = const_cast<unsigned char *>(code);
  while (currCount < size) {
    size_t count = decodeInstruction(currInst);
    if (count == -1) {
      break;
    }

    // NOTE: this will work if we are printing out all the instructions
    // it will breakdown after the per function disassemble feature.
    // TODO investigate how to get instruction address using XED
    if (instructions.size() > 0) {
      instructions[instructions.size() - 1].address = startAddress + currCount;
    }
    currInst += count;
    currCount += count;
  }
}