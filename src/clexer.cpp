#include <cstring>
#include <locale>
#include <sstream>
#include <stdexcept>

#include "cerror.hpp"
#include "clexer.hpp"
#include "io.hpp"

namespace pasc {
    CLexer::CLexer(const io_ptr &io) {
        this->io = io;
        key_words = std::unordered_map<std::string, token_operator>{
            {"AND", pasc::eto_and},
            {"ARRAY", pasc::eto_array},
            {":=", pasc::eto_assignment},
            {"*", pasc::eto_asterisk},
            {"BEGIN", pasc::eto_begin},
            {"CASE", pasc::eto_case},
            {":", pasc::eto_colon},
            {",", pasc::eto_comma},
            {"CONST", pasc::eto_const},
            {"DIV", pasc::eto_div},
            {"DO", pasc::eto_do},
            {"..", pasc::eto_double_period},
            {"DOWNTO", pasc::eto_downto},
            {"ELSE", pasc::eto_else},
            {"END", pasc::eto_end},
            {"=", pasc::eto_equal},
            {"FILE", pasc::eto_file},
            {"FOR", pasc::eto_for},
            {"FUNCTION", pasc::eto_function},
            {"GOTO", pasc::eto_goto},
            {">=", pasc::eto_greater_equal},
            {">", pasc::eto_greater_than},
            {"IF", pasc::eto_if},
            {"IN", pasc::eto_in},
            {"LABEL", pasc::eto_label},
            {"[", pasc::eto_left_bracket},
            {"{", pasc::eto_left_curly_bracket},
            {"(*", pasc::eto_left_multicomment},
            {"(", pasc::eto_left_parenthesis},
            {"<=", pasc::eto_less_equal},
            {"<", pasc::eto_less_than},
            {"-", pasc::eto_minus},
            {"%", pasc::eto_mod},
            {"NIL", pasc::eto_nil},
            {"NOT", pasc::eto_not},
            {"<>", pasc::eto_not_equal},
            {"OF", pasc::eto_of},
            {"OR", pasc::eto_or},
            {"PACKED", pasc::eto_packed},
            {".", pasc::eto_period},
            {"+", pasc::eto_plus},
            {"^", pasc::eto_pointer},
            {"PROCEDURE", pasc::eto_procedure},
            {"PROGRAM", pasc::eto_program},
            {"RECORD", pasc::eto_record},
            {"REPEAT", pasc::eto_repeat},
            {"]", pasc::eto_right_bracket},
            {"}", pasc::eto_right_curly_bracket},
            {"*)", pasc::eto_right_multicomment},
            {")", pasc::eto_right_parenthesis},
            {";", pasc::eto_semicolon},
            {"SET", pasc::eto_set},
            {"/", pasc::eto_slash},
            {"THEN", pasc::eto_then},
            {"TO", pasc::eto_to},
            {"TYPE", pasc::eto_type},
            {"UNTIL", pasc::eto_until},
            {"VAR", pasc::eto_var},
            {"WHILE", pasc::eto_while},
            {"WITH", pasc::eto_with}
        };
        skip_spaces();
    }
    size_t CLexer::get_token_row() const {
        return token_row_pos;
    }
    size_t CLexer::get_token_col() const {
        return token_col_pos;
    }
    bool CLexer::is_end_of_stream() {
        return io->is_eof();
    }

    bool CLexer::is_service_symbol(char symbol) {
        const char* key_symbols = ".,;:^()[]=+-*/<>";
        return strchr(key_symbols, symbol) != nullptr;
    }
    
    void CLexer::skip_spaces() {
        while (std::isspace(io->peek_char())) {
            io->get_char();
        }
    }

