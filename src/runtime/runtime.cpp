// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "runtime.h"

#include <memory>

#include "runtime/internalData.h"

const std::vector<uint8_t> &Binary::Instructions() const {
  return mInstructions;
}

Binary::Binary(std::string path) : mPath(path) {
  mBinaryInternal = std::make_unique<BinaryInternal>();
}

std::vector<std::string> &Binary::functionNames() {
  return mBinaryInternal->functionNames();
}

Binary::~Binary() {}