#pragma once

#include <string_view> // dependency: string_view
#include <string>   // dependency: string

// std::string::trim 的作用：
// 去掉字符串开头和结尾的空白字符，中间的空白字符不动 空白字符包括 空格/制表符/换行/回车

// trim:  "   jojojo ho \t \n  "

namespace cxx_utils {
    namespace string {
        enum class TrimPolicy
        {
            left,
            right,
            both
        };

        std::string_view trim ( const std::string_view sv, const TrimPolicy trimPolicy );

        inline const bool isSpaceChar ( const char ch ) // 注意重复包含和重复定义的区别：重复包含指的是多重声明，如结构体/类的多重声明；但重定义是在多个.o文件中存在多个函数实现的副本
        {
            return std::isspace ( ch ) != 0;
        }
    }
}   // namespace cxx_utils

