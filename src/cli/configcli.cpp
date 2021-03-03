// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "configcli.h"
#include "interfaces/jsonHelper.h"
#include "interfaces/types.h"
#include "rawDisassemble.h"
#include "binaryDisassemble.h"

const std::string ConfigCLI::name = "c";
const std::string ConfigCLI::altName = "Config";
const std::string ConfigCLI::description =
    "Performs Diff behavior specified by Config";

ConfigCLI::ConfigCLI(int argc, char **argv) : BaseCLI(argc, argv) {
  configure_parser();
  // NOTE Needs to be run after configure_parser and property initalization
  parser.run(); // TODO: figure out how to abstract this so its only in BaseCLI

  this->jsonConfigFilePath = parser.get<std::string>("c");
}

ConfigCLI::~ConfigCLI() {}

void ConfigCLI::configure_parser() {
  this->BaseCLI::configure_parser();
  parser.set_required<std::string>(name, altName, description);
}

void ConfigCLI::executeAction() {
  jObjects::ActionConfig config =
      JsonHelper::readJsonToObj<jObjects::ActionConfig>(this->jsonConfigFilePath);

  ConfigAction cAction = LookupHelpers::ActionFind(config.action);
  jObjects::Config config1 = config.configs.front();
  switch(cAction) {
    case ConfigAction::RAW:
    RawDisassemble::action(config1.rawAsm, config1.arch,
                           config1.libpath);
    break;
    case ConfigAction::BINARY:
    BinaryDisassemble::action(config1.binaryPath, config1.libpath);
    break;
    case ConfigAction::DIFF:
    break;
  }
}