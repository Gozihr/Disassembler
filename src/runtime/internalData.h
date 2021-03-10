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
};

#endif //__internal_data_h__