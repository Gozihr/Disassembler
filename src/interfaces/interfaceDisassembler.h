#ifndef __Interface_Disassembler_H__
#define __Interface_Disassembler_H__

#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include "types.h"

class InterfaceDisassembler {
    public:
        virtual void Decode(const unsigned char *code, size_t size) = 0;
        virtual void Clear() = 0;
        virtual ~InterfaceDisassembler() {};
        virtual const std::vector<std::string>& getOperands() const = 0;
        virtual const std::vector<std::string>& getOpCodes() const = 0;
};

class AbstractDisassembler : public InterfaceDisassembler {
    public:
        virtual ~AbstractDisassembler() {}
        friend std::ostream& operator<< (std::ostream& out, const AbstractDisassembler& aDis);
        virtual const std::vector<std::string>& getOperands() const { return operands;}
        virtual const std::vector<std::string>& getOpCodes() const { return opCodes;}
        virtual void Clear() final {
            operands.clear();
            opCodes.clear();
        }
    protected:
        std::vector<std::string> operands;
        std::vector<std::string> opCodes;
};

inline std::ostream& operator<< (std::ostream& out, const AbstractDisassembler& aDis) {
    auto operands = aDis.operands;
    auto opCodes  = aDis.opCodes;
    for(size_t i = 0; i < aDis.opCodes.size(); i++) {
        out << opCodes[i] << " " << operands[i] << std::endl;
    }
    return out;
}

#endif // __Interface_Disassembler_H__
