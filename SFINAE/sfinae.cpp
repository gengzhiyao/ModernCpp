#include "sfinae.h"
#include <memory>

struct WithValueType
{
    using value_type = int;
};

//NOTE - 数组形式的模板实参推断，这样是不对的，C++ 中，固定大小数组的引用 必须明确指定数组的大小，除非用模板参数推导大小
// template<typename T>
// void ArrFunction (const T (&) [])
// {
// }

//这种写法才是正确的
template<typename T , std::size_t N>
void ArrFunction (const T (&) [N])
{

}

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

    int arr [] = { 2,2,2,2 };
    ArrFunction (arr);

    return 0;
}