    token_ptr CLexer::get_next_token() {
        enum scan_state {
            ss_start,
            ss_int,
            ss_real,
            ss_str,
            ss_identifier,
            ss_comment,
            ss_end,
        };
        std::stringstream lexeme_stream;
        size_t row_start = io->get_row_index();
        size_t col_start = io->get_col_index();
        scan_state state = ss_start;
        lexeme_type ltype = lt_unknown;
        while (state != ss_end) {
            char symbol = io->get_char();
            char next = io->peek_char();
            if (symbol == '(' && next == '*') {
                state = ss_comment;
            } else {
                lexeme_stream << symbol;
            }
            switch (state) {
            case ss_start: {
                if (symbol == '\0') {
                    state = ss_end;
                } else if (std::isdigit(symbol)) {
                    if (next == '.') {
                        state = ss_real;
                    } else if (!std::isdigit(next)) {
                        state = ss_end;
                        ltype = lt_int_const;
                    } else {
                        state = ss_int;
                    }
                } else if (std::isalpha(symbol) || symbol=='_') {
                    if (is_service_symbol(next) || std::isspace(next)) {
                        ltype = lt_identifier;
                        state = ss_end;
                    } else {
                        state = ss_identifier;
                    }
                } else if (symbol == '\'') {
                    state = ss_str;
                } else if (is_service_symbol(symbol)) {
                    if ((symbol == ':' && next == '=') || (symbol == '.' && next == '.') ||
                        (symbol == '<' && next == '>') || (symbol == '<' && next == '=') ||
                        (symbol == '>' && next == '=')) {
                            lexeme_stream << next;
                            io->get_char(); // Skip
                    }
                    ltype = lt_identifier;
                    state = ss_end;
                }
            } break;
            case ss_comment: {
                bool end_of_comment = false;
                io->get_char();
                while (!end_of_comment) {
                    end_of_comment = io->get_char() == '*' && io->peek_char() == ')';
                }
                io->get_char();
                skip_spaces();
                state = ss_start;
            } break;
            case ss_int: {
                if (next == '.') {
                    state = ss_real;
                } else if (!std::isdigit(next)) {
                    ltype = lt_int_const;
                    state = ss_end;
                }
            } break;
            case ss_real: {
                if (!std::isdigit(next)) {
                    ltype = lt_real_const;
                    state = ss_end;
                }
            } break;
            case ss_str: {
                if (symbol == '\'') {
                    ltype = lt_str_const;
                    state = ss_end;
                }
            } break;
            case ss_identifier: {
                if (is_service_symbol(next) || std::isspace(next)) {
                    ltype = lt_identifier;
                    state = ss_end;
                }
            } break;
            default: break;
            }
        }
        skip_spaces();
        return get_parsed_token(row_start, col_start, ltype, lexeme_stream.str());
    }

    token_ptr CLexer::get_parsed_token(size_t row_start, size_t col_start, lexeme_type ltype, const std::string &lexeme) {
        token_ptr token = nullptr;
        variant_ptr variant;
        CError error(row_start, col_start);
        switch (ltype) {
        // case lt_unknown: {
        //     error.code = eec_invalid_symbol;
        // } break;
        case lt_identifier: {
            std::string lexeme_copy(lexeme);
            for (auto & c: lexeme_copy) c = toupper(c);
            auto kw = key_words.find(lexeme_copy) != key_words.end() ? key_words[lexeme_copy] : eto_undefined;
            if (kw == eto_undefined) {
                token = std::make_unique<CToken>(row_start, col_start, lexeme);
            } else {
                token = std::make_unique<CToken>(row_start, col_start, kw);
            }
        } break;
        case lt_int_const: {
            long int value;
            try {
                value = std::stol(lexeme);
            }
            catch (const std::invalid_argument& ia) {
                error.code = eec_out_of_range;
                break;
            }
            catch (const std::out_of_range& oor) {
                error.code = eec_out_of_range;
                break;
            }
            variant = std::make_unique<CIntVariant>(value);
            token = std::make_unique<CToken>(row_start, col_start, variant);
        } break;
        case lt_real_const: {
            long double value;
            try {
                value = std::stold(lexeme);
            }
            catch (const std::invalid_argument& ia) {
                error.code = eec_out_of_range;
                break;
            }
            catch (const std::out_of_range& oor) {
                error.code = eec_out_of_range;
                break;
            }
            variant = std::make_unique<CRealVariant>(value);
            token = std::make_unique<CToken>(row_start, col_start, variant);
        } break;
        case lt_str_const: {
            std::string value = lexeme.substr(1, lexeme.size() - 2);
            if (value.size() == 1) {
                variant = std::make_unique<CCharVariant>(value[0]);
                token = std::make_unique<CToken>(row_start, col_start, variant);
            } else {
                variant = std::make_unique<CStringVariant>(value);
                token = std::make_unique<CToken>(row_start, col_start, variant);
            }
        } break;
        default: break;
        }
        io->add_error(error);
        return token;
    }
} // namespace pasc
