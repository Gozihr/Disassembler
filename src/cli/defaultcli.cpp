// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "defaultcli.h"
#include "dataPattern/singleton.h"
#include "interfaces/pch.h"

typedef std::function<void(cli::Parser &parser)> registerCli;
namespace {

struct Singleton_DefaultCLI_Members {
  Singleton_DefaultCLI_Members() {}
  std::vector<registerCli> vecRegisterCLIs;
};
} // namespace

typedef SingletonBase<Singleton_DefaultCLI_Members> Singleton;

DefaultCLI::DefaultCLI(int argc, char **argv) : BaseCLI(argc, argv) {
  configure_parser();
  // NOTE Needs to be run after configure_parser and property initalization
  parser.run(); // TODO: figure out how to abstract this so its only in BaseCLI
}

DefaultCLI::~DefaultCLI() {}

void DefaultCLI::configure_parser() {
  this->BaseCLI::configure_parser();
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  for (const registerCli &rf : instance.vecRegisterCLIs) {
    rf(parser);
  }
}

void DefaultCLI::executeAction() { this->BaseCLI::executeAction(); }

void DefaultCLIMgr::Register(const std::string &name,
                             const std::string &altname,
                             const std::string &description, CLIType type) {
  auto &instance = Singleton::get();
  auto lock(instance.getLock());
  instance.vecRegisterCLIs.push_back([&, type](cli::Parser &parser) {
    switch (type) {
    case CLIType::tBool:
      parser.set_optional<bool>(name, altname, false, description);
      break;
    case CLIType::tString:
      parser.set_optional<std::string>(name, altname, "", description);
      break;
    default:
      throw std::runtime_error("An unexpected CLI flag type was chosen.");
    }
  });
}