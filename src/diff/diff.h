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