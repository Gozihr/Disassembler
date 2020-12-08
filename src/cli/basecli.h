#ifndef __base_cli_h__
#define __base_cli_h__

#include <cmdParser/cmdparser.hpp>


class BaseCLI
{
protected:
    cli::Parser parser;

    BaseCLI(int argc, char** argv) : parser(argc, argv) {}

	virtual void configure_parser() {
		parser.set_optional<bool>("v", "verbose", false, "print verbose");
	}

public:
	virtual ~BaseCLI() {}
	virtual void executeAction() = 0;
};

#endif //__base_cli_h__