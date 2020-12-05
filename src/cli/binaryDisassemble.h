
#ifndef __binary_disassemble_h__
#define __binary_disassemble_h__

#include <string>

class  BinaryDisassemble
{
public:
	BinaryDisassemble() { }
public:
	virtual bool action(std::string filename);
};

#endif // __binary_disassemble_h__