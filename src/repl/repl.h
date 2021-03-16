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
};

#endif //__repl_h__