/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __repl_cli_h__
#define __repl_cli_h__

#include "basecli.h"

class ReplCLI : public BaseCLI {
public:
  static const std::string name;
  static const std::string altName;
  static const std::string description;

protected:
  virtual void configure_parser() override;

public:
  ReplCLI(int argc, char **argv);
  virtual ~ReplCLI();
  virtual void executeAction() override final;
};

#endif // __repl_cli_h__