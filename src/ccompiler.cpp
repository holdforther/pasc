#include <iostream>
#include <memory>
#include <ostream>

#include "ccompiler.hpp"
#include "ctoken.hpp"

namespace pasc {
    Compiler::Compiler(const io_ptr &io) {
        this->io = io;
        lexer = std::make_unique<CLexer>(io);
        prev_token = nullptr;
        token = nullptr;
        operator_errors = std::unordered_map<token_operator, error_code> {
            {eto_undefined, eec_unknown},
            {eto_program, eec_exp_program},
            {eto_semicolon, eec_exp_semicolon},
            {eto_period, eec_exp_period},
            {eto_begin, eec_exp_begin},
            {eto_end, eec_exp_end},
            {eto_colon, eec_exp_colon},
            {eto_comma, eec_exp_comma},
            {eto_procedure, eec_exp_procedure},
            {eto_left_parenthesis, eec_exp_left_parenthesis},
            {eto_right_parenthesis, eec_exp_right_parenthesis},
            {eto_procedure, eec_exp_procedure},
            {eto_while, eec_exp_while},
            {eto_do, eec_exp_do},
            {eto_assignment, eec_exp_assignment}
        };
    }

    static operator_set operator_beginnings {eto_begin, eto_if, eto_while, eto_for, eto_case, eto_with, eto_repeat, eto_goto};
    static operator_set operator_endings {eto_end, eto_semicolon};
    static operator_set expression_beginnings {eto_plus, eto_minus, eto_left_parenthesis, eto_right_parenthesis};
    static operator_set expression_endings {eto_end, eto_semicolon, eto_then, eto_do, eto_of, eto_to, eto_downto};
    static operator_set block_beginnings {eto_var, eto_type, eto_procedure, eto_function, eto_begin};
    static operator_set var_endings {eto_begin, eto_procedure, eto_function};

    void Compiler::add_error(const CError &error) {
        io->add_error(error);
    }

    void Compiler::skip_token() {
        prev_token = std::move(token);
        CError error;
        token = lexer->get_next_token();
        if (token == nullptr && !lexer->is_end_of_stream()) {
            add_error(error);
        }
    }

    void Compiler::skip_tokens(bool(*condition)(token_ptr&)) {
        while(!lexer->is_end_of_stream() &&
            (!token || condition(token))) {
            if (token) std::cout << "Skippin' " << token->to_string() << std::endl;
            skip_token();
        }
    }

    void Compiler::accept_operator(token_operator op) {
        CError error;
        if (token) {
            if (token->op == op) {
                skip_token();
            } else {
                error.code = operator_errors.find(op) != operator_errors.end() ? operator_errors[op] : eec_unknown;
                error.row = token->get_row_pos();
                error.col = token->get_col_pos();
            }
        } else {
            error.code = operator_errors.find(op) != operator_errors.end() ? operator_errors[op] : eec_unknown;
            error.row = io->get_row_index();
            error.col = io->get_col_index();
        }
        add_error(error);
    }

    void Compiler::accept_identifier() {
        CError error;
        if (token) {
            if (token->type == ett_identifier) {
                skip_token();
            } else {
                error.code = eec_exp_identifier;
                error.row = token->get_row_pos();
                error.col = token->get_col_pos();
            }
        } else {
            error.code = eec_exp_identifier;
            error.row = io->get_row_index();
            error.col = io->get_col_index();
        }
        add_error(error);
    }

    void Compiler::accept_value() {
        CError error;
        if (token) {
            if (token->type == ett_value) {
                skip_token();
            } else {
                error.code = eec_exp_value;
                error.row = token->get_row_pos();
                error.col = token->get_col_pos();
            }
        } else {
            error.code = eec_exp_value;
            error.row = io->get_row_index();
            error.col = io->get_col_index();
        }
        add_error(error);
    }

    void Compiler::bnf_program() {
        size_t error_count = io->get_errors_size();
        accept_operator(eto_program);
        accept_identifier();
        accept_operator(eto_semicolon);
        if (io->get_errors_size() > error_count) {
            auto condition = [](token_ptr &token){
                return (block_beginnings.find(token->op) == block_beginnings.end());
            };
            skip_tokens(condition);
        }
        bnf_block();
        accept_operator(eto_period);
    }

