#include "parser.h"
//#include <LIEF/Abstract/Parser.hpp>

#include "LIEF/ELF/utils.hpp"
#include "LIEF/ELF/Parser.hpp"

#include "LIEF/PE/utils.hpp"
#include "LIEF/PE/Parser.hpp"
#include "LIEF/PE/Binary.hpp"

#include "LIEF/MachO/utils.hpp"
#include "LIEF/MachO/Parser.hpp"
#include "LIEF/MachO/FatBinary.hpp"
#include "LIEF/MachO/Binary.hpp"

#include <iostream>

namespace {
    Archtype GetArch(LIEF::MachO::CPU_TYPES cputype) {
        switch(cputype){
        case LIEF::MachO::CPU_TYPES::CPU_TYPE_X86_64:
            return Archtype::X86_64;
        case LIEF::MachO::CPU_TYPES::CPU_TYPE_I386  :
            return Archtype::X86;
        case LIEF::MachO::CPU_TYPES::CPU_TYPE_ARM64:
            return Archtype::ARM64;
        default:
            std::cerr << "This not a unsupported Architecture." << std::endl;
            throw;
        }
    }
}

ASMParser::ASMParser(std::string filename) {
    if (LIEF::ELF::is_elf(filename)) {
        this->os = OStype::LINUX;
        auto elfBinary = LIEF::ELF::Parser::parse(filename);
        LIEF::ELF::Section& textSection = elfBinary->get_section(".text");
        textSection.content().swap(this->instructions);
        //TODO fetch cpu type
    } else if (LIEF::MachO::is_macho(filename)) {
         this->os = OStype::MACOS;
        // For fat binary we take the last one...
        LIEF::MachO::FatBinary* fat = LIEF::MachO::Parser::parse(filename).release();
        LIEF::MachO::Binary* binaryData = nullptr;
        if (fat) {
          binaryData = fat->pop_back();
          delete fat;
        }

        auto header = binaryData->header();
        this->arch = ::GetArch(header.cpu_type());

        LIEF::MachO::Section& textSection = binaryData->get_section("__text");
        textSection.content().swap(this->instructions);
    } else if (LIEF::PE::is_pe(filename)) {
        this->os = OStype::WINDOWS;
        auto peBinary = LIEF::PE::Parser::parse(filename);
        LIEF::PE::Section& textSection = peBinary->get_section(".text");
        textSection.content().swap(this->instructions);
        //TODO fetch cpu type
    } else {
        std::cerr << "This binary is not currently supported." << std::endl;
    }
    //auto binaryData = LIEF::Parser::parse(path);
    //if( binaryData->is<LIEF::ELF::Binary>()) {
    //    this->os = OStype::LINUX;
    //} else if(binaryData->is<LIEF::MachO::Binary>()) {
    //    this->os = OStype::MACOS;
    //    //auto textSection = (binaryData->as<LIEF::MachO::Binary>())->get_section("__text");
    //} else if(binaryData->is<LIEF::PE::Binary>()) {
    //    this->os = OStype::WINDOWS;
    //} 
}

const std::vector<uint8_t>& ASMParser::Instructions() const {
    return instructions;
}