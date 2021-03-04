/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __linux_factory_h__
#define __linux_factory_h__

#include "abstractOSFactory.h"

#include <gmodule.h>

class LinuxSOLoad : public ILoad {
private:
  GModule *mGmodule = nullptr;
  function_union mSOLibFunctions;

public:
  LinuxSOLoad() : ILoad() {}
  virtual bool LoadLibraryFromPath(std::string sLoadPath) override;
  virtual function_union &getLoadedLibrary() override;
  ~LinuxSOLoad();
};

class LinuxFactory : public AbstractOSFactory {
public:
  virtual Load_ptr getLoadLib() final;
};

#endif // __linux_factory_h__