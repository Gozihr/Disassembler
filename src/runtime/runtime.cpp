#include "runtime.h"
#include <memory>

#include "internalData.h"

const std::vector<uint8_t> &Binary::Instructions() const {
  return mInstructions;
}