
#ifndef __raw_disassemble_h__
#define __raw_disassemble_h__

#include <string>

class  RawDisassemble
{
public:
	RawDisassemble() { }
public:
	virtual bool action(std::string assembly, std::string arch);
};

#endif // __raw_disassemble_h__