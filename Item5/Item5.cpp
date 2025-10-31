#include "Item5.h"

int main ()
{
    std::string newDog ("Persephone");

    std::string oldDog ("Satch");

    NamedObject<int> p (newDog , 2);

    NamedObject<int> s (oldDog , 36);

    //!编译器拒绝为我们生成拷贝赋值运算符！
    //!为什么呢？
    // 如果生成拷贝赋值运算符，那么会产生以下现象：
    // p.nameValue=s.nameValue; 但是！这两个都是引用，引用一旦绑定就不可以解绑或者绑定其他对象
    // 这意味着什么？
    // p = s; 
    //! 如果你希望一个包含引用成员的class支持赋值，你必须自己定义 copy assignment operator（拷贝赋值运算符）。
    //! 对于含有 const members的 classe类，编译器会有类似的行为。
    //! 最后，如果基类将拷贝赋值运算符声明为 private，编译器拒绝为从它继承的派生类合成拷贝赋值运算符。因为在派生类进行赋值时，基类部分需要调用基类部分的拷贝赋值运算符！
}