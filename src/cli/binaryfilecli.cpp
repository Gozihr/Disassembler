// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "binaryfilecli.h"
#include "runtime/binaryDisassemble.h"

const std::string BinaryFileCLI::name = "b";
const std::string BinaryFileCLI::altName = "binary";
const std::string BinaryFileCLI::description =
    "Dissassemble a native executable";

BinaryFileCLI::BinaryFileCLI(int argc, char **argv) : BaseCLI(argc, argv) {
  configure_parser();
  // NOTE Needs to be run after configure_parser and property initalization
  parser.run_and_exit_if_error(); // TODO: figure out how to abstract this so
                                  // its only in BaseCLI
  this->filename = parser.get<std::string>("f");
  this->dynamicLibs = parser.get<std::string>("d");
}

BinaryFileCLI::~BinaryFileCLI() {}

void BinaryFileCLI::configure_parser() {
  this->BaseCLI::configure_parser();
  parser.set_required<std::string>("f", "filename",
                                   "input file to disassemble.");
  parser.set_required<bool>(name, altName, description);
  parser.set_optional<std::string>("d", "dynamic", "",
                                   "input to the dynamic lib we want to load.");
}

void BinaryFileCLI::executeAction() {
  this->BaseCLI::executeAction();
  BinaryDisassemble::action(this->filename, this->dynamicLibs);
}