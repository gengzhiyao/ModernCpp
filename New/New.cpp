#include "New.h"

int main ()
{
    New* a = new New(3);
    a->SetData (4);
    std::cout << a->GetData () << std::endl;
    New* b = new(a) New (5);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << a->GetData () << std::endl;
    std::cout << b->GetData () << std::endl;

    delete a;
}