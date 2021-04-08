/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __IMGUI_GL_WINDOW_H__
#define __IMGUI_GL_WINDOW_H__

#include "glfwWindow.h"
#include "interfaces/interfaceDisassembler.h"

class GozihrWindow {
public:
  bool gozihr_active;
  std::string filePath;
  std::string binary;
  std::unique_ptr<AbstractDisassembler> pDisasm;
  GozihrWindow() : gozihr_active(true) {}
  void Draw();
  void Disassemble(std::string binaryPath, std::string pluginPath = "");
};

class ImguiGLWindow : public GLWindow {
private:
  std::unique_ptr<GozihrWindow> mGozihrWindow;

public:
  ImguiGLWindow(std::string title, int width = 640, int height = 480);
  virtual void init() final;
  virtual void draw() final;
};

#endif // __IMGUI_GL_WINDOW_H__