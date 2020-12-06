#include "autocli.h"
#include "rawcli.h"
#include "binaryfilecli.h"

AutoCLI::AutoCLI(int argc, char** argv)
	{
		initParser(argc, argv);
		
		if (CliParser)
		{
			CliParser->executeAction();
		}
	}

void AutoCLI::initParser(int argc, char** argv)
{
    cli::Parser parser(argc, argv);

    if (parser.doesArgumentExist(RawCLI::name, "--" + RawCLI::altName))
    {
        CliParser = std::unique_ptr<BaseCLI>(new RawCLI(argc, argv));
        return;
    }

    if (parser.doesArgumentExist(BinaryFileCLI::name, "--" + BinaryFileCLI::altName))
    {
    	CliParser = std::unique_ptr<BaseCLI>(new BinaryFileCLI(argc, argv));
    	return;
    }
}