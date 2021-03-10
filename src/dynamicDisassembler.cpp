// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "dynamicDisassembler.h"
#include "pluginInfra/dynamicLibMgr.h"

DynamicDisassembler::DynamicDisassembler(Archtype archType) {
  DynamicLibMgr::initalize(archType);
}

DynamicDisassembler::~DynamicDisassembler() {
  AbstractDisassembler::Clear();
  Clear();
}

void DynamicDisassembler::Decode(const unsigned char *code, size_t size) {
  DynamicLibMgr::decode(code, size);
  AbstractDisassembler::Clear();
  DynamicLibMgr::getInstructions(mInstructions);
}

void DynamicDisassembler::Clear() { DynamicLibMgr::clear(); }