#include <cstdio>
#include <iostream>
#include <memory>

#include "clexer.hpp"
#include "ctoken.hpp"
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
    auto lexer = std::make_unique<CLexer>(io);
    token_ptr token = lexer->get_next_token();
    while(token)
    {
        std::cout << token->to_string() << std::endl;
        token = lexer->get_next_token();
        std::getchar();
    }
    return(0);
}
