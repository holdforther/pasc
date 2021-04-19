#include "ctoken.hpp"

namespace pasc {
    CToken::CToken() {
        id = "";
        val = nullptr;
    }
    CToken::CToken(variant_ptr &value) {
        type = ett_value;
        id = value->to_string(); 
        val = std::move(value);
    }
    CToken::CToken(const std::string &identifier) {
        type = ett_identifier;
        id = identifier;
    }
    

    CToken::CToken(token_operator _operator) {
        type = ett_operator;
        op = _operator;
        id = std::to_string(_operator);
    }   

    static std::unordered_map<token_operator, std::string> op_repr {
        {eto_and, "AND"},
        {eto_array, "ARRAY"},
        {eto_assignment, ":="},
        {eto_asterisk, "*"},
        {eto_begin, "BEGIN"},
        {eto_case, "CASE"},
        {eto_colon, ":"},
        {eto_comma, ","},
        {eto_const, "CONST"},
        {eto_div, "DIV"},
        {eto_do, "DO"},
        {eto_double_period, ".."},
        {eto_downto, "DOWNTO"},
        {eto_else, "ELSE"},
        {eto_end, "END"},
        {eto_equal, "="},
        {eto_file, "FILE"},
        {eto_for, "FOR"},
        {eto_function, "FUNCTION"},
        {eto_goto, "GOTO"},
        {eto_greater_equal, ">="},
        {eto_greater_than, ">"},
        {eto_if, "IF"},
        {eto_in, "IN"},
        {eto_label, "LABEL"},
        {eto_left_bracket, "["},
        {eto_left_curly_bracket, "{"},
        {eto_left_multicomment, "(*"},
        {eto_left_parenthesis, "("},
        {eto_less_equal, "<="},
        {eto_less_than, "<"},
        {eto_minus, "-"},
        {eto_mod, "%"},
        {eto_nil, "NIL"},
        {eto_not, "NOT"},
        {eto_not_equal, "<>"},
        {eto_of, "OF"},
        {eto_or, "OR"},
        {eto_packed, "PACKED"},
        {eto_period, "."},
        {eto_plus, "+"},
        {eto_pointer, "^"},
        {eto_procedure, "PROCEDURE"},
        {eto_program, "PROGRAM"},
        {eto_record, "RECORD"},
        {eto_repeat, "REPEAT"},
        {eto_right_bracket, "]"},
        {eto_right_curly_bracket, "}"},
        {eto_right_multicomment, "*)"},
        {eto_right_parenthesis, ")"},
        {eto_semicolon, ";"},
        {eto_set, "SET"},
        {eto_slash, "/"},
        {eto_then, "THEN"},
        {eto_to, "TO"},
        {eto_type, "TYPE"},
        {eto_until, "UNTIL"},
        {eto_var, "VAR"},
        {eto_while, "WHILE"},
        {eto_with, "WITH"}
    };

    std::string CToken::to_string() const {
        switch (type) {
        case ett_operator: {
            std::string oper_repr = op_repr.find(op) != op_repr.end() ? op_repr[op] : "UNKNOWN"; 
            return "Operator " + oper_repr;
        }
        case ett_value: {
            return "Value " + val->to_string();
        }
        default: {
            return "Identifier " + id;
        }
        }
    }
}
