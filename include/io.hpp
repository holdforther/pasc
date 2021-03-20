#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace pasc
{
    enum io_mode
    {
        file,
        console
    };

    class IO
    {
    private:
        io_mode mode;
        std::string input_name;
    public:
        IO(const std::string &name, const io_mode mode);
        static std::string get_program_text(std::istream &is);
    };
}