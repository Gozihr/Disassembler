#include "binaryfilecli.h"

const std::string BinaryFileCLI::name = "b";
const std::string BinaryFileCLI::altName = "binary";
const std::string BinaryFileCLI::description = "Dissassemble a native executable";


BinaryFileCLI::BinaryFileCLI(int argc, char** argv) : BaseCLI(argc, argv)
{
    configure_parser();
	//NOTE Needs to be run after configure_parser and property initalization
	parser.run(); //TODO: figure out how to abstract this so its only in BaseCLI
    this->filename = parser.get<std::string>("f");
}

BinaryFileCLI::~BinaryFileCLI() {}

void BinaryFileCLI::configure_parser()
{
    this->BaseCLI::configure_parser();
    parser.set_required<std::string>("f", "filename", "input file to disassemble.");
    parser.set_required<bool>(name, altName, description);
}


void BinaryFileCLI::executeAction()
{
    m_disassemble.action(this->filename);
}