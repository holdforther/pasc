#include "ctoken.hpp"
#include <memory>
#include <string>

pasc::CToken::CToken(pasc::variant_ptr value)
{
    this->type = ett_value;
    this->value = std::move(value);
}

pasc::CToken::CToken(const std::string &identifier)
{
    this->type = ett_identifier;
    this->identifier = identifier;
}

pasc::CToken::CToken(pasc::token_operator oper)
{
    this->oper = oper;
    type = ett_operator;
}

static std::unordered_map<pasc::token_operator, std::string> operator_repr
{
    {pasc::eto_and, "AND"},
    {pasc::eto_array, "ARRAY"},
    {pasc::eto_assignment, ":="},
    {pasc::eto_asterisk, "*"},
    {pasc::eto_begin, "BEGIN"},
    {pasc::eto_case, "CASE"},
    {pasc::eto_colon, ":"},
    {pasc::eto_comma, ","},
    {pasc::eto_const, "CONST"},
    {pasc::eto_div, "DIV"},
    {pasc::eto_do, "DO"},
    {pasc::eto_double_period, ".."},
    {pasc::eto_downto, "DOWNTO"},
    {pasc::eto_else, "ELSE"},
    {pasc::eto_end, "END"},
    {pasc::eto_equal, "="},
    {pasc::eto_file, "FILE"},
    {pasc::eto_for, "FOR"},
    {pasc::eto_function, "FUNCTION"},
    {pasc::eto_goto, "GOTO"},
    {pasc::eto_greater_equal, ">="},
    {pasc::eto_greater_than, ">"},
    {pasc::eto_if, "IF"},
    {pasc::eto_in, "IN"},
    {pasc::eto_label, "LABEL"},
    {pasc::eto_left_bracket, "["},
    {pasc::eto_left_curly_bracket, "{"},
    {pasc::eto_left_multicomment, "(*"},
    {pasc::eto_left_parenthesis, "("},
    {pasc::eto_less_equal, "<="},
    {pasc::eto_less_than, "<"},
    {pasc::eto_minus, "-"},
    {pasc::eto_mod, "%"},
    {pasc::eto_nil, "NIL"},
    {pasc::eto_not, "NOT"},
    {pasc::eto_not_equal, "<>"},
    {pasc::eto_of, "OF"},
    {pasc::eto_or, "OR"},
    {pasc::eto_packed, "PACKED"},
    {pasc::eto_period, "."},
    {pasc::eto_plus, "+"},
    {pasc::eto_pointer, "^"},
    {pasc::eto_procedure, "PROCEDURE"},
    {pasc::eto_program, "PROGRAM"},
    {pasc::eto_record, "RECORD"},
    {pasc::eto_repeat, "REPEAT"},
    {pasc::eto_right_bracket, "]"},
    {pasc::eto_right_curly_bracket, "}"},
    {pasc::eto_right_multicomment, "*)"},
    {pasc::eto_right_parenthesis, ")"},
    {pasc::eto_semicolon, ";"},
    {pasc::eto_set, "SET"},
    {pasc::eto_slash, "/"},
    {pasc::eto_then, "THEN"},
    {pasc::eto_to, "TO"},
    {pasc::eto_type, "TYPE"},
    {pasc::eto_until, "UNTIL"},
    {pasc::eto_var, "VAR"},
    {pasc::eto_while, "WHILE"},
    {pasc::eto_with, "WITH"}
};

std::string pasc::CToken::to_string()
{
    return operator_repr[this->oper];
}
