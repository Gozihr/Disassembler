// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "binaryDisassemble.h"
#include "disassemble.h"
#include "interfaces/helpers.h"
#include "interfaces/types.h"
#include "parser.h"
#include <iostream>

bool BinaryDisassemble::action(const std::string &filename,
                               const std::string &dynamicLibPaths) {
  std::unique_ptr<Binary> binary = ASMParser::Parser(filename);
  std::cout << *(binary.get()) << std::endl;
  DisassemblerType dType =
      Disassembler::checkAndInitDynamicDisassemblers(dynamicLibPaths);

  Disassembler disasm(binary->Arch(), dType);
  disasm.setStartAddress(binary->getStartAddress());
  disasm.Decode(binary->Instructions().data(), binary->Instructions().size());

  std::cout << disasm << std::endl;

  return true;
}