#pragma once
#include <fstream>
#include <memory>
#include <string>
#include <sstream>

#include "ctoken.hpp"
#include "io.hpp"

namespace pasc
{
    class CLexer
    {
    public:
        std::string Expr;
        io_ptr io;
        static token_ptr get_next_token();
    };
}

/*
*/
