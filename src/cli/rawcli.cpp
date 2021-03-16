// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "rawcli.h"
#include "runtime/rawDisassemble.h"

const std::string RawCLI::name = "r";
const std::string RawCLI::altName = "raw";
const std::string RawCLI::description = "Dissassemble the raw bytes";

RawCLI::RawCLI(int argc, char **argv) : BaseCLI(argc, argv) {
  configure_parser();
  // NOTE Needs to be run after configure_parser and property initalization
  parser.run_and_exit_if_error(); // TODO: figure out how to abstract this so
                                  // its only in BaseCLI

  this->arch = parser.get<std::string>("a");
  this->assembly = parser.get<std::string>("i");
  this->dynamicLibs = parser.get<std::string>("d");
}

RawCLI::~RawCLI() {}

void RawCLI::configure_parser() {
  this->BaseCLI::configure_parser();
  parser.set_required<std::string>("a", "arch", "", "ISA to decode.");
  parser.set_required<std::string>("i", "input",
                                   "input string to disassemble.");
  parser.set_required<bool>(name, altName, description);
  parser.set_optional<std::string>("d", "dynamic", "",
                                   "input to the dynamic lib we want to load.");
}

void RawCLI::executeAction() {
  this->BaseCLI::executeAction();
  RawDisassemble::action(this->assembly, this->arch, this->dynamicLibs);
}