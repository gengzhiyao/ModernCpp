#include "trim.h"

std::string_view cxx_utils::string::trim ( const std::string_view sv, const TrimPolicy trimPolicy )
{
    // 思路：
    // 找到第一个非空白字符的 index
    // 从后往前找：第一个非空白字符的index
    // [f,e] 将这个区间内的字符串交过去
    if ( sv.empty () ) return sv;

    std::size_t end = sv.size ();
    std::size_t start = 0;

    if ( trimPolicy == TrimPolicy::both || trimPolicy == TrimPolicy::left )
    {
        while ( start < end && isSpaceChar ( sv[start] ) )
        {
            ++start;
        }
    }

    if ( trimPolicy == TrimPolicy::both || trimPolicy == TrimPolicy::right )
    {
        while ( end > start && isSpaceChar ( sv[end-1] ) )
        {
            --end;
        }
    }

    return sv.substr ( start, end - start );

}