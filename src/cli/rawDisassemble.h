/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */


#ifndef __raw_disassemble_h__
#define __raw_disassemble_h__

#include <string>

class RawDisassemble {
public:
  RawDisassemble() {}

public:
  virtual bool action(std::string assembly, std::string arch,
                      const std::string &dynamicLibPaths);
};

#endif // __raw_disassemble_h__