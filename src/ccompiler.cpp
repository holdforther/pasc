#include <iostream>
#include <fstream>
#include <string>

#include "clexer.hpp"

using namespace pasc;

int main(int argc, char **args)
{
    if (argc != 2)
    {
        std::cout << "Provide single Pascal source file\n";
        return(-1);
    }
    std::ifstream is(args[1], std::ifstream::in); 
    if(!is)
    {
        std::cout << "Can't open file\n";
        return(-1);
    }
    
    auto token = CLexer::get_next_token(is);
    while(token)
    {
        std::cout << token.to_string() << std::endl;
        token = CLexer::get_next_token(is);
    }
    
    is.close();
    return(0);
}