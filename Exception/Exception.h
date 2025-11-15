#include <iostream>

struct A
{
    A ()
    {
        throw std::bad_alloc();
    }
    A (void*)
    {
        throw new std::bad_alloc ();
    }
    A (const char* msg)
    {
        
    }
    void ThrowException ()
    {
        throw "C-Style String: ThrowException";
    }

    std::ostream& MyDebug ()
    {
        return std::cerr;
    }
};
 