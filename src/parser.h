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
private:
  ASMParser() = delete;

public:
  static std::unique_ptr<Binary> Parser(std::string filename);
};

#endif // __Parser_H__