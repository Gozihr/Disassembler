#ifndef __abstract_factory_h__
#define __abstract_factory_h__
#include <string>
#include <vector>
#include <memory>

class ILoad {
    public:
        virtual bool LoadLibraryFromPath(std::string sLoadPath) = 0;
        virtual function_union& getLoadedLibrary() = 0;
};

typedef std::shared_ptr<ILoad> Load_ptr;
class AbstractOSFactory;
typedef std::shared_ptr<AbstractOSFactory> AbstractOSFactory_ptr;

class AbstractOSFactory {
    virtual Load_ptr get
};

#endif // __abstract_factory_h__