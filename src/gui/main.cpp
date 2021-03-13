// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "imguiGLWindow.h"

int main(int argc, char *argv[]) {

  ImguiGLWindow gWindow("Disasm-Gui");

  gWindow.init();
  gWindow.run();
  exit(EXIT_SUCCESS);
}