#ifndef __Disassembler_H__
#define __Disassembler_H__

#include <iostream>
#include <memory> 
#include <vector>
#include <iterator>
#include <string>
#include "interfaces/interfaceDisassembler.h"

enum class DisassemblerType { 
    CAPSTONE
};

class Disassembler : public InterfaceDisassembler {
public:
    Disassembler(Archtype Archtype, DisassemblerType type=DisassemblerType::CAPSTONE);
    virtual void Decode(const unsigned char *code, int size) final;
    virtual ~Disassembler() {}
    friend std::ostream& operator<< (std::ostream& out, const Disassembler& aDis);
    //const std::unique_ptr<AbstractDisassembler>& getDisassembler() const { return pDisasm;}
    const std::vector<std::string>& getMnemonic() const final { return pDisasm->getMnemonic();}
    const std::vector<std::string>& getOpCodes() const final { return pDisasm->getOpCodes();}
    virtual void Clear() final;
private:
    std::unique_ptr<AbstractDisassembler> pDisasm;
};

template <typename T>
inline std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
    if ( !v.empty() ) {
        out << '[';
        std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
        out << "\b\b]";
    }
    return out;
}

inline std::ostream& operator<< (std::ostream& out, const Disassembler& aDis) {
    auto mnemonic = aDis.pDisasm->getMnemonic();
    auto opCodes  = aDis.pDisasm->getOpCodes();
    out << "Instruction count: " << mnemonic.size() << std::endl;
    for(size_t i = 0; i < mnemonic.size(); i++) {
        out << mnemonic[i] << " " << opCodes[i] << std::endl;
    }
    return out;
}

#endif // __Disassembler_H__
