#include <iostream>
#include <fstream>
#include <string>

#include "clexer.hpp"
#include "io.hpp"

using namespace pasc;

int main(int argc, char **args)
{
    if (argc != 2)
    {
        std::cout << "Provide single Pascal source file\n";
        return(-1);
    }
    IO io_module(args[1]);

    auto token = CLexer::get_next_token(io_module.ifs);
    while(token)
    {
        std::cout << token.to_string() << std::endl;
        token = CLexer::get_next_token(is);
    }

    return(0);
}