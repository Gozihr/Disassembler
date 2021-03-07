// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "replcli.h"
#include "interfaces/pch.h"
#include "repl/repl.h"

const std::string ReplCLI::name = "R";
const std::string ReplCLI::altName = "repl";
const std::string ReplCLI::description = "Starts a Run-Eval-Print-Loop";

ReplCLI::ReplCLI(int argc, char **argv) : BaseCLI(argc, argv) {
  configure_parser();
  // NOTE Needs to be run after configure_parser and property initalization
  parser.run(); // TODO: figure out how to abstract this so its only in BaseCLI
}

ReplCLI::~ReplCLI() {}

void ReplCLI::configure_parser() {
  this->BaseCLI::configure_parser();
  parser.set_required<bool>(name, altName, description);
}

void ReplCLI::executeAction() { Repl::run(); }