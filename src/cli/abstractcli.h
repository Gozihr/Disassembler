#ifndef __abstract_cli_h__
#define __abstract_cli_h__

#include <cmdParser/cmdparser.hpp>

class AbstractCLI
{
public:
	virtual void configure_parser(cli::Parser& parser) = 0;
	virtual void executeCLI() = 0;
	virtual void executeAction() = 0;
};

class BaseCLI : public AbstractCLI
{
private:
	bool bParsed;
	bool bParseResult;
	void parse()
	{
		if (!bParsed)
		{
			bParsed = true;
			configure_parser(parser);
			bParseResult = parser.run();
		}
	}
protected:
	cli::Parser parser;

	BaseCLI(int argc, char** argv) : parser(argc, argv) 
	{

	}

	virtual void configure_parser(cli::Parser& parser) override
	{
		parser.set_optional<bool>("v", "verbose", false, "print verbose");
	}

public:
	virtual ~BaseCLI() {}

	virtual void executeCLI() override
	{
		parse();
	}

	bool isParseAble()
	{
		parse();
		return bParseResult;
	}

};

#endif //__abstract_cli_h__