    void Compiler::bnf_block() {
        scope_ptr parent_scope = scope;
        scope = std::make_shared<CScope>(scope);

        if (token && token->op == eto_var) {
            int error_count = io->get_errors_size();
            bnf_var_decl();
            if (io->get_errors_size() > error_count) {
                auto condition = [](token_ptr &token){
                    return (var_endings.find(token->op) == var_endings.end());
                };
                skip_tokens(condition);
            }
        }
        bnf_composite_operator();
        scope = parent_scope;
    }

    void Compiler::bnf_var_decl() {
        std::vector<std::string> variables;
        accept_operator(eto_var);
        while (token && token->type == ett_identifier) {
            int error_count = io->get_errors_size();
            accept_identifier();
            variables.push_back(prev_token->id);
            while (token && token->op == eto_comma) {
                accept_operator(eto_comma);
                accept_identifier();
                variables.push_back(prev_token->id);
            }
            if (io->get_errors_size() > error_count) {
                while(token->op != eto_colon) {
                    skip_token();
                }
            }
            accept_operator(eto_colon);
            accept_identifier();
            if (prev_token) {
                CError type_error (prev_token->get_row_pos(), prev_token->get_col_pos());
                std::string type_name = prev_token->id;
                for (auto & c : type_name) {c = std::toupper(c); }
                standard_type st = scope->get_type_by_id(type_name);
                if (st != est_unknown) {
                    for (auto variable : variables) {
                        scope->add_variable(variable, st, false);
                    }
                } else {
                    type_error.code = eec_invalid_type;
                    add_error(type_error);
                }
            }
            variables.clear();
            accept_operator(eto_semicolon);
        }
    }

    void Compiler::bnf_composite_operator() {
        accept_operator(eto_begin);
        bnf_operator();
        while (token && token->op == eto_semicolon) {
            accept_operator(eto_semicolon);
            if (token->type == ett_identifier || token->op == eto_begin ||
                token->op == eto_if || token->op == eto_for || token->op == eto_while ||
                token->op == eto_repeat || token->op == eto_with || token->op == eto_case) {
                bnf_operator();
            }
        }
        size_t error_count = io->get_errors_size();
        accept_operator(eto_end);
        if (io->get_errors_size() > error_count) {
            auto condition = [](token_ptr &token){
                return (token->type != ett_identifier ||
                    operator_beginnings.find(token->op) == operator_beginnings.end());
            };
            skip_tokens(condition);
        }
    }

    void Compiler::bnf_operator() {
        int error_count = io->get_errors_size();
        // simple operators -- assignment or procedure
        if (token && token->op == eto_procedure) {
            // bnf_procedure_operator();
        } else if (token && token->type == ett_identifier) {
            bnf_assignment_operator();
        }
        // complex operators -- composite, choice or cycle operators
        else if (token && token->type == ett_operator) {
            switch (token->op) {
                case eto_begin: bnf_composite_operator(); break;
                // case eto_if: bnf_choice_operator(); break;
                // case eto_for: bnf_for_operator(); break;
                // case eto_while: bnf_while_operator(); break;
                // case eto_repeat: bnf_repeat_operator(); break;
                // case eto_with: bnf_with_operator(); break;
                // case eto_case: break;
                default: {
                    add_error(CError(token->get_row_pos(), token->get_col_pos(), eec_invalid_operator));
                } break;
            }
        } else if (token) {
            add_error(CError(token->get_row_pos(), token->get_col_pos(), eec_invalid_operator));
        }
        if (io->get_errors_size() > error_count) {
            auto condition = [](token_ptr &token){
                return (operator_endings.find(token->op) == operator_endings.end());
            };
            skip_tokens(condition);
        }
    }

    void Compiler::bnf_assignment_operator() {
        accept_identifier();
        auto variable = scope->get_variable_by_id(prev_token->id);
        if (variable == nullptr) {
            add_error(CError(prev_token->get_row_pos(), prev_token->get_col_pos(), eec_unknown_identifier));
        }
        accept_operator(eto_assignment);
        bnf_expression();
        if (variable && !are_compatible(variable->get_type(), last_type)) {
            add_error(CError(prev_token->get_row_pos(), prev_token->get_col_pos(), eec_incompatible_types));
        };
    }

    void Compiler::bnf_choice_operator() {
        accept_operator(eto_if);
        bnf_expression();
        accept_operator(eto_then);
        bnf_operator();
        if (token && token->op == eto_else) {
            accept_operator(eto_else);
            bnf_operator();
        }
    }

