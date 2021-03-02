// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "interfaces/pch.h"
#include "diff.h"
#include "disassemble.h"
#include "myers-diff/myersDiff.hpp"
#include "parser.h"

DiffTool::DiffTool(DiffConfig &dconfig) : config(dconfig) {}

namespace {
void GetInstructions(Config &config, std::vector<Instruction> &instructions) {
  DisassemblerType dType =
      Disassembler::checkAndInitDynamicDisassemblers(config.libpath);
  if (config.binaryPath.empty() && config.rawAsm.empty() &&
      config.arch.empty()) {
    std::cerr << "Error: Config needs either a binary path or raw data and "
                 "architecute type."
              << std::endl;
    return;
  } else if (!config.binaryPath.empty() && !config.rawAsm.empty() &&
             !config.arch.empty()) {
    std::cerr << "Error: Pick either binary or raw ASM disassembly."
              << std::endl;
    return;
  } else if (!config.binaryPath.empty()) {
    ASMParser asmParser(config.binaryPath);
    Disassembler disasm(asmParser.Arch(), dType);
    disasm.Decode(asmParser.Instructions().data(),
                  asmParser.Instructions().size());
    disasm.moveInstructions(instructions);

  } else if (!config.rawAsm.empty() && config.arch.empty()) {
    std::cerr
        << "Error: Raw Assembly requires an architecture type to be provided."
        << std::endl;
    return;
  } else {
    assert(!config.rawAsm.empty() && !config.arch.empty());
    Archtype arch = LookupHelpers::ArchFind(config.arch);
    if (arch == Archtype::UNKNOWN) {
      std::cerr << "Error: An unknown architecture was provided." << std::endl;
      return;
    }
    Disassembler disasm(arch, dType);
    std::vector<unsigned char> bytesArr;
    bytesArr = StringHelpers::HexToBytesFormat(config.rawAsm);
    disasm.Decode(bytesArr.data(), bytesArr.size());
    disasm.moveInstructions(instructions);
  }
}
} // namespace

void DiffTool::compute() {
  std::stringstream ss;
  std::vector<Instruction> instructions;
  GetInstructions(config.config1, instructions);
  ss << instructions;
  std::string left = ss.str();
  ss.clear();
  GetInstructions(config.config2, instructions);
  ss << instructions;
  std::string right = ss.str();
  auto strPair = Diff::compute(left,right);
  std::cout << strPair.first << " | " << strPair.second;
}