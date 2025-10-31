/* ---------------------------------------------------------------------------------------------- */
/*                                     了解 C++ 为你偷偷地加上和调用了什么函数                          */
/* ---------------------------------------------------------------------------------------------- */

#include <iostream>
#include <string>

class Empty { };

#ifdef DEFAULTCTOR  // 模拟编译器为我们生成的默认特种成员函数
class Empty
{

public:

    Empty () { /* ... */ }                            // default constructor

    Empty (const Empty& rhs) { /* ... */ }            // copy constructor

    ~Empty () { /* ... */ }                           // destructor — see below for whether it's virtual

    Empty& operator=(const Empty& rhs) { /* ... */ }  // copy assignment operator

};
//!需要注意，编译器为我们生成的默认析构函数是否为virtual取决于他的父类是否是virtual destructor
#endif

//! 编译器生成的特种成员函数只有在我们需要的时候才会被合成出来.

template<typename T>
class SomeObject
{
public:
    SomeObject (const char* name , const T& value);
    SomeObject (const std::string& name , const T& value);

    /* ... */

private:
    std::string nameValue;
    T objectValue;
};

// 对拷贝构造函数和拷贝赋值运算符，编译器生成版本只是简单地从源对象拷贝每一个非静态数据成员到目标对象。遇到类类型data member时，再去调用data member对应的copy constructor/assignment 
// 对于build-in type，编译器将通过拷贝data member的每一个二进制位进行赋值。


/* -------------------------- 在未自定义特种成员函数的时候，编译器在某些情况下会拒绝为我们生成默认的特种成员函数 ------------------------- */
template<class T>
class NamedObject
{
public:

    // 该构造函数移除了以上代码中const类型的name形参，并将char*替换为了std::string，因为我们需要一个引用，char*无法做到
    NamedObject (std::string& name , const T& value)
        :nameValue (name) , objectValue (value)
    {

    }

    /* ... */                               // as above, assume no operator= is declared

private:
    std::string& nameValue;                 // this is now a reference
    const T objectValue;                    // this is now const
};