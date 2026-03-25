#include "split_string.h"

namespace cxx_utils {
    namespace string {
        std::vector<std::string> split ( const std::string& src, const char symbol )
        {
            // key = value
            static constexpr std::size_t START_POS = 0;
            std::size_t currentPosition = src.find ( symbol, START_POS );
            std::size_t lastIndex = START_POS;
            std::vector<std::string> vec;

            while ( currentPosition != std::string::npos )
            {
                vec.emplace_back ( src.substr ( /*START_POS*/lastIndex, currentPosition - START_POS ) );
                vec.emplace_back ( 1, symbol );
                lastIndex = ++currentPosition;
                currentPosition = src.find ( symbol, lastIndex );
            }
            vec.emplace_back ( src.substr ( lastIndex ) );

            return vec;
        }
    }
}