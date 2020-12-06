#include "binaryfilecli.h"

const std::string BinaryFileCLI::name = "b";
const std::string BinaryFileCLI::altName = "binary";
const std::string BinaryFileCLI::description = "Dissassemble a native executable";


BinaryFileCLI::BinaryFileCLI(int argc, char** argv) : BaseCLI(argc, argv)
{ }

BinaryFileCLI::~BinaryFileCLI() {}

void BinaryFileCLI::configure_parser(cli::Parser& parser)
{
	this->BaseCLI::configure_parser(parser);
	parser.set_required<std::string>("f", "filename", "input file to disassemble.");
	parser.set_required<bool>(name, altName, description);
}

void BinaryFileCLI::executeCLI()
{
	this->BaseCLI::executeCLI();
    this->filename = parser.get<std::string>("f");
}

void BinaryFileCLI::executeAction()
{
	executeCLI();
	m_disassemble.action(this->filename);
}