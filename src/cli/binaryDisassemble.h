
#ifndef __binary_disassemble_h__
#define __binary_disassemble_h__

#include <string>

class BinaryDisassemble {
public:
  BinaryDisassemble() {}

public:
  virtual bool action(const std::string &filename, const std::string &dynamicLibPaths);
};

#endif // __binary_disassemble_h__