#include <iostream>
#include <fstream>
#include <memory>
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

    auto io = std::make_unique<IO>(args[1]);
    auto token = CLexer::get_next_token(io->ifs);
    while(token)
    {
        std::cout << token->to_string() << std::endl;
        token = CLexer::get_next_token(io->ifs);
    }
    return(0);
}
