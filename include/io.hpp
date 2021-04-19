#pragma once
#include <fstream>
#include <memory>
#include <string>

#include <cerror.hpp>

namespace pasc
{
    class IO
    {
    private:
        std::ifstream ifs;
        std::string line_buf;
        size_t row_index;
        size_t column_index;
    public:
        IO(const std::string &input_file_name);
        char get_char();
        char peek_char();
        size_t get_row_index() const;
        size_t get_col_index() const;
    };
    typedef std::unique_ptr<IO> io_ptr;
} // namespace pasc