#ifndef __abstract_factory_h__
#define __abstract_factory_h__
#include <string>
#include <vector>
#include <memory>
#include <type_traits>
#include <utility>

#include "dynamicLibMgr.h"

class ILoad {
    public:
        virtual bool LoadLibraryFromPath(std::string sLoadPath) = 0;
        virtual function_union& getLoadedLibrary() = 0;
        ILoad() {}
};

typedef std::shared_ptr<ILoad> Load_ptr;

namespace Helper {
#if _WIN32
    template <typename Derived, typename = std::enable_if<std::is_base_of<ILoad, Derived>::value>::type>
#else
    template <typename Derived, typename std::enable_if<std::is_base_of<ILoad, Derived>::value>::type>
#endif
    std::shared_ptr<ILoad> makeShared() {
        return std::make_shared<Derived>();
    }
};

class AbstractOSFactory;
typedef std::shared_ptr<AbstractOSFactory> AbstractOSFactory_ptr;

class AbstractOSFactory {
    public: 
        virtual Load_ptr getLoadLib() = 0;

        static AbstractOSFactory_ptr createFactory();
        static bool doesFileExist(const std::string &filePath);
};

#endif // __abstract_factory_h__