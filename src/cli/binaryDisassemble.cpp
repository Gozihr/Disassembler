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
  std::cout << "filename: " << filename << std::endl;
  ASMParser asmParser(filename);
  std::cout << "OS: " << asmParser.OS() << std::endl;
  std::cout << "ISA: " << asmParser.Arch() << std::endl;
  std::cout << "Text section size: " << asmParser.Instructions().size()
            << std::endl;

  DisassemblerType dType =
      Disassembler::checkAndInitDynamicDisassemblers(dynamicLibPaths);

  Disassembler disasm(asmParser.Arch(), dType);
  disasm.Decode(asmParser.Instructions().data(),
                asmParser.Instructions().size());

  std::cout << disasm << std::endl;

  return true;
}