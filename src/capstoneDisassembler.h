/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __Capstone_Disassembler_H__
#define __Capstone_Disassembler_H__

#include "interfaces/interfaceDisassembler.h"

struct cs_insn;
class CapstoneDisassembler : public AbstractDisassembler {
public:
  CapstoneDisassembler(Archtype archType);
  virtual ~CapstoneDisassembler();
  virtual void Decode(const unsigned char *code, size_t size) final;

private:
  size_t decodeInstruction(const unsigned char *code, size_t size,
                           cs_insn *&insn);
  void freeInstruction(cs_insn *insn, size_t count);
  size_t handle; // csh
};

#endif // __Capstone_Disassembler_H__
