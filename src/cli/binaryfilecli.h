#ifndef __binary_file_cli_h__
#define __binary_file_cli_h__

#include "basecli.h"
#include "binaryDisassemble.h"

class BinaryFileCLI : public BaseCLI {
public:
  static const std::string name;
  static const std::string altName;
  static const std::string description;

protected:
  BinaryDisassemble m_disassemble;
  virtual void configure_parser() override;

public:
  BinaryFileCLI(int argc, char **argv);
  virtual ~BinaryFileCLI();
  virtual void executeAction() override final;

private:
  std::string filename;
};

#endif // __binary_file_cli_h__