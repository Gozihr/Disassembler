#ifndef __auto_cli_h__
#define __auto_cli_h__

#include <memory>
#include "basecli.h"

class AutoCLI
{
private:
    std::unique_ptr<BaseCLI> CliParser;
    void initParser(int argc, char** argv);
public:
	AutoCLI(int argc, char** argv);
};

#endif //__auto_cli_h__