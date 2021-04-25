#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "cerror.hpp"
#include "clexer.hpp"
#include "cscope.hpp"
#include "ctoken.hpp"
#include "cvariable.hpp"
#include "io.hpp"
#include "standard_types.hpp"

namespace pasc {
    typedef std::unordered_set<token_operator> operator_set;

    class Compiler {
        io_ptr io;
        lexer_ptr lexer;
        token_ptr token;
        token_ptr prev_token;
        std::unordered_map<token_operator, error_code> operator_errors;
        scope_ptr scope;
        standard_type last_type;
        var_ptr last_variable;
        bool are_compatible(standard_type t1, standard_type t2);
        void skip_token();
        void skip_tokens(bool(*condition)(token_ptr&));
        void add_error(const CError &error);
        void accept_operator(token_operator _operator);
        void accept_identifier();
        void accept_value();
        // Backus-Naur Forms
        void bnf_program();
        void bnf_block();
        void bnf_var_decl();
        void bnf_composite_operator();
        void bnf_operator();
        void bnf_assignment_operator();
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
    public:
        Compiler(const io_ptr &io);
        void compile();
    };
}