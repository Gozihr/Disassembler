#ifndef __Parser_H__
#define __Parser_H__

#include "interfaces/types.h"
#include "interfaces/pch.h"

class ASMParser {
public:
  ASMParser(std::string filename);
  Archtype Arch() { return arch; }
  OStype OS() { return os; }
  const std::vector<uint8_t> &Instructions() const;

private:
  OStype os = OStype::UNKNOWN;
  Archtype arch = Archtype::UNKNOWN;
  std::vector<uint8_t> instructions;
};

#endif // __Parser_H__