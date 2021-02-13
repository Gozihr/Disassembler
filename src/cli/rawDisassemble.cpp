
#include "disassemble.h"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <sstream>
#include <vector>

#include "interfaces/types.h"
#include "rawDisassemble.h"
#include "pluginInfra/dynamicLibMgr.h"
#include "interfaces/helpers.h"
#include "interfaces/types.h"

namespace {
std::vector<unsigned char> HexToBytes(const std::string &hex) {
  std::vector<unsigned char> bytes;
  for (size_t i = 0; i < hex.length(); i += 2) {
    std::string byteStr = hex.substr(i, 2);
    unsigned char byte =
        static_cast<unsigned char>(strtol(byteStr.c_str(), nullptr, 16));
    bytes.push_back(byte);
  }

  return bytes;
}

std::vector<unsigned char> HexToBytesFormat(const std::string &hex) {
  std::string hexStr(hex);
  hexStr.erase(std::remove(hexStr.begin(), hexStr.end(), ' '), hexStr.end());
  if (hexStr[0] == '0' && (hexStr[1] == 'x' || hexStr[1] == 'X')) {
    hexStr = hexStr.substr(2, hexStr.size() - 2);
  }
  return HexToBytes(hexStr);
}
} // namespace

bool RawDisassemble::action(std::string assembly, std::string arch, const std::string &dynamicLibPaths) {
  std::vector<unsigned char> bytesArr;
  bytesArr = ::HexToBytesFormat(assembly);
  Arch_iterator archFound = ArchTypeMap.find(arch);
  if (archFound == ArchTypeMap.end()) {
    std::cerr << "architecture not found!" << std::endl;
    return false;
  }

  DisassemblerType dType = DisassemblerType::CAPSTONE;
  if(!dynamicLibPaths.empty()) {
    std::vector<std::string> vecDynamicLibPaths = Helpers::Split(dynamicLibPaths);
    DynamicLibMgr::loadDynamicLibs(vecDynamicLibPaths);
    dType = DisassemblerType::DYNAMIC;
  }

  Archtype archType = archFound->second;
  Disassembler disasm(archType, dType);
  disasm.Decode(bytesArr.data(), bytesArr.size());

  std::cout << disasm << std::endl;

  return true;
}