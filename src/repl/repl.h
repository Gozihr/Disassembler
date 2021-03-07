/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __repl_h__
#define __repl_h__

#include <string>

class Repl {
private:
  Repl() = delete;

public:
  static void run();
  static std::string name();
  static std::string version();
};

#endif //__repl_h__