#pragma once
#include <string>

namespace pasc
{
    class CError
    {    
    public:
        std::string msg;
        CError(const std::string &err_msg);
    };
}