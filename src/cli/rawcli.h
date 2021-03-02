/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __raw_cli_h__
#define __raw_cli_h__

#include "basecli.h"
#include "rawDisassemble.h"

class RawCLI : public BaseCLI {
public:
  static const std::string name;
  static const std::string altName;
  static const std::string description;

protected:
  RawDisassemble m_disassemble;
  virtual void configure_parser() override;

public:
  RawCLI(int argc, char **argv);
  virtual ~RawCLI();
  virtual void executeAction() override final;

private:
  std::string arch;
  std::string assembly;
  std::string dynamicLibs;
};

#endif // __raw_cli_h__