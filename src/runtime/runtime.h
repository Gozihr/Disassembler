/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __runtime_h__
#define __runtime_h__

#include "interfaces/pch.h"
#include "interfaces/types.h"

enum class RuntimeTypes { UNKNOWN, DLIB, BINARY, SECTIONS };

class DynamicLibrary {
private:
  std::string mPath;

public:
  DynamicLibrary(std::string path) : mPath(path) {}
  std::string Path() const { return mPath; }
};

struct BinaryInternal;

class Binary {
private:
  std::string mPath;
  OStype os = OStype::UNKNOWN;
  Archtype arch = Archtype::UNKNOWN;
  uint64_t textSectionStartAddress;
  std::vector<uint8_t> mInstructions;
  std::unique_ptr<BinaryInternal> mBinaryInternal;
  void elfParser();
  void peParser();
  void machOParser();

public:
  Binary(std::string path);
  ~Binary();
  std::string Path() const { return mPath; }
  uint64_t getStartAddress() const { return textSectionStartAddress; }
  Archtype Arch() const { return arch; }
  OStype OS() const { return os; }

  const std::vector<uint8_t> &Instructions() const;
  std::vector<std::string> &functionNames();
  friend class ASMParser;
};

inline std::ostream &operator<<(std::ostream &out, const Binary &binary) {
  out << "filename: " << binary.Path() << std::endl;
  out << "OS: " << binary.OS() << std::endl;
  out << "ISA: " << binary.Arch() << std::endl;
  out << "Text section size: " << binary.Instructions().size();
  return out;
}

inline std::ostream &operator<<(std::ostream &out, const DynamicLibrary &dLib) {
  out << dLib.Path() << std::endl;
  return out;
}

#endif // __runtime_h__