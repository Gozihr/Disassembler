// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "autocli.h"
#include "runtime/ansiConsole.h"

int main(int argc, char **argv) {
  ansiColors::enableAnsiColors();
  AutoCLI parser(argc, argv);
  return 0;
}