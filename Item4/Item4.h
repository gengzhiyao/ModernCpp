/* ---------------------------------------------------------------------------------------------- */
/*                                          确保对象在使用前被初始化                                   */
/* ---------------------------------------------------------------------------------------------- */

#include <iostream>
#include <list>

// 对于C-Style类型的build-in类型，尤其需要注意初始化，特别是对于数组形式. 另外，对于内置类型，是否进行初始化还需要考虑变量的位置，例如全局变量会自动进行初始化.
// 对于build-in type, 我们需要对变量手动进行初始化
void Foo ()
{
    int x = 0;                                // manual initialization of an int

    const char* text = "A C-style string";    // manual initialization of a

    double d;                                 // "initialization" by reading from an input stream

    std::cin >> d;  
}

// 但是对于用户自定义数据类型，初始化的责任就落到了构造函数中. 规则很简单：确保你的constructor初始化了其所有成员！
// !C++ 的规则规定一个 object（对象）的 data members（数据成员）在进入 constructor（构造函数）的函数体之前被初始化。

class PhoneNumber { /* ... */ };

class ABEntry   // ABEntry = "Address Book Entry"
{                         
public:

    ABEntry (const std::string& name , const std::string& address ,
        const std::list<PhoneNumber>& phones);

private:

    std::string theName;

    std::string theAddress;

    std::list<PhoneNumber> thePhones;

    int numTimesConsulted;

};

ABEntry::ABEntry (const std::string& name , const std::string& address ,
    const std::list<PhoneNumber>& phones)
// ?在进入函数体之前，已经调用了data member的默认构造函数，但是对于numTimesConsulted来说，是build-in type ，无法保证它在被assignment之前被初始化
{
/* ----------------------------------------- assignments ---------------------------------------- */
    // theName = name;                       // these are all assignments,

    // theAddress = address;                 // not initializations

    // thePhones = phones;

    // numTimesConsulted = 0;
/* ----------------------------------------- assignments ---------------------------------------- */
}
// 另外：对于build-in type，一些情况下必须要在initialization list中进行初始化，如reference / const data member

// data member 初始化顺序：按照用户声明的顺序进行初始化，而不是构造函数初始化列表中的顺序进行初始化

// !需要注意的是：定义在不同编译单元的非局部静态对象的初始化顺序是不受控的，just like global/namespace/static in class/file scope object
// !the relative order of initialization of non-local static objects defined in different translation units is undefined
// !如果其中一个 translation unit（转换单元）内的一个 non-local static object（非局部静态对象）的 initialization（初始化）用到另一个 translation unit（转换单元）内的non-local static object（非局部静态对象），它所用到的 object（对象）可能没有被初始化