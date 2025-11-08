#pragma once
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

template<typename T>
T MaxValue (T a , T b)
{
    std::cout << "[Type:] T ->" << typeid(T).name () << std::endl;
    return a > b ? a : b;
}

//聚合初始化的核心逻辑是：编译器不调用任何构造函数，直接将初始化列表中的值 “按顺序” 赋值给聚合类型的 “公有非静态数据成员”。
template<typename T , int N>
struct FixedArray
{
    T array[N];
    const T operator[](/* int */std::size_t index) const
    {
        return array[index];
    }
};

//模板模板参数
template<template<typename , typename> class Container , typename T>
struct ContainerPrinter
{
    void Print (const Container<T , std::allocator<T>>& container)
    {
        for (const auto& i : container)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
};


//通用模板类
template<typename T , typename Enable = void>
class Logger
{
public:
    static void log (const T& value)    //通用
    {
        std::cout << "General Logger: " << value << std::endl;
    }
};

//模板偏特化，当T是指针类型
template<typename T>
class Logger<T , typename std::enable_if<std::is_pointer<T>::value>::type>
{
public:
    static void log (T& value)
    {
        if (value)
        {
            std::cout << "Pointer Logger: " << *value << std::endl;
        } else
        {
            std::cout << "Pointer Logger: std::nullptr_t" << std::endl;
        }

    }
};

//全特化 当T是std::string类型
template<>
class Logger<std::string>
{
public:
    static void log (const std::string& value)
    {
        std::cout << "std::string Logger: " << value << std::endl;
    }
};

//函数模板：用于递归调用Logger::log
template<typename T>
void logOnce (/* const */ T& value)
{
    Logger<T>::log (value);
}

//使用模板折叠表达式实现可变参数列表打印
template<typename... Args>
void logAll (/* const */ Args&... args)
{
    (logOnce (args) , ...);
}

/* ---------------------------------------------------------------------------------------------- */
/*             无参普通函数 PrintAll () 和模板函数 PrintAll (const First& , const Args&...) 构成重载；  */
/* ---------------------------------------------------------------------------------------------- */
//是重载而非特化
inline void PrintAll ()
{
    std::cout << std::endl;
}

//因为参数包的类型完全是可以不同的，因此PrintAll函数可以构成多个重载形式的函数
template<typename First , typename... Args>
void PrintAll (const First& first , const Args&... args)
{
    std::cout << first << " ";
    PrintAll (args...);    //NOTE - 递归调用，参数包展开，直到展开到没有，随后会调用无参版本的PrintAll
}

//左折叠
template<typename... Args>
auto leftSumAll (const Args&... args) -> decltype((args + ...))
{
    return (args + ...);
}

template<typename... Args>
auto rightSumAll (const Args&... args) -> decltype((... + args))
{
    return (... + args);
}

template<int N>
struct Factorial
{
    static const int value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<0>
{
    static const int value = 1; //非const的static成员变量必须在类外初始化，即便是在类内进行了初始化，但是在类外使用是是不能够取地址的，编译器只是将用到value的地方当做一个字面量使用
};

/* ---------------------------------------------------------------------------------------------- */
/*                                           类外static定义                                        */
/* ---------------------------------------------------------------------------------------------- */
template<int N>
const int Factorial<N>::value;

template<int N>
struct Fibonacci
{
    inline static const int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

template<>
struct Fibonacci<0>
{
    inline static const int value = 0;
};

template<>
struct Fibonacci<1>
{
    inline static const int value = 1;
};

template<typename T , typename = void>
struct is_addable :std::false_type
{

};

template<typename T >
struct is_addable < T , decltype(void (std::declval<T> () + std::declval<T> ()))> :std::true_type//std::declval<T> () 返回一个T类型的右值引用，不创建实际类型的对象
{

};


template<typename...Ts>
struct TypeList
{

};


//获取类型列表中第N个类型
template<typename List , std::size_t N>
struct TypeAt;

template<typename Head , typename... Tail>
struct TypeAt<TypeList<Head , Tail...> , 0>
{
    using type = Head;
};

template<typename Head , typename... Tail , std::size_t N>
struct TypeAt<TypeList<Head , Tail...> , N>
{
    using type = typename TypeAt<TypeList<Tail...> , N - 1>::type;
};


