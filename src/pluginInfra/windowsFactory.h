/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __windows_factory_h__
#define __windows_factory_h__

#include "abstractOSFactory.h"
#include <wtypes.h>

class WindowsDLibLoad : public ILoad {
private:
  HINSTANCE mProcHinstance;
  function_union mDllFunctions;

public:
  WindowsDLibLoad() : ILoad(), mProcHinstance(nullptr) {
    memset(&mDllFunctions, 0, sizeof(mDllFunctions));
  }
  virtual bool LoadLibraryFromPath(std::string sLoadPath) override;
  virtual function_union &getLoadedLibrary() override;
  ~WindowsDLibLoad();
};

class WindowsFactory : public AbstractOSFactory {
public:
  virtual Load_ptr getLoadLib() final;
};

#endif //__windows_factory_h__