#pragma once
#include <fstream>
#include <memory>
#include <string>
#include <sstream>

#include "ctoken.hpp"

namespace pasc
{
    class CLexer
    {
    public:
        std::string Expr;
        static token_ptr get_next_token(std::unique_ptr<std::ifstream> &ifs);
    };
}
