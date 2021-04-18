#include <cstring>
#include <locale>
#include <memory>
#include <string>
#include <unordered_map>

#include "clexer.hpp"

pasc::CLexer::CLexer(io_ptr io)
{
    this->io = std::move(io);
}

static std::unordered_map<std::string, pasc::token_operator> operator_name
{
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
    { "%", pasc::eto_mod},
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
    { ")", pasc::eto_right_parenthesis},
    { ";", pasc::eto_semicolon},
    {"SET", pasc::eto_set},
    {"/", pasc::eto_slash},
    {"THEN", pasc::eto_then},
    { "TO", pasc::eto_to},
    {"TYPE", pasc::eto_type},
    {"UNTIL", pasc::eto_until},
    {"VAR", pasc::eto_var},
    {"WHILE", pasc::eto_while},
    {"WITH", pasc::eto_with}
};

enum lexeme_type
{
    lt_identifier,
    lt_int_const,
    lt_real_const,
    lt_string_const
};

enum scan_state
{
    ss_null,
    ss_int,
    ss_real,
    ss_string,
    ss_identifier,
    ss_end_of_lexeme
};

static bool is_service(const char ch)
{
    if (ch == '\0') return true; 
    char *services = "+-*/=<>()[]:;.,^";
    return std::strchr(services, ch) != nullptr;
}

pasc::token_ptr pasc::CLexer::get_next_token()
{
    char cur_char = ' ', next_char = ' ';
    token_ptr token = nullptr;
    std::stringstream stream;
    while(std::isspace(cur_char)) // Skip whitespaces
    {
        cur_char = io->get_char();
    }
    next_char = io->peek_char();
    lexeme_type lex;
    scan_state scan;
    while(scan != ss_end_of_lexeme) // While getting a lexeme
    {
        switch (scan) {
        case ss_null:
        {

        }
        break;
        case ss_int:
        {

        }
        break;
        case ss_real:
        {

        }
        break;
        case ss_identifier:
        {
            stream << cur_char;
        }
        break;
        case ss_string:
        {

        }
        break;
        }
        if (std::isdigit(cur_char)) // Int or Real const
        {
            stream << cur_char;

        }
        else if (std::isalpha(cur_char) || cur_char == '_' || cur_char == '\0') // Identifier
        {
            stream << cur_char;
        }
        
        cur_char = io->get_char();
        next_char = io->peek_char();
    }

    return token;
}
