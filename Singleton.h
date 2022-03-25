#ifndef SINGLETON_H
#define SINGLETON_H

#include "NonCopyable.h"
#include <mutex>

template<typename T>
class CSingleton : public CNonCopyable
{
public:
    static T* Instance()
    {
        static std::once_flag of;
        std::call_once(of, [&]
        {
            instance_ = new T();
        });

        return instance_;
    }

private:
    static T* instance_;
};

template<typename T>
T* CSingleton<T>::instance_ = nullptr;

#endif // SINGLETON_H
