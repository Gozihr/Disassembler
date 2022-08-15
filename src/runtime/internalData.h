/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __internal_data_h__
#define __internal_data_h__

#include <memory>

#include <LIEF/ELF/Binary.hpp>
#include <LIEF/MachO/Binary.hpp>
#include <LIEF/PE/Binary.hpp>

struct BinaryTypes {
  std::unique_ptr<LIEF::ELF::Binary> elf;
  std::unique_ptr<LIEF::PE::Binary> pe;
  std::unique_ptr<LIEF::MachO::Binary> machO;
};

struct BinaryInternal {
  BinaryInternal() {}
  BinaryTypes binary;
  std::vector<std::string> funcNames;
  void setElf(std::unique_ptr<LIEF::ELF::Binary> &elf) {
    binary.elf = std::move(elf);
  }
  void setPE(std::unique_ptr<LIEF::PE::Binary> &pe) {
    binary.pe = std::move(pe);
  }
  void setMachO(std::unique_ptr<LIEF::MachO::Binary> &machO) {
    binary.machO = std::move(machO);
  }
  void setMachO(LIEF::MachO::Binary *machO) {
    binary.machO = std::unique_ptr<LIEF::MachO::Binary>(machO);
  }
  LIEF::Binary::functions_t functions() {
    if (binary.elf) {
      return binary.elf->functions();
    }
    if (binary.pe) {
      return binary.pe->functions();
    }
    if (binary.machO) {
      return binary.machO->functions();
    }
  }
  std::vector<std::string> &functionNames() {
    auto funcs = functions();
    if (funcNames.empty()) {
      auto getFuncName = [](LIEF::Function &func) { return func.name(); };
      std::transform(funcs.begin(), funcs.end(), std::back_inserter(funcNames),
                     getFuncName);
    }
    return funcNames;
  }
};

#endif //__internal_data_h__