// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "binaryDisassemble.h"
#include "disassemble.h"
#include "interfaces/helpers.h"
#include "interfaces/types.h"
#include "parser.h"

void BinaryDisassemble::disassemble(const Binary &binary,
                                    std::vector<Instruction> &instructions,
                                    DisassemblerType dtype) {
  std::unique_ptr<AbstractDisassembler> disasm =
      BinaryDisassemble::disassemble(binary, dtype);
  disasm->moveInstructions(instructions);
}

std::unique_ptr<AbstractDisassembler>
BinaryDisassemble::disassemble(const Binary &binary, DisassemblerType dtype) {
  Disassembler disasm(binary.Arch(), dtype);
  disasm.setStartAddress(binary.getStartAddress());
  disasm.Decode(binary.Instructions().data(), binary.Instructions().size());
  return disasm.getDisam();
}

std::unique_ptr<AbstractDisassembler>
BinaryDisassemble::disassemble(const std::string &filename,
                               const std::string &dynamicLibPaths) {
  std::unique_ptr<Binary> binary = ASMParser::Parser(filename);
  DisassemblerType dType =
      Disassembler::checkAndInitDynamicDisassemblers(dynamicLibPaths);
  return BinaryDisassemble::disassemble(*(binary.get()), dType);
}

bool BinaryDisassemble::action(const std::string &filename,
                               const std::string &dynamicLibPaths,
                               std::ostream &out) {
  std::unique_ptr<Binary> binary = ASMParser::Parser(filename);

  auto disasm = disassemble(filename, dynamicLibPaths);

  out << *(binary.get()) << std::endl;
  out << *(disasm.get()) << std::endl;
  return true;
}