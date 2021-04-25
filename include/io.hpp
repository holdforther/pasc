#pragma once
#include <fstream>
#include <memory>
#include <string>

#include "cerror.hpp"

namespace pasc
{
    class IO
    {
    private:
        std::ifstream ifs;
        std::string line_buf;
        size_t row_index;
        size_t column_index;
        ErrorList errors;
    public:
        IO(const std::string &input_file_name);
        char get_char();
        char peek_char();
        size_t get_row_index() const;
        size_t get_col_index() const;
        bool is_eof();
        void add_error(const CError &error);
        size_t get_errors_size() const;
        ErrorList get_errors() const;
    };
    typedef std::shared_ptr<IO> io_ptr;
} // namespace pasc