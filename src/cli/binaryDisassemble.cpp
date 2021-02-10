#include "binaryDisassemble.h"
#include "disassemble.h"
#include "parser.h"
#include <iostream>

bool BinaryDisassemble::action(std::string filename) {
  ASMParser asmParser(filename);
  std::cout << "OS: " << asmParser.OS() << std::endl;
  std::cout << "ISA: " << asmParser.Arch() << std::endl;
  std::cout << "Text section size: " << asmParser.Instructions().size()
            << std::endl;
  Disassembler disasm(asmParser.Arch());
  disasm.Decode(asmParser.Instructions().data(),
                asmParser.Instructions().size());

  std::cout << disasm << std::endl;

  return true;
}