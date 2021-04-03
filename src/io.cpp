#include "io.hpp"

pasc::IO::IO(const std::string &input_file_name)
{
    fname = input_file_name;
    ifs = std::make_unique<std::ifstream>(input_file_name, std::ios::in);
}

std::string pasc::IO::get_program_text()
{
    ifs->seekg(0, ifs->end);
    int length = ifs->tellg();
    ifs->seekg(0, ifs->beg);
    char *buffer = new char [length];
    ifs->read(buffer, length);
    std::string text(buffer);
    delete[] buffer;
    return text;
}

std::string pasc::IO::get_lexeme()
{
    std::string lexeme;
    (*ifs) >> lexeme;
    return lexeme;
}
