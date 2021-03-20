#include "io.hpp"

pasc::IO::IO(const std::string &input_name, const io_mode mode)
{
    this->mode = mode;
    this->input_name = input_name;
}

std::string pasc::IO::get_program_text(std::istream &is)
{
    is.seekg(0, is.end);
    int length = is.tellg();
    is.seekg(0, is.beg);
    char *buffer = new char [length];
    is.read(buffer, length);
    std::string text(buffer);
    delete[] buffer;
    return text;
}