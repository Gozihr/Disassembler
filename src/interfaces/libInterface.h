#ifndef __lib_Interface_H__
#define __lib_Interface_H__

#include "interfaceDisassembler.h"
#include "types.h"
#include <memory>

#if defined(_WIN32) || defined(_WIN64)
#define EXPORT(type) extern "C" __declspec(dllexport) type __cdecl
#else
#define EXPORT(type) extern "C" type
#endif

EXPORT(AbstractDisassembler *) GetDisassembler();
EXPORT(void) Decode(const unsigned char *code, size_t size);
EXPORT(void) Clear();
EXPORT(const std::vector<std::string> *) GetOperands();
EXPORT(const std::vector<std::string> *) GetOpCodes();
EXPORT(void) Initalize(Archtype archType);
EXPORT(bool) IsInitalized();

#endif //__lib_Interface_H__