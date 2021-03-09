/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __runtime_h__
#define __runtime_h__

#include "interfaces/pch.h"
#include "interfaces/types.h"

enum class RuntimeTypes { DLIB, BINARY, SECTIONS };

class DynamicLibrary {
private:
  std::string mPath;

public:
  DynamicLibrary(std::string path) : mPath(path) {}
  std::string Path() const { return mPath; }
};

union BinaryInternal;

class Binary {
private:
  std::string mPath;
  OStype os = OStype::UNKNOWN;
  Archtype arch = Archtype::UNKNOWN;
  std::vector<uint8_t> mInstructions;
  BinaryInternal *mBinaryInternal;

public:
  Binary(std::string path) : mPath(path) {}
  std::string Path() const { return mPath; }
  // std::vector<Section> GetSections();
  Archtype Arch() const { return arch; }
  OStype OS() const { return os; }
  const std::vector<uint8_t> &Instructions() const;
  friend class ASMParser;
};

inline std::ostream &operator<<(std::ostream &out, const DynamicLibrary &dLib) {
  out << dLib.Path() << std::endl;
  return out;
}

#endif // __runtime_h__