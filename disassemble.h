#ifndef __Disassembler_H__
#define __Disassembler_H__

#include <iostream>
#include <memory> 
#include <vector>
#include <string>

enum class Archtype { 
    ARM64,
    X86,
    X86_64
};

enum class DisassemblerType { 
    CAPSTONE
};

class InterFaceDisassembler {
    public:
        virtual void Decode(const unsigned char *code, int size) = 0;
        virtual void Clear() = 0;
        virtual ~InterFaceDisassembler() {};
        virtual const std::vector<std::string>& getMnemonic() const = 0;
        virtual const std::vector<std::string>& getOpCodes() const = 0;
};

class AbstractDisassembler : public InterFaceDisassembler {
    public:
        virtual void Decode(const unsigned char *code, int size) = 0;
        virtual ~AbstractDisassembler() {}
        friend std::ostream& operator<< (std::ostream& out, const AbstractDisassembler& aDis);
        virtual const std::vector<std::string>& getMnemonic() const { return mnemonic;}
        virtual const std::vector<std::string>& getOpCodes() const { return opCodes;}
        virtual void Clear() final;
    protected:
        std::vector<std::string> mnemonic;
        std::vector<std::string> opCodes;
};

class Disassembler : public InterFaceDisassembler {
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

inline std::ostream& operator<< (std::ostream& out, const AbstractDisassembler& aDis) {
    auto mnemonic = aDis.mnemonic;
    auto opCodes  = aDis.opCodes;
    for(size_t i = 0; i < aDis.mnemonic.size(); i++) {
        out << mnemonic[i] << " " << opCodes[i] << std::endl;
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
