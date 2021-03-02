/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __diff_h__
#define __diff_h__

#include "interfaces/types.h"

struct DiffConfig {
  Config config1;
  Config config2;
  bool perLineDiff = false;
};

class DiffTool {
private:
  DiffConfig config;

public:
  DiffTool(DiffConfig &dconfig);
  void compute();
};

#endif //__diff_h__