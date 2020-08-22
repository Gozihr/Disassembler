#ifndef __Interface_Disassembler_H__
#define __Interface_Disassembler_H__

#include <iostream>
#include <vector>
#include <iterator>
#include <string>

enum class Archtype { 
    ARM64,
    X86,
    X86_64
};

class InterfaceDisassembler {
    public:
        virtual void Decode(const unsigned char *code, int size) = 0;
        virtual void Clear() = 0;
        virtual ~InterfaceDisassembler() {};
        virtual const std::vector<std::string>& getMnemonic() const = 0;
        virtual const std::vector<std::string>& getOpCodes() const = 0;
};

class AbstractDisassembler : public InterfaceDisassembler {
    public:
        virtual void Decode(const unsigned char *code, int size) = 0;
        virtual ~AbstractDisassembler() {}
        friend std::ostream& operator<< (std::ostream& out, const AbstractDisassembler& aDis);
        virtual const std::vector<std::string>& getMnemonic() const { return mnemonic;}
        virtual const std::vector<std::string>& getOpCodes() const { return opCodes;}
        virtual void Clear() final {
            mnemonic.clear();
            opCodes.clear();
        }
    protected:
        std::vector<std::string> mnemonic;
        std::vector<std::string> opCodes;
};

inline std::ostream& operator<< (std::ostream& out, const AbstractDisassembler& aDis) {
    auto mnemonic = aDis.mnemonic;
    auto opCodes  = aDis.opCodes;
    for(size_t i = 0; i < aDis.mnemonic.size(); i++) {
        out << mnemonic[i] << " " << opCodes[i] << std::endl;
    }
    return out;
}

#endif // __Interface_Disassembler_H__
