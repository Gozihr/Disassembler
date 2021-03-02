// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.


#include "disassemble.h"
#include <algorithm>
#include <bitset>

#include "interfaces/pch.h"
#include "interfaces/helpers.h"
#include "interfaces/types.h"
#include "rawDisassemble.h"

bool RawDisassemble::action(std::string assembly, std::string arch,
                            const std::string &dynamicLibPaths) {
  std::vector<unsigned char> bytesArr;
  bytesArr = StringHelpers::HexToBytesFormat(assembly);

  DisassemblerType dType =
      Disassembler::checkAndInitDynamicDisassemblers(dynamicLibPaths);

  Archtype archType = LookupHelpers::ArchFind(arch);
  if (archType == Archtype::UNKNOWN) {
    return false;
  }
  Disassembler disasm(archType, dType);
  disasm.Decode(bytesArr.data(), bytesArr.size());

  std::cout << disasm << std::endl;

  return true;
}