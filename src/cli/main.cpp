
#include <cmdParser/cmdparser.hpp>
#include <iostream>
#include <bitset>
#include <vector>
#include <sstream>
#include <algorithm>
#include "disassemble.h"

std::vector<unsigned char> HexToBytes(const std::string& hex) {
  std::vector<unsigned char> bytes;
  for (size_t i = 0; i < hex.length(); i += 2) {
    std::string byteStr = hex.substr(i, 2);
    unsigned char byte = static_cast<unsigned char>(strtol(byteStr.c_str(), nullptr, 16));
    bytes.push_back(byte);
  }

  return bytes;
}

std::vector<unsigned char> HexToBytes(const char* hex) {
    std::string hexStr(hex);
    hexStr.erase(std::remove(hexStr.begin(), hexStr.end(), ' '), hexStr.end());
    if(hexStr[0] == '0' && (hexStr[1] == 'x' || hexStr[1] == 'X')) {
        hexStr = hexStr.substr(2, hexStr.size() - 2);
    }
    return HexToBytes(hexStr);
}

int main(int argc, char** argv) {
    std::vector<unsigned char> bytesArr;
    if(argc == 2) {
        bytesArr = HexToBytes(argv[1]);
    }
    Disassembler disasm(Archtype::X86_64);
    disasm.Decode(bytesArr.data(), bytesArr.size());
    std::cout << disasm << std::endl;
    return 0;
}