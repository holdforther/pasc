#pragma once
#include <string>
#include <unordered_map>

#include "cerror.hpp"
#include "clexer.hpp"

namespace pasc {
    class Compiler {
        lexer_ptr lexer;
        token_ptr token;
        token_ptr prev_token;
        ErrorList errors;
        std::unordered_map<token_operator, error_code> operator_errors;
        void skip_token();
        void add_error(const CError &error);
        void accept_operator(token_operator _operator);
        void accept_identifier();
        void accept_value();
        // Backus-Naur Forms
        void bnf_program();
        void bnf_block();
        void bnf_var_decl();
        void bnf_procedure_decl();
        void bnf_function_decl();
        void bnf_composite_operator();
        void bnf_operator();
        void bnf_assignment_operator();
        void bnf_procedure_operator();
        void bnf_fact_parameter();
        void bnf_choice_operator();
        void bnf_for_operator();
        void bnf_while_operator();
        void bnf_repeat_operator();
        void bnf_with_operator();
        void bnf_expression();
        void bnf_simple_expression();
        void bnf_term();
        void bnf_multiplier();

        // void bnf_relation_operator();
        // void bnf_additive_operation();
        // void bnf_multiplicative_operation();
        // void bnf_complex_operator();
    public:
        Compiler(const std::string &filename);
        ErrorList compile();
    };
}