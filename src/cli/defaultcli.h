/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __defaul_cli_h__
#define __defaul_cli_h__

#include "basecli.h"

enum class CLIType : uint8_t { tBool, tString };

class DefaultCLI : public BaseCLI {

protected:
  virtual void configure_parser() override;

public:
  DefaultCLI(int argc, char **argv);
  virtual ~DefaultCLI();
  virtual void executeAction() override final;
};

class DefaultCLIMgr {
private:
  DefaultCLIMgr() = delete;

public:
  static void Register(const std::string &name, const std::string &altname,
                       const std::string &description, CLIType type);
};

#endif // __defaul_cli_h__