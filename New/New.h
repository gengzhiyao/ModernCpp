#include <new>
#include <iostream>

/* ---------------------------------------------------------------------------------------------- */
/*                                       new和operator new说明                                       */
/* ---------------------------------------------------------------------------------------------- */
/**
 *@brief new是一个关键字，和其他关键字一样，如sizeof等等，我们是无法该表new关键字的功能的。
 * new关键字做三件事：1. 分配内存空间 2. 调用构造函数初始化对象 3. 返回一个指向所分配内存空间的指针
 * 其中，分配内存空间的工作由operator new完成。
 * 因此，在这里需要澄清：new是关键字；operator new是函数，我们能够重载的只是operator new这个函数，让new关键字(运算符)在分配内存的时候调用我们重载的operator new函数
 * placement new是operator new的一种重载形式，在已经分配的内存空间上面构造一个新的对象；
 * operator new函数的第一个形参必须是size_t，返回值必须是void*类型。C++标准并没有规定operator new除第一个参数为size_t之外，参数列表中还可以有多少个形参
 * 对于opeartor new(size_t,void* ptr)这种类型的重载，就是placement new的形式了，它会在ptr所指向的堆内存中构造一个新的对象，在构造新对象时，会将原来存在的数据覆盖掉。
 * 对用重载operator delete new[] delete[] 等等情况和上述机理类似。
 */

struct New
{
private:
    int m_data;
public:
    void* operator new(std::size_t size)
    {
        std::cout << "operator new" << std::endl;
        return malloc (size);
    }

    void* operator new(std::size_t , void* ptr)
    {
        std::cout << "placement new" << std::endl;
        return ptr;
    }
    void SetData (int data)
    {
        m_data = data;
    }
    int GetData ()
    {
        return m_data;
    }

    explicit New (int data)
        :m_data(data){}

};
