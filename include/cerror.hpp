#pragma once
#include <string>
#include <vector>

#include "ctoken.hpp"

namespace pasc
{
    enum error_code {
        eec_no,
        // Lexical errors
        eec_out_of_range,
        // Syntactic errors
        eec_exp_program,
        eec_exp_identifier,
        eec_exp_semicolon,
        eec_exp_value,
        eec_exp_end,
        eec_exp_period,
        eec_exp_colon,
        eec_exp_comma,
        eec_exp_left_parenthesis,
        eec_exp_right_parenthesis,
        eec_exp_assignment,
        eec_exp_procedure,
        eec_invalid_operator,
        eec_exp_begin,
        eec_unknown
    };

    struct CError
    {
        size_t row;
        size_t col;
        error_code code;
        CError() : row(0), col(0), code(eec_no) {}
        CError(size_t row, size_t col) : row(row), col(col), code(eec_no) {} 
        CError(size_t row, size_t col, error_code code) : row(row), col(col), code(code) {}
        std::string to_string() const;
    };
    
    typedef std::vector<CError> ErrorList;
}