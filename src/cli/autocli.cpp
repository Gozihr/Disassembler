// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "autocli.h"
#include "binaryfilecli.h"
#include "rawcli.h"

AutoCLI::AutoCLI(int argc, char **argv) {
  initParser(argc, argv);

  if (CliParser) {
    CliParser->executeAction();
  }
}

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
}