    void Compiler::bnf_for_operator() {
        accept_operator(eto_for);
        accept_identifier();
        accept_operator(eto_assignment);
        bnf_expression();
        if (token && token->op == eto_to) accept_operator(eto_to);
        else if (token && token->op == eto_downto) accept_operator(eto_downto);
        bnf_expression();
        accept_operator(eto_do);
        bnf_operator();
    }

    void Compiler::bnf_while_operator() {
        accept_operator(eto_while);
        bnf_expression();
        accept_operator(eto_do);
        bnf_operator();
    }

    void Compiler::bnf_repeat_operator() {
        accept_operator(eto_repeat);
        bnf_operator();
        accept_operator(eto_until);
        bnf_expression();
    }

    void Compiler::bnf_with_operator() {
        accept_operator(eto_with);
        accept_identifier();
        while (token && token->op == eto_comma) {
            accept_operator(eto_comma);
            accept_identifier();
        }
    }

    void Compiler::bnf_expression() {
        bnf_simple_expression();
        standard_type first_operand_type = last_type;
        if (token) {
            if (token->op == eto_equal || token->op == eto_not_equal ||
                token->op == eto_less_than || token->op == eto_greater_than ||
                token->op == eto_less_equal || token->op == eto_greater_equal ||
                token->op == eto_in) {
                    accept_operator(token->op);
                    bnf_simple_expression();
            }
        }
        last_type = first_operand_type;
    }

    void Compiler::bnf_simple_expression() {
        bnf_term();
        standard_type first_operand_type = last_type;
        while (token && (token->op == eto_plus || token->op == eto_minus ||
            token->op == eto_or)) {
            accept_operator(token->op);
            bnf_term();
            if (!are_compatible(first_operand_type, last_type)) {
                add_error(CError(prev_token->get_row_pos(), prev_token->get_col_pos(), eec_incompatible_types));
            } else {
                first_operand_type = last_type;
            }
        }
        last_type = first_operand_type;
    }

    void Compiler::bnf_term() {
        CError error;
        bnf_multiplier();
        standard_type first_operand_type = last_type;
        while (token && (token->op == eto_asterisk || token->op == eto_slash ||
            token->op == eto_div || token->op == eto_mod || token->op == eto_and)) {
            accept_operator(token->op);
            bnf_multiplier();
            if (!are_compatible(first_operand_type, last_type)) {
                add_error(CError(prev_token->get_row_pos(), prev_token->get_col_pos(), eec_incompatible_types));
            } else {
                first_operand_type = last_type;
            }
        }
        last_type = first_operand_type;
    }

    bool Compiler::are_compatible(standard_type t1, standard_type t2) {
        return (t1 == t2 || (t1 == est_real && t2 == est_integer));
    }

    void Compiler::bnf_multiplier() {
        if (token) {
            if (token->op == eto_not) {
                accept_operator(eto_not);
                bnf_multiplier();
            } else if (token->op == eto_minus || token->op == eto_plus) {
                accept_operator(token->op);
            }
            if (token->type == ett_identifier) {
                accept_identifier();
                last_variable = scope->get_variable_by_id(prev_token->id);
                if (last_variable != nullptr) {
                    last_type = last_variable->get_type();
                    last_variable = nullptr;
                } else {
                    add_error(CError(prev_token->get_row_pos(), prev_token->get_col_pos(), eec_unknown_identifier));
                }
            } else if (token->type == ett_value) {
                accept_value();
                auto constant_type = prev_token->val->get_type();
                switch (constant_type) {
                case evt_int: {
                    last_type = scope->get_type_by_id("INTEGER");
                } break;
                case evt_real: {
                    last_type = scope->get_type_by_id("REAL");
                } break;
                case evt_char: {
                    last_type = scope->get_type_by_id("CHAR");
                } break;
                default: last_type = est_unknown; break;
                }
            } else if (token->op == eto_left_parenthesis) {
                accept_operator(eto_left_parenthesis);
                bnf_expression();
                accept_operator(eto_right_parenthesis);
            }
        } else {
            last_type = est_unknown;
        }
    }

    void Compiler::compile() {
        scope = std::make_shared<CScope>();
        scope->set_type_name("INTEGER", est_integer);
        scope->set_type_name("REAL", est_real);
        scope->set_type_name("BOOLEAN", est_boolean);
        scope->set_type_name("CHAR", est_char);
        scope->add_variable("TRUE", est_boolean, true);
        scope->add_variable("FALSE", est_boolean, true);
        token = lexer->get_next_token();
        bnf_program();
    }
}
