// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "parser.h"
//#include <LIEF/Abstract/Parser.hpp>

#include <LIEF/ELF/Binary.hpp>
#include <LIEF/ELF/Parser.hpp>
#include <LIEF/ELF/Section.hpp>
#include <LIEF/ELF/utils.hpp>

#include <LIEF/PE/Binary.hpp>
#include <LIEF/PE/Parser.hpp>
#include <LIEF/PE/Section.hpp>
#include <LIEF/PE/utils.hpp>

#include <LIEF/MachO/Binary.hpp>
#include <LIEF/MachO/FatBinary.hpp>
#include <LIEF/MachO/Parser.hpp>
#include <LIEF/MachO/Section.hpp>
#include <LIEF/MachO/utils.hpp>

#include <iostream>

#include "runtime/internalData.h"

namespace {
Archtype GetArch(LIEF::MachO::CPU_TYPES cputype) {
  switch (cputype) {
  case LIEF::MachO::CPU_TYPES::CPU_TYPE_X86_64:
    return Archtype::X86_64;
  case LIEF::MachO::CPU_TYPES::CPU_TYPE_I386:
    return Archtype::X86;
  case LIEF::MachO::CPU_TYPES::CPU_TYPE_ARM64:
    return Archtype::ARM64;
  default:
    std::cerr << "This not a unsupported Architecture." << std::endl;
    throw;
  }
}

Archtype GetArch(LIEF::ELF::ARCH cputype) {
  switch (cputype) {
  case LIEF::ELF::ARCH::EM_AARCH64:
    return Archtype::ARM64;
  case LIEF::ELF::ARCH::EM_386:
    return Archtype::X86;
  case LIEF::ELF::ARCH::EM_X86_64:
    return Archtype::X86_64;
  default:
    std::cerr << "This not a unsupported Architecture." << std::endl;
    throw;
  }
}

Archtype GetArch(LIEF::PE::MACHINE_TYPES cputype) {
  switch (cputype) {
  case LIEF::PE::MACHINE_TYPES::IMAGE_FILE_MACHINE_ARM64:
    return Archtype::ARM64;
  case LIEF::PE::MACHINE_TYPES::IMAGE_FILE_MACHINE_I386:
    return Archtype::X86;
  case LIEF::PE::MACHINE_TYPES::IMAGE_FILE_MACHINE_AMD64:
    return Archtype::X86_64;
  default:
    std::cerr << "This not a unsupported Architecture." << std::endl;
    throw;
  }
}

} // namespace

void ASMParser::elfParser() {
  
  std::unique_ptr<LIEF::ELF::Binary> elfBinary =
      LIEF::ELF::Parser::parse(this->mBinary.Path());
  auto header = elfBinary->header();
  LIEF::ELF::Section &textSection = elfBinary->get_section(".text");
  textSection.content().swap(this->mBinary.mInstructions);

  this->mBinary.os = OStype::LINUX;
  this->mBinary.arch = ::GetArch(header.machine_type());
  //this->mBinary.mBinaryInternal->elfBinary = std::move(elfBinary);
}

void ASMParser::peParser() {
   
   auto peBinary = LIEF::PE::Parser::parse(this->mBinary.Path());
   LIEF::PE::Section &textSection = peBinary->get_section(".text");
   textSection.content().swap(this->mBinary.mInstructions);
   this->mBinary.os = OStype::WINDOWS;
   this->mBinary.arch = ::GetArch(peBinary->header().machine());
   //this->mBinary.mBinaryInternal->peBinary = std::move(peBinary);
}

void ASMParser::machOParser() {
    // For fat binary we take the last one...
    LIEF::MachO::FatBinary *fat =
        LIEF::MachO::Parser::parse(this->mBinary.Path()).release();
    LIEF::MachO::Binary *binaryData = nullptr;
    if (fat) {
      binaryData = fat->pop_back();
      delete fat;
    }

    auto header = binaryData->header();
    LIEF::MachO::Section &textSection = binaryData->get_section("__text");
    textSection.content().swap(this->mBinary.mInstructions);

    this->mBinary.os = OStype::MACOS;
    this->mBinary.arch = ::GetArch(header.cpu_type());
    //this->mBinary.mBinaryInternal->machOBinary = std::move(binaryData);
}

ASMParser::ASMParser(std::string filename) : mBinary(filename) {
  if (LIEF::ELF::is_elf(filename)) {
    elfParser();
  } else if (LIEF::MachO::is_macho(filename)) {
    machOParser();
  } else if (LIEF::PE::is_pe(filename)) {
    peParser();
  } else {
    std::cerr << "This binary is not currently supported." << std::endl;
  }
}