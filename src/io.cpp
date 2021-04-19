#include "io.hpp"
#include <string>

namespace pasc {
    IO::IO(const std::string &input_file_name) : ifs(input_file_name, std::ios::in) {
        row_index = 0;
        column_index = 0;
        std::getline(ifs, line_buf);
        while (line_buf.empty() && !ifs.eof()) {
            std::getline(ifs, line_buf);
            row_index++;
        }
    }

    char IO::get_char() {
        if(column_index >= line_buf.length()) {
            if (ifs.eof()) {
                return '\0';
            } else {
                column_index = 0;
                row_index++;
                std::getline(ifs, line_buf);
                while (line_buf.empty() && !ifs.eof()) {
                    std::getline(ifs, line_buf);
                    row_index++;
                }
                return '\n';
            }
        }
        return line_buf[column_index++];
    }

    char IO::peek_char() {
        if (column_index < line_buf.length()) {
            return line_buf[column_index];
        }
        return ifs.eof() ? '\0' : '\n';
    }

    size_t IO::get_col_index() const {
        return column_index;
    }

    size_t IO::get_row_index() const {
        return row_index;
    }
}