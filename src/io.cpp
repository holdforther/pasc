#include "io.hpp"

pasc::IO::IO(const std::string &input_file_name)
{
    fname = input_file_name;
    ifs = std::make_unique<std::ifstream>(input_file_name, std::ios::in);
}

char pasc::IO::get_char()
{
    char ch = ' ';
    ifs->get(ch);
    if (ch == '\n')
    {
        caret.nline++;
        caret.ncol = 1;
    }
    else
        caret.ncol++;
    return ch;
}

char pasc::IO::peek_char()
{
    return ifs->peek();
}