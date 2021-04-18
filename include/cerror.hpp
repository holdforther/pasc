#pragma once
#include <string>
#include <vector>

namespace pasc
{
    struct caret_position
    {
        unsigned nline;
        unsigned ncol;  
    };
    
    enum error_type
    {
        no_errors
    };

    struct ErrorList
    {
        std::vector<int> codes;
        std::vector<size_t> rows;
        std::vector<size_t> cols;
    };
}