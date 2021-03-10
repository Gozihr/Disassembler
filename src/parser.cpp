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

void Binary::elfParser() {

  std::unique_ptr<LIEF::ELF::Binary> elfBinary =
      LIEF::ELF::Parser::parse(this->Path());
  auto header = elfBinary->header();
  LIEF::ELF::Section &textSection = elfBinary->get_section(".text");
  textSection.content().swap(this->mInstructions);

  this->os = OStype::LINUX;
  this->arch = ::GetArch(header.machine_type());
  this->textSectionStartAddress = textSection.virtual_address();
  this->mBinaryInternal->setElf(elfBinary);
}

void Binary::peParser() {

  auto peBinary = LIEF::PE::Parser::parse(this->Path());
  LIEF::PE::Section &textSection = peBinary->get_section(".text");
  textSection.content().swap(this->mInstructions);
  this->os = OStype::WINDOWS;
  this->arch = ::GetArch(peBinary->header().machine());
  this->textSectionStartAddress = textSection.virtual_address();
  this->mBinaryInternal->setPE(peBinary);
}

void Binary::machOParser() {
  // For fat binary we take the last one...
  LIEF::MachO::FatBinary *fat =
      LIEF::MachO::Parser::parse(this->Path()).release();
  LIEF::MachO::Binary *binaryData = nullptr;
  if (fat) {
    binaryData = fat->pop_back();
    delete fat;
  }

  auto header = binaryData->header();
  LIEF::MachO::Section &textSection = binaryData->get_section("__text");
  textSection.content().swap(this->mInstructions);

  this->os = OStype::MACOS;
  this->arch = ::GetArch(header.cpu_type());
  this->textSectionStartAddress = textSection.virtual_address();
  this->mBinaryInternal->setMachO(binaryData);
}

std::unique_ptr<Binary> ASMParser::Parser(std::string filename) {
  auto binary = std::make_unique<Binary>(filename);
  if (LIEF::ELF::is_elf(filename)) {
    binary->elfParser();
  } else if (LIEF::MachO::is_macho(filename)) {
    binary->machOParser();
  } else if (LIEF::PE::is_pe(filename)) {
    binary->peParser();
  } else {
    std::cerr << "This binary is not currently supported." << std::endl;
  }
  return binary;
}