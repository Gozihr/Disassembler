/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __Parser_H__
#define __Parser_H__

#include "interfaces/pch.h"
#include "interfaces/types.h"
#include "runtime/runtime.h"

class ASMParser {
public:
  ASMParser(std::string filename);
  Archtype Arch() const { return mBinary.arch; }
  OStype OS() const { return mBinary.os; }
  const std::vector<uint8_t> &Instructions() const {
    return mBinary.Instructions();
  }

private:
  Binary mBinary;
  void elfParser();
  void peParser();
  void machOParser();
};

#endif // __Parser_H__