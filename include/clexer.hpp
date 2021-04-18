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
        io_ptr io;
    public:
        CLexer(io_ptr io);
        token_ptr get_next_token();
    };
}
