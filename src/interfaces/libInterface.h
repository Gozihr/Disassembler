/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __lib_Interface_H__
#define __lib_Interface_H__

#include "instruction.h"
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
EXPORT(const std::vector<Instruction> *) GetInstructions();
EXPORT(void) Initalize(Archtype archType);
EXPORT(bool) IsInitalized();

#endif //__lib_Interface_H__