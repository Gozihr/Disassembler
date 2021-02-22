#include "dynamicDisassembler.h"
#include "pluginInfra/dynamicLibMgr.h"

DynamicDisassembler::DynamicDisassembler(Archtype archType) {
  DynamicLibMgr::initalize(archType);
}

DynamicDisassembler::~DynamicDisassembler() { 
	AbstractDisassembler::Clear();
	Clear(); 
}

void DynamicDisassembler::Decode(const unsigned char *code, size_t size) {
  DynamicLibMgr::decode(code, size);
  AbstractDisassembler::Clear();
  DynamicLibMgr::getOperands(operands);
  DynamicLibMgr::getOpCodes(opCodes);
}

void DynamicDisassembler::Clear() { DynamicLibMgr::clear(); }