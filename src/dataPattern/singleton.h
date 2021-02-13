#ifndef singleton_h
#define singleton_h

#include <memory>
#include <mutex>

// typedef std::lock_guard<std::mutex> Lock;
typedef std::unique_lock<std::mutex> Lock;
template <class T> class SingletonBase : public T {
  SingletonBase<T>(const SingletonBase<T> &) = delete;
  SingletonBase<T> &operator=(const SingletonBase<T> &) = delete;
  SingletonBase<T>() = default;

  static std::unique_ptr<SingletonBase<T>> m_pInstance;
  static std::once_flag m_once;
  std::mutex m_mutex;

public:
  virtual ~SingletonBase<T>() = default;
  static SingletonBase<T> *getPtr() {
    std::call_once(m_once, []() { m_pInstance.reset(new SingletonBase<T>); });
    return m_pInstance.get();
  }
  static SingletonBase<T> &get() { return *getPtr(); }
  Lock getLock() { return Lock(m_mutex); }
};

template <typename T>
std::unique_ptr<SingletonBase<T>> SingletonBase<T>::m_pInstance;
template <typename T> std::once_flag SingletonBase<T>::m_once;

#endif // singleton_h
