/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __base_cli_h__
#define __base_cli_h__

#include <cmdParser/cmdparser.hpp>
#include <version/version.h>

class BaseCLI {
protected:
  cli::Parser parser;
  // TODO add verbose logging move this to a
  // singleton.
  bool shouldLogVerbose = false;
  BaseCLI(int argc, char **argv) : parser(argc, argv) {}

  virtual void configure_parser() {
    parser.set_optional<bool>("v", "verbose", false, "print verbose");
    parser.set_optional<bool>("V", "version", false, "print version");
  }

public:
  virtual ~BaseCLI() {}
  virtual void executeAction() {
    shouldLogVerbose = parser.get<bool>("v");
    if (parser.get<bool>("V")) {
      Gozihr::printVersion();
      exit(0);
    }
  }
};

#endif //__base_cli_h__