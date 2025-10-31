/* ---------------------------------------------------------------------------------------------- */
/*                                          只要可能就用 const                                       */
/* ---------------------------------------------------------------------------------------------- */

#include <vector>
#include <iterator>
#include <cstring>

//const
//在类的外部：global/namespace 中声明const常量，包括static变量同样可以使用const进行修饰

//在内的内部，可以声明member function和data members 

//对于指针，可以声明两种const：const pointer/point to const

char greeting [] = "Hello";

char* p1 = greeting; // non-const pointer,

const char* p2 = greeting; // point to const

char* const p3 = greeting; // const pointer,

const char* const p4 = greeting; // const pointer,const data

/* --------------------------------------- const与iterator --------------------------------------- */

// STL iterators（迭代器）以 pointers（指针）为原型，所以一个 iterator 在行为上非常类似于一个 T* pointer（指针）
// 因此也可以分为能够指向const以及指向特定值的const_iterator
void Foo ()
{
    std::vector<int> vec (10 , 2);

    const std::vector<int>::iterator iter = vec.begin ();
    *iter = 10;
    // ++iter;                                     //!error iterator指向的位置不可变

    std::vector<int>::const_iterator cIter = vec.begin ();
    // *cIter = 10;                              
    ++cIter;                                        //!error const_iterator表示指向的值不可变

    auto it = vec.cbegin ();    //cbegin返回的就是const_iterator
}

// 关于 const parameters（参数）没什么特别新鲜之处——它们的行为就像 local（局部）的 const objects（对象），而且无论何时，只要你能，你就应该这样使用。

/* ------------------------------------ const与member function ----------------------------------- */
// 成员函数被声明为 const 的目的是标明这个成员函数可能/或者说要求 被 const 对象调用。
// 成员函数在 constness 常量性不同时是可以被重载的。
class TextBlock
{
public:
    TextBlock (std::string nText)
        :text (nText)
    {
    }

public:
    //...
    const char& operator[](std::size_t position) const   // operator[] for const objects
    {
        return text[position];
    }

    // 返回的是 reference 如果返回的是char 那么类似于const char& ，我们也不能够修改text中的值
    char& operator[](std::size_t position)               // operator[] for non-const objects
    {
        return text[position];
    }

private:
    std::string text;
};

/* ----------------------------- bitwise constness和logical constness ---------------------------- */

    /* -------------------------------------- BITWISE CONSTNESS ------------------------------------- */
// 假设是C风格的API，我们的代码与之交互
class CTextBlock
{
public:
    CTextBlock (char* nText)
        :pText (nText)
    {

    }

public:
    char* GetString () const
    {
        return pText;
    }

    char& operator[](std::size_t position) const   // 不合适的声明，返回普通引用形式，但却声明为const member function
    {
        return pText[position];
    }                    // const declaration of operator[]

    std::size_t length () const
    {
        if (!lengthIsValid)
        {
            textLength = std::strlen (pText);  // error! can't assign to textLength and lengthIsValid in a const
            lengthIsValid = true;
        }

        return textLength;
    }
private:
    char* pText;
    mutable std::size_t textLength;             // 添加const以便能够在const成员函数中使用
    mutable bool lengthIsValid;                 // whether length is currently valid
};

/* -------------------------------------- LOGICAL CONSTNESS ------------------------------------- */

//const member function可能会改变调用它的对象中的一些 bits ，但是只能用客户无法察觉的方法.
//仍以上述代码为例：
//添加mutable关键字以更加符合逻辑常量性。bitwise constness是编译器方面的检查，但是更加符合我们人类直觉的其实是logical constness
//mutable就是为了打破编译器的限制，让我们编写出符合logical constness的代码

class MyTextBlock
{
public:
    MyTextBlock (char* nText)
        :text (nText)
    {

    }

    const char& operator[](std::size_t position) const
    {
        return text[position];
    }

    char& operator[](std::size_t position)
    {
        //...
        //return text[position];
        // 在实际开发中，该函数内还会有其他业务逻辑，很不幸的是，如果我们通过以上的方式实现该函数，那么我们就需要维护两份代码
        // 在设计中，在使用const成员函数并且进行重载时，都使用以下的这种方式！
        // 代码中不能仅仅调用operator[]，否则会导致递归调用

        // return const_cast< char& >(this->text[position]);           // !注意：这里调用的是std::string类中重载的operator[]
        // return const_cast< char& >((*this)[0]);                     // 对于non-const使用this->operator[0]会导致递归调用
        // return const_cast< char& >(this->operator[](0));            // 等价形式
        return const_cast< char& >(static_cast< const MyTextBlock& >(*this)[position]);
    }

    const std::string GetString () const
    {
        return text;
    }

private:
    // char* text;  //对于char*类型调用operator时，调用的还是build-in数组形式的索引[index]
    std::string text;
};

/* ---------------------------------------------------------------------------------------------- */
//以上方法在开发时特别常用，我们称：
//------------------->根据non-const member function调用它的const 版本
//但是反过来不行，在 const member function 中调用 non-const 函数中是有可能改变对象的状态，这与我们承诺的调用 const member function 不改变对象状态冲突.