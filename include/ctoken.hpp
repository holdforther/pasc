#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "cvariant.hpp"

namespace pasc {
    // https://www.pascal-central.com/ppl/chapter3.html
    enum token_type {
        ett_operator,
        ett_identifier,
        ett_value,
    };

    enum token_operator {
        eto_undefined, // Undefined
        // Assignment
        eto_assignment,             // :=
        // Relational
        eto_equal,                  // =
        eto_not_equal,              // <>
        eto_less_than,              // <
        eto_greater_than,           // >
        eto_less_equal,             // <=
        eto_greater_equal,          // >=
        // Arithmetic
        eto_plus,                   // +
        eto_minus,                  // -
        eto_asterisk,               // *
        eto_slash,                  // /
        // Brackets
        eto_left_parenthesis,       // (
        eto_right_parenthesis,      // )
        eto_left_bracket,           // [
        eto_right_bracket,          // ]
        // Others
        eto_period,                 // .
        eto_comma,                  // ,
        eto_colon,                  // :
        eto_semicolon,              // ;
        eto_pointer,                // ^
        eto_double_period,          // ..
        eto_left_curly_bracket,     // {
        eto_right_curly_bracket,    // }
        eto_left_multicomment,      // (*
        eto_right_multicomment,     // )*
        // Reserved words
        eto_and,        // Boolean conjunction operator
        eto_array,      // Array type
        eto_begin,      // Starts a compound statement
        eto_case,       // Starts a CASE statement
        eto_const,      // Declares a constant
        eto_div,        // Integer division
        eto_do,         // Follows WHILE and FOR clause, preceding action to take
        eto_downto,     // In a FOR loop, indicates that FOR variable is decremented at each pass
        eto_else,       // If the boolean in the IF is false, the action following ELSE is executed
        eto_end,        // Ends a compound statement, a case statement, or a record declaration
        eto_file,       // Declares a variable as a file
        eto_for,        // Executes line(s) of code while FOR loop variable in within range
        eto_function,   // Declares a Pascal function
        eto_goto,       // Branches to a specified label
        eto_if,         // Examine a boolean condition and execute code if true
        eto_in,         // Boolean evaluated to true if value is in a specified set
        eto_label,      // Indicates code to branch to in a GOTO statement
        eto_mod,        // Modular integer evaluation
        eto_nil,        // Null value for a pointer
        eto_not,        // Negates the value of a boolean expression
        eto_of,         // Used in CASE statement after case variable
        eto_or,         // Boolean disjunction operator
        eto_packed,     // Used with ARRAY, FILE, RECORD, and SET to pack data storage
        eto_procedure,  // Declares a Pascal procedure
        eto_program,    // Designates the program heading
        eto_record,     // Declares a record type
        eto_repeat,     // Starts a REPEAT/UNTIL loop
        eto_set,        // Declares a set
        eto_then,       // Follows the boolean expression after an IF statement
        eto_to,         // In a FOR loop, indicates that FOR variable is incremented at each pass
        eto_type,       // Defines a variable type
        eto_until,      // Ends a REPEAT/UNTIL loop
        eto_var,        // Declares a program variable
        eto_while,      // Executes block of code until WHILE condition is false
        eto_with        // Specifies record variable to use for a block of code
    };

    class CToken
    {
    public:
        token_type type;
        token_operator op;
        variant_ptr val;
        std::string id;
        CToken();
        CToken(token_operator _operator);
        CToken(const std::string &identifier);
        CToken(variant_ptr &value);
        std::string to_string() const;
    };
    typedef std::unique_ptr<CToken> token_ptr;
} // namespace pasc
