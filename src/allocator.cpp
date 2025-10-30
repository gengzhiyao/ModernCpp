#include "allocator.h"

void MemMgr::MemAlloc ()
{
    int* pInt1 = static_cast< int* >(malloc (10 * sizeof (int)));
    int* pInt2 = static_cast< int* >(calloc (10 , sizeof (int)));
    std::cout << pInt1 << std::endl << pInt2 << std::endl;
    std::cout << *pInt1 << std::endl << *pInt2 << std::endl;
    int* pInt3 = static_cast< int* >(realloc (pInt2 , 15));
    std::cout << pInt3 << std::endl;
}

int main ()
{
    MemMgr mgr;
    mgr.MemAlloc ();

    MyAllocator<MemMgr> myalloc;
    myalloc.allocate (2);
}