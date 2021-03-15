// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "difftool.h"
#include "disassemble.h"
#include "interfaces/pch.h"
#include "myers-diff/myersDiff.hpp"
#include "parser.h"

namespace {
void GetInstructions(const jObjects::Config &config,
                     std::vector<Instruction> &instructions) {
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
    auto binary = ASMParser::Parser(config.binaryPath);
    Disassembler disasm(binary->Arch(), dType);
    disasm.Decode(binary->Instructions().data(), binary->Instructions().size());
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

bool DiffTool::action(const jObjects::Config &config1,
                      const jObjects::Config &config2) {
  std::stringstream ss1;
  std::vector<Instruction> instructions;
  GetInstructions(config1, instructions);
  ss1 << instructions;
  std::string left = ss1.str();

  GetInstructions(config2, instructions);
  std::stringstream ss2;
  ss2 << instructions;
  std::string right = ss2.str();

  auto strPair = Diff::compute(left, right);
  std::cout << strPair.first << "\n" << strPair.second;
  return true;
}

DiffOutput DiffTool::action(std::vector<Instruction> &inst1,
                            std::vector<Instruction> &inst2) {
  std::stringstream ss1;
  ss1 << inst1;
  std::stringstream ss2;
  ss2 << inst2;
  std::string left = ss1.str();
  std::string right = ss2.str();
  return Diff::compute(left, right);
}