#ifndef __lib_Interface_H__
#define __lib_Interface_H__

#include "interfaceDisassembler.h"
#include "types.h"
#include <memory>

extern "C" AbstractDisassembler *GetDisassembler();
extern "C" void Decode(const unsigned char *code, size_t size);
extern "C" void Clear();
extern "C" void GetOperands(std::vector<std::string> &operands);
extern "C" void GetOpCodes(std::vector<std::string> &opCodes);
extern "C" void Initalize(Archtype archType);
extern "C" bool IsInitalized();

#endif //__lib_Interface_H__