#pragma once
#include <fstream>
#include <memory>
#include <string>

namespace pasc
{
    typedef std::unique_ptr<std::filebuf> filebuf_ptr;
    typedef std::unique_ptr<std::ifstream> ifstream_ptr;

    class IO
    {
    private:
        filebuf_ptr fbuf;
    public:
        std::string fname;
        ifstream_ptr ifs;
        IO(const std::string &input_file_name);
        std::string get_program_text();
    };
}