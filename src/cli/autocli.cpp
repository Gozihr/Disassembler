// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "autocli.h"
#include "binaryfilecli.h"
#include "configcli.h"
#include "defaultcli.h"
#include "rawcli.h"
#include "replcli.h"

AutoCLI::AutoCLI(int argc, char **argv) {
  initParser(argc, argv);

  if (CliParser) {
    CliParser->executeAction();
  }
}
namespace {
void Register() {
  DefaultCLIMgr::Register(BinaryFileCLI::name, BinaryFileCLI::altName,
                          BinaryFileCLI::description, CLIType::tBool);
  DefaultCLIMgr::Register(ConfigCLI::name, ConfigCLI::altName,
                          ConfigCLI::description, CLIType::tString);
  DefaultCLIMgr::Register(RawCLI::name, RawCLI::altName, RawCLI::description,
                          CLIType::tBool);
  DefaultCLIMgr::Register(ReplCLI::name, ReplCLI::altName, ReplCLI::description,
                          CLIType::tBool);
}
} // namespace
void AutoCLI::initParser(int argc, char **argv) {
  cli::Parser parser(argc, argv);

  if (parser.doesArgumentExist(RawCLI::name, "--" + RawCLI::altName)) {
    CliParser = std::unique_ptr<BaseCLI>(new RawCLI(argc, argv));
    return;
  }

  if (parser.doesArgumentExist(BinaryFileCLI::name,
                               "--" + BinaryFileCLI::altName)) {
    CliParser = std::unique_ptr<BaseCLI>(new BinaryFileCLI(argc, argv));
    return;
  }

  if (parser.doesArgumentExist(ConfigCLI::name, "--" + ConfigCLI::altName)) {
    CliParser = std::unique_ptr<BaseCLI>(new ConfigCLI(argc, argv));
    return;
  }

  if (parser.doesArgumentExist(ReplCLI::name, "--" + ReplCLI::altName)) {
    CliParser = std::unique_ptr<BaseCLI>(new ReplCLI(argc, argv));
    return;
  }

  ::Register();
  CliParser = std::unique_ptr<BaseCLI>(new DefaultCLI(argc, argv));
}