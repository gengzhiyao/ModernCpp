#include "Logger.h"

int main ()
{
    int a = 10;
    Logger<int>::log (a);
    const char* ch = "string";
    int* b = &a;
    Logger<const char*>::log (ch);
    Logger<int*>::log (b);

    std::string str = "Hello World";
    Logger<std::string>::log (str);

    std::cout << "------------" << std::endl;
    logAll (a , b , str);

    std::cout << "5! = " << Factorial<5>::value << std::endl;

    std::cout << Fibonacci<10>::value << std::endl;

    static_assert(is_addable<int>::value , "int can be addable.");
    //static_assert(is_addable<void*>::value , "pointer can not be addable.");  //NOTE - 编译期间报错，不可以相加
    static_assert(!is_addable<void*>::value , "pointer can not be addable.");
    
    using list = TypeList<int , double , char>;
    using third_type = TypeAt<list , 2>::type;
    std::cout << "TypeAt 2 :" << typeid(third_type).name () << std::endl;

    MaxValue ('a' , 'f');
    //MaxValue (2 , 3.2);     //ERROR - 不明确的推导类型
    MaxValue<double> (2 , 3.2);

    FixedArray<char , 10> arr = { 'a','b' };
    std::cout << arr[1] << std::endl;

    std::vector<int> container = { 1,2,3,4,5 };
    ContainerPrinter <std::vector , int> printer;
    printer.Print (container);

    PrintAll (5 , 4 , 2.4f , 'a' , "C-style string");

    std::cout <<"leftSumAll:"<< leftSumAll (1 , 2 , 3 , 4 , 5) << std::endl;
    std::cout << "rightSumAll:"<< rightSumAll (1 , 2 , 3 , 4 , 5) << std::endl;

    return 0;
}