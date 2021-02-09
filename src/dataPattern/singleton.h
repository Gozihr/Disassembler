#ifndef singleton_h
#define singleton_h

#include <atomic>
#include <future>
#include <mutex>
#include <thread>
#include <memory>

#include "singletonMgr.h"

template<class T>
class SingletonBase : public T
{
public:
    typedef std::atomic <SingletonBase*> pointer;
    static SingletonBase& get();

private:
    // prevent this class from ever being instantiated directly
    SingletonBase();
    // to allow for determanistic singleton destruction (only to be called by SingletonMgr)
    static void release();
    static SingletonBase* getPtr();
    // prevent this class from ever being copied or moved
    SingletonBase(const SingletonBase&) = delete;
    SingletonBase(SingletonBase&&) = delete;
    static std::mutex s_guardMutex;
    static pointer      m_pInstance;
    friend class SingletonMgr;
    //NOTE: MSVC triggers internal error on the below line.
    //friend SingletonMgr::areEqual(SingletonMgr::SingletonReleaseFunc* pSingletonRelease);
};

template<class T>
SingletonBase<T>::SingletonBase() {
    SingletonMgr::registerSingleton(SingletonBase<T>::release);
}

template<class T>
void SingletonBase<T>::release() {
    delete getPtr();
}

template<class T>
SingletonBase<T>& SingletonBase<T>::get() {
    return *getPtr();
}

#define DECLARE_SINGLETON_STATICS(T)                                            \
    template<>T::pointer T::m_pInstance;                                        \
    template<>std::mutex T::s_guardMutex;                                       \
                                                                                \
    template<>T* T::getPtr() {                                                  \
        T* ptr = m_pInstance.load(std::memory_order_acquire);                   \
        if (!ptr) {                                                             \
            std::lock_guard<std::mutex> Lock(s_guardMutex);                     \
            ptr = m_pInstance.load(std::memory_order_relaxed);                  \
            if(!ptr) {                                                          \
                ptr = new T();                                                  \
                m_pInstance.store(ptr, std::memory_order_release);              \
            }                                                                   \
        }                                                                       \
        return ptr;                                                             \
    }                                                                           \

#endif // singleton_h