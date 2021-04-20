#include "cerror.hpp"
#include <unordered_map>

namespace pasc {
    std::unordered_map<error_code, std::string> code_repr {
        {eec_out_of_range, "too many symbols for an identifier"},
        {eec_exp_program, "expected \'PROGRAM\'"},
        {eec_exp_begin, "expected \'BEGIN\'"},
        {eec_exp_end, "expected \'END\'"},
        {eec_exp_identifier, "expected identifier"},
        {eec_exp_period, "expected \'.\'"},
        {eec_exp_comma, "expected \',\'"},
        {eec_exp_colon, "expected \':\'"},
        {eec_exp_semicolon, "expected \';\'"},
        {eec_exp_double_period, "expected \'..\'"},
        {eec_exp_assignment, "expected \':=\'"},
        {eec_exp_left_parenthesis, "expected \'(\'"},
        {eec_exp_right_parenthesis, "expected \')\'"},
        {eec_exp_then, "expected \'THEN\'"},
        {eec_exp_do, "expected \'DO\'"},
        {eec_exp_equal, "expected \'EQUAL\'"},
        {eec_exp_record, "expected \'RECORD\'"},
        {eec_exp_until, "expected \'UNTIL\'"},
        {eec_invalid_operator, "invalid operator"},
        {eec_unknown, "unknown error"}
    };

    std::string CError::to_string() const{
        return code_repr.find(code) != code_repr.end() ? code_repr[code] : "UNKNOWN";
    }
}