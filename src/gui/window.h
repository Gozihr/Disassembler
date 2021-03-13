/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <functional>
#include <memory>
#include <string>
#include <vector>

typedef std::function<void()> drawCallBack;

class Window {
protected:
  size_t mWidth, mHeight;
  std::string mTitle;
  std::vector<drawCallBack> drawFunctors;
  virtual void draw();

public:
  Window(std::string title, size_t width, size_t height);
  virtual void init() = 0;
  virtual void run() = 0;
  size_t Width() const { return mWidth; }
  size_t Height() const { return mHeight; }
  std::string Title() const { return mTitle; }

  void insertDrawCallback(drawCallBack &db);
  const std::vector<drawCallBack> &getDrawCallBacks();
};

#endif // __WINDOW_H__