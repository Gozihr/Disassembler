#include "rawcli.h"

const std::string RawCLI::name = "r";
const std::string RawCLI::altName = "raw";
const std::string RawCLI::description = "Dissassemble the raw bytes";


RawCLI::RawCLI(int argc, char** argv) : BaseCLI(argc, argv)
{ }

RawCLI::~RawCLI() {}

void RawCLI::configure_parser(cli::Parser& parser)
{
	this->BaseCLI::configure_parser(parser);
	parser.set_required<std::string>("a", "arch", "", "ISA to decode.");
	parser.set_required<std::string>("i", "input", "input string to disassemble.");
	parser.set_required<bool>(name, altName, description);
}

void RawCLI::executeCLI()
{
	this->BaseCLI::executeCLI();
    this->arch      = parser.get<std::string>("a");
    this->assembly  = parser.get<std::string>("i");
}

void RawCLI::executeAction()
{
	executeCLI();
	m_disassemble.action(this->assembly, this->arch);
}