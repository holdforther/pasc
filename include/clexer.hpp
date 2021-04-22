#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "cerror.hpp"
#include "ctoken.hpp"
#include "io.hpp"

namespace pasc
{
    enum lexeme_type {
        lt_unknown,
        lt_int_const,
        lt_real_const,
        lt_str_const,
        lt_identifier
    };

    class CLexer
    {
        io_ptr io;
        size_t token_row_pos;
        size_t token_col_pos;
        std::unordered_map<std::string, token_operator> key_words;
        bool is_service_symbol(char symbol);
        void skip_spaces();
        token_ptr get_parsed_token(size_t row_pos, size_t col_pos, lexeme_type ltype, const std::string &lexeme, CError &error);
    public:
        CLexer(io_ptr &io);
        token_ptr get_next_token(CError &error);
        size_t get_token_row() const;
        size_t get_token_col() const;
        bool is_end_of_stream();
    };

    typedef std::unique_ptr<CLexer> lexer_ptr;
}
