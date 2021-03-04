/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __auto_cli_h__
#define __auto_cli_h__

#include "basecli.h"
#include <memory>

class AutoCLI {
private:
  std::unique_ptr<BaseCLI> CliParser;
  void initParser(int argc, char **argv);

public:
  AutoCLI(int argc, char **argv);
};

#endif //__auto_cli_h__