#include "sfinae.h"
#include <memory>

struct WithValueType
{
    using value_type = int;
};


int main ()
{
    int a = 5;
    print_type(a);
    std::unique_ptr<float> b = std::make_unique<float> (2.4f);
    float* c = new float(2.4f);
    print_type (c);
    print_type (b.get ());

    const char* string = "Hello C-style string.";
    print_type (string);

    //编译器认为float*类型的模板
    double* d = new double{ 2.3 };
    print_type (d);
    WithFooClass fooClass;
    call_foo (fooClass);

    TypePrinter<WithValueType , std::true_type>::print ();

    return 0;
}