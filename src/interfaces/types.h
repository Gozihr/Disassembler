/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __Types_H__
#define __Types_H__

#include "pch.h"
#include <unordered_map>

enum class Archtype { UNKNOWN, ARM64, X86, X86_64 };

enum class OStype { UNKNOWN, LINUX, MACOS, WINDOWS };

static const std::unordered_map<std::string, Archtype> ArchTypeMap = {

    {"aarch64", Archtype::ARM64},
    {"arm64", Archtype::ARM64},
    {"x86", Archtype::X86},
    {"x86_64", Archtype::X86_64}

};

static const std::unordered_map<Archtype, std::string> ArchStrMap = {

    {Archtype::UNKNOWN, "unknown"},
    {Archtype::ARM64, "arm64"},
    {Archtype::X86, "x86"},
    {Archtype::X86_64, "x86_64"}

};

typedef std::unordered_map<std::string, Archtype>::const_iterator Arch_iterator;
typedef std::unordered_map<Archtype, std::string>::const_iterator
    Arch_Str_iterator;

static const std::unordered_map<std::string, OStype> OSTypeMap = {

    {"Linux", OStype::LINUX},
    {"MacOS", OStype::MACOS},
    {"Windows", OStype::WINDOWS}

};

static const std::unordered_map<OStype, std::string> OSStrMap = {
    {OStype::UNKNOWN, "unknown"},
    {OStype::LINUX, "Linux"},
    {OStype::MACOS, "MacOS"},
    {OStype::WINDOWS, "Windows"}

};

typedef std::unordered_map<std::string, OStype>::const_iterator OS_iterator;
typedef std::unordered_map<OStype, std::string>::const_iterator OS_Str_iterator;

inline std::ostream &operator<<(std::ostream &out, const Archtype archtype) {
  out << ArchStrMap.at(archtype);
  return out;
}

inline std::ostream &operator<<(std::ostream &out, const OStype ostype) {
  out << OSStrMap.at(ostype);
  return out;
}

class LookupHelpers {
    LookupHelpers() = delete;
    public:
 static Archtype ArchFind(std::string arch) {
  Arch_iterator archFound = ArchTypeMap.find(arch);
  if (archFound == ArchTypeMap.end()) {
    std::cerr << "architecture not found!" << std::endl;
    return Archtype::UNKNOWN;
  }
  return archFound->second;
}
};

struct Config {
  std::string arch;
  std::string libpath;
  std::string binaryPath;
  std::string rawAsm;
};

#endif //__Types_H__