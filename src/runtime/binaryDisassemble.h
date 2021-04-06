/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __binary_disassemble_h__
#define __binary_disassemble_h__

#include "interfaces/pch.h"
#include "runtime.h"

struct Instruction;

class BinaryDisassemble {
private:
  BinaryDisassemble() = delete;

public:
  static void disassemble(const Binary &binary,
                          std::vector<Instruction> &instructions);
  static bool action(const std::string &filename,
                     const std::string &dynamicLibPaths,
                     std::ostream &out = std::cout);
};

#endif // __binary_disassemble_h__