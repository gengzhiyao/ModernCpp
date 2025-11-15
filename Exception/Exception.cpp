#include "Exception.h"

int main ()
{
    
    try
    {
        A a1;
        A* a2 = new A (new int(0));
        a1.ThrowException ();
    }
    catch (std::exception& e)
    {
        std::cout << e.what () << "------throw std::bad_alloc()" << std::endl;
        throw;
    }
    catch (std::exception*& e)
    {
        std::cout << e->what () << "------throw new std::bad_alloc()" << std::endl;
    }
    catch (const char* msg)
    {
        std::cout << msg << std::endl;
    }

    A* a3 = new A ("no exception.");
    a3->MyDebug () << "no exception called.\n";   //类似qt中的qDebug()

    std::cout << "After throw exception" << std::endl;
    std::terminate();
    return 0;
}