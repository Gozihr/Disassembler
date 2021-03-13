/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __GLFW_WINDOW_H__
#define __GLFW_WINDOW_H__

#include "window.h"

struct GLFWwindow;
typedef std::function<void(GLFWwindow *, int, int, int, int)> keyCallBack;

class GLWindow : public Window {
private:
  GLFWwindow *pGlfwWindow;
  std::vector<keyCallBack> keyCallBacks;
  void glInit();

public:
  static constexpr const char *glslVersion = "#version 330";
  GLWindow(std::string title, int width, int height);
  GLFWwindow *getGLFWwindow();
  const std::vector<keyCallBack> &getKeyCallBacks();
  void insertKeyCallback(keyCallBack &kb);
  virtual void init();
  virtual void run() final;
  virtual ~GLWindow();
};

#endif // __GLFW_WINDOW_H__