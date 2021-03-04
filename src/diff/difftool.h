/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __diff_tool_h__
#define __diff_tool_h__

#include "interfaces/jsonHelper.h"
#include "interfaces/types.h"

class DiffTool {
private:
  DiffTool() = delete;

public:
  static bool action(const jObjects::Config &config1,
                     const jObjects::Config &config2);
};

#endif //__diff_tool_h__