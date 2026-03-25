#include <iostream>
#include <string>
#include <optional>
#include <string_view>
#include <charconv>

#include "trim.h"   // dependency: trim

#include "split_string.h"

std::optional<int> ParseInt ( std::string_view sv )
{
    int value = 0;
    auto [ptr, ec] = std::from_chars ( sv.data (), sv.data () + sv.size (), value );
    if ( ec == std::errc () )
    {
        return value;
    }
    return std::nullopt;
}

int STDOptional ()
{
    auto value = ParseInt ( "1234" );
    std::cout << value.value () << std::endl;

    value = ParseInt ( "dfasfa" );  // Illigal

    if ( value.has_value () )
    {
        std::cout << *value << std::endl;
    } else
    {
        std::cerr << "Error providing the string." << std::endl;
    }

    value = ParseInt ( "dfasfa" ).value_or ( 0 ); // 在没有值时，给出默认情况 0
    std::cout << value.value () << std::endl;

    value = ParseInt ( "dfasfa" );
    std::cout << value.value () << std::endl;   // 强行使用，标准库中抛出异常 what():  bad optional access

    // std::optional 缺点是不能够携带失败的信息

    return 0;
}

// std::string_view
// 为什么需要这个？
// std::string 传参意味着一次拷贝和一次内存分配
// const std::string& 虽然避免了拷贝，但限制了调用方的类型     const std::string& temp = "Hello World";    // 即便是类似这种方式进行函数调用，仍然会有一次临时对象的构造
// C 风格的字符串不安全，长度未知

// 什么是std::string_view
// 指向字符串序列的一段视图
// 内部只保存指针加长度，不拥有内存，不负责生命周期管理
// 几乎零开销，可按值传递

// fadsfdas HOFDASFD JOjooj 
// 想要拿到 HOFDASFD 这个字符串，我们通过 std::string_view 就能得到一个 const char* buffer_ptr = "H" size=8 的一个string_view 对象
std::string_view sv = "Hello C++";  // 持有在 .data 段的一个字符串视图

std::string source = "Hello string in heap";
std::string_view stringSourceView ( source );

const char buf [ ] = { 'A','B' };
std::string_view stringArrayView ( buf, 2 );

// 构造std::string_view 的方式：1. 通过在.data段的字符串 2. 通过已经存在的字符串 3. 通过字符数组
#define USE_STRING_VIEW

#ifdef USE_STRING_VIEW
std::string_view RemoveOnePrefix ( const std::string_view& sv )
{
    return sv.substr ( 1 );
}
#else
std::string RemoveOnePrefix ( const std::string& s )    // 这可能是我们常常优先考虑的，但是实际上开销较大
{
    return s.substr ( 1 );
}
#endif

int main ()
{
    auto fruit = std::string { "apple" };
    std::cout << RemoveOnePrefix ( fruit ) << std::endl;

    std::string_view sv = std::string { "Temp" };   // 通过临时对象构造 std::string_view ERROR: 不负责生命周期的管理
    std::cout << "UB" << sv << std::endl;

    // 我们也能够通过 std::string_view 构造一个 std::string 的一个副本，这是在考虑到生命周期时考虑的
    std::string stringBak ( sv );

    // 不要返回指向局部 string 的 std::string_view
    // std::string_view 是一个观察者，而非容器
    // 零拷贝，只读，生命周期敏感，优先考虑 std::string_view
 
    std::cout << cxx_utils::string::trim ( "   jojojo ho \t \n  ", cxx_utils::string::TrimPolicy::both ) << std::endl;  // for trim

    std::string test { "key=value" };

    auto result = cxx_utils::string::split ( test, '=' );

    for (const auto& i:result)
    {
        std::cout << i << std::endl;
    }
    
    return 0;
}