/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __config_cli_h__
#define __config_cli_h__

#include "basecli.h"

class ConfigCLI : public BaseCLI {
public:
  static const std::string name;
  static const std::string altName;
  static const std::string description;

protected:
  virtual void configure_parser() override;

public:
  ConfigCLI(int argc, char **argv);
  virtual ~ConfigCLI();
  virtual void executeAction() override final;

private:
  std::string jsonConfigFilePath;
};

#endif // __config_cli_h__