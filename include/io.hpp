#pragma once
#include <fstream>
#include <memory>
#include <string>

#include <cerror.hpp>

namespace pasc
{
    typedef std::unique_ptr<std::ifstream> ifstream_ptr;

    class IO
    {
    private:
        std::string fname;
        ifstream_ptr ifs;
        caret_position caret;
    public:
        IO(const std::string &input_file_name);
        ifstream_ptr get_ifs();
        char get_char();
        char peek_char();
        caret_position get_pos() const {return this->caret;}
    };
    typedef std::unique_ptr<IO> io_ptr;
}
// Пропускаем комментарии и сплитим по спецсимволам
