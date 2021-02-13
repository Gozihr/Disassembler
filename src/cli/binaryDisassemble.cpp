#include "binaryDisassemble.h"
#include "disassemble.h"
#include "parser.h"
#include "pluginInfra/dynamicLibMgr.h"
#include <iostream>
#include "interfaces/helpers.h"
#include "interfaces/types.h"

bool BinaryDisassemble::action(const std::string &filename, 
                               const std::string &dynamicLibPaths) {
  ASMParser asmParser(filename);
  std::cout << "OS: " << asmParser.OS() << std::endl;
  std::cout << "ISA: " << asmParser.Arch() << std::endl;
  std::cout << "Text section size: " << asmParser.Instructions().size()
            << std::endl;
  
  DisassemblerType dType = DisassemblerType::CAPSTONE;
  if(!dynamicLibPaths.empty()) {
    std::vector<std::string> vecDynamicLibPaths = Helpers::Split(dynamicLibPaths);
    DynamicLibMgr::loadDynamicLibs(vecDynamicLibPaths);
    dType = DisassemblerType::DYNAMIC;
  }
  Disassembler disasm(asmParser.Arch(), dType);
  disasm.Decode(asmParser.Instructions().data(),
                asmParser.Instructions().size());

  std::cout << disasm << std::endl;

  return true;
}