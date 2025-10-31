#include "Item3.h"
#include <iostream>

int main ()
{
    Foo ();

    TextBlock tb ("Hello");
    std::cout << tb[0] << "\n";                    // calls non-const
    // TextBlock::operator[]
    const TextBlock ctb ("World");
    std::cout << ctb[0] << "\n";                    // calls const TextBlock::operator[]
    // 通过重载operator[]，而且给不同的版本不同的返回类型，你能对 const 和 non - const 的 TextBlocks 做不同的操作
    tb[0] = 'x';
    // ctb[0] = 'x';   //!error const char& 不应该被修改

    char carray [] = "Hello";
    //char* array = "World";//!error 对于C风格的字符串字面量，在C++中是const char[strlen(string)+1]，应该使用const char*接收
    const CTextBlock c_tb (carray); //?即便是一个const对象，通过返回引用，并且还是调用了const member function，我们还是改变了对象的值
    c_tb[1] = 'a';
    std::cout << c_tb.GetString () << std::endl;    //打印Hallo

    char tmp [] = "World";
    MyTextBlock myTextBlock (tmp);
    // std::cout << "myTextBlock: " << myTextBlock.GetString ()[0] << std::endl;
    std::cout << "myTextBlock: " << myTextBlock[0] << std::endl;
}