#include "runtime.h"

#include <memory>

#include "runtime/internalData.h"

const std::vector<uint8_t> &Binary::Instructions() const {
  return mInstructions;
}

Binary::Binary(std::string path) : mPath(path) {
  mBinaryInternal = std::make_unique<BinaryInternal>();
}

Binary::~Binary() {}