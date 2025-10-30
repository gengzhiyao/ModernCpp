#include <memory>
#include <stdlib.h>
#include <iostream>

class MemMgr {
public:
    MemMgr () = default;
    MemMgr (const char* nmessage)
        :message (nmessage)
    {
        std::cout << message << std::endl;
    }
    void MemAlloc ();

private:
    const char* message;
};

template <typename T>
class MyAllocator {
public:
    T* allocate (std::size_t n)
    {
        return static_cast< T* >(malloc (sizeof (T) * n));
    }
};