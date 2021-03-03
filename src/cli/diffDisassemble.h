/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __diff_disassemble_h__
#define __diff_disassemble_h__

#include <string>

class DiffDisassemble {
private:
  DiffDisassemble() = delete;

public:
  static bool action(std::string jsonConfigFilePath);
};

#endif // __raw_disassemble_h__