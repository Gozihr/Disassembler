#ifndef singleton_mgr_h
#define singleton_mgr_h

#include "Singleton.h"

class SingletonMgr {
public:
	typedef void (SingletonReleaseFunc)();
	static void registerSingleton(SingletonReleaseFunc* pSingletonRelease);
	static bool areEqual(SingletonReleaseFunc* pSingletonRelease);
private:
	SingletonMgr() = delete;
};

#endif // singleton_mgr_h