#include <fstream>

#include "abstractOSFactory.h"
#if defined(_WIN32) || defined(_WIN64)
#include "windowsFactory.h"
#endif


AbstractOSFactory_ptr  AbstractOSFactory::createFactory() {
    #if defined(_WIN32) || defined(_WIN64)
        return AbstractOSFactory_ptr(new WindowsFactory);
    #else
        return AbstractOSFactory_ptr();
    #endif
}

bool AbstractOSFactory::doesFileExist(const std::string &filePath) {
    std::ifstream fileStream(filePath.c_str());
    return fileStream.good();
}