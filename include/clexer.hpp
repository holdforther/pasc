#pragma once
#include "ctoken.hpp"
#include <string>
#include <sstream>

namespace pasc
{
    class CLexer
    {
    private:
        int pos;
    public:
        std::string Expr;
        // CLexer(std::string Expr);
        static CToken get_next_token(std::istream &is);
    };
}
