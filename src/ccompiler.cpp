#include <iostream>

#include "ccompiler.hpp"
#include "cerror.hpp"
#include "ctoken.hpp"
#include "cvariant.hpp"

namespace pasc {
    Compiler::Compiler(const std::string &filename) {
        auto io = std::make_unique<IO>(filename);
        lexer = std::make_unique<CLexer>(io);
        prev_token = nullptr;
        token = nullptr;
        errors = ErrorList(0);
        operator_errors = std::unordered_map<token_operator, error_code> {
            {eto_undefined, eec_unknown},
            {eto_program, eec_exp_program},
            {eto_semicolon, eec_exp_semicolon},
            {eto_period, eec_exp_period},
            {eto_end, eec_exp_end},
            {eto_colon, eec_exp_colon},
            {eto_comma, eec_exp_comma},
            {eto_procedure, eec_exp_procedure},
            {eto_left_parenthesis, eec_exp_left_parenthesis},
            {eto_right_parenthesis, eec_exp_right_parenthesis},
            {eto_begin, eec_exp_begin}
        };
    }

    void Compiler::add_error(const CError &error) {
        if (error.code != eec_no) {
            errors.emplace_back(error);
        }
    }

    void Compiler::skip_token() {
        prev_token = std::move(token);
        CError error;
        token = lexer->get_next_token(error);
        if (token == nullptr && !lexer->is_end_of_stream()) {
            add_error(error);
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
                add_error(error);
            }
        }
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
                add_error(error);
            }
        }
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
                add_error(error);
            }
        }
    }

    void Compiler::bnf_program() {
        std::cout << "Program in\n";
        accept_operator(eto_program);
        accept_identifier();
        accept_operator(eto_semicolon);
        bnf_block();
        accept_operator(eto_period);
        std::cout << "Program out\n";
    }

    void Compiler::bnf_block() {
        std::cout << "Block in\n";
        if (token && token->op == eto_var) {
            int error_count = errors.size();
            bnf_var_decl();
            if (errors.size() > error_count) {
                while (token && token->op != eto_begin && token->op != eto_procedure && token->op != eto_function) {
                    skip_token();
                }
            }
        }
        // if (token && token->op == eto_procedure) {
        //     bnf_procedure_decl();
        // }
        // if (token && token->op == eto_function) {
        //     bnf_function_decl();
        // }
        bnf_composite_operator();
        std::cout << "Block out\n";
    }

    void Compiler::bnf_var_decl() {
        std::cout << "Var declaration in\n";
        accept_operator(eto_var);
        while (token && token->type == ett_identifier) {
            int error_count = errors.size();
            accept_identifier();
            while (token && token->op == eto_comma) {
                accept_operator(eto_comma);
                accept_identifier();
            }
            if (errors.size() > error_count) {
                while(token->op != eto_colon) {
                    skip_token();
                }
            }
            accept_operator(eto_colon);
            accept_identifier();
            accept_operator(eto_semicolon);
        }

        std::cout << "Var declaration out\n";
    }

    void Compiler::bnf_composite_operator() {
        std::cout << "Compostite operator in\n";
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
        accept_operator(eto_end);
        std::cout << "Composite operator out\n";
    }

    void Compiler::bnf_operator() {
        std::cout << "Operator in\n";
        int error_count = errors.size();
        // simple operators -- assignment or procedure
        if (token && token->op == eto_procedure) {
            bnf_procedure_operator();
        } else if (token && token->type == ett_identifier) {
            bnf_assignment_operator();
        }
        // complex operators -- composite, choice or cycle operators
        else if (token && token->type == ett_operator) {
            switch (token->op) {
                case eto_begin: bnf_composite_operator(); break;
                case eto_if: bnf_choice_operator(); break;
                case eto_for: bnf_for_operator(); break;
                case eto_while: bnf_while_operator(); break;
                case eto_repeat: bnf_repeat_operator(); break;
                case eto_with: bnf_with_operator(); break;
                case eto_case: break;
                default: {
                    add_error(CError(token->get_row_pos(), token->get_col_pos(), eec_invalid_operator));
                } break;
            }
        } else if (token) {
            add_error(CError(token->get_row_pos(), token->get_col_pos(), eec_invalid_operator));
        }
        if (errors.size() > error_count) {
            while (!lexer->is_end_of_stream() && token->op != eto_semicolon && token->op != eto_end) {
                skip_token();
            }
        }
        std::cout << "Operator out\n";
    }

    void Compiler::bnf_assignment_operator() {
        std::cout << "Assignment in\n";
        accept_identifier();
        accept_operator(eto_assignment);
        bnf_expression();
        std::cout << "Assignment out\n";
    }

    void Compiler::bnf_procedure_operator() {
        // accept_identifier();
        // if (token->op == eto_left_parenthesis) {
        //     accept_operator(eto_left_parenthesis);
        //     bnf_fact_parameter();
        //     while (token->op == eto_comma) {
        //         accept_operator(eto_comma);
        //         bnf_fact_parameter();
        //     }
        //     accept_operator(eto_right_parenthesis);
        // }
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
        std::cout << "Expression in\n";
        bnf_simple_expression();
        if (token) {
            if (token->op == eto_equal || token->op == eto_not_equal ||
                token->op == eto_less_than || token->op == eto_greater_than ||
                token->op == eto_less_equal || token->op == eto_greater_equal ||
                token->op == eto_in) {
                    accept_operator(token->op);
                    bnf_simple_expression();
            }
        }
        std::cout << "Expression out\n";
    }

    void Compiler::bnf_simple_expression() {
        std::cout << "Simple expression in\n";
        bnf_term();
        while (token && (token->op == eto_plus || token->op == eto_minus ||
            token->op == eto_or)) {
            accept_operator(token->op);
            bnf_term();
        }
        std::cout << "Simple expression out\n";
    }

    void Compiler::bnf_term() {
        std::cout << "Term in\n";
        bnf_multiplier();
        while (token && (token->op == eto_asterisk || token->op == eto_slash ||
            token->op == eto_div || token->op == eto_mod || token->op == eto_and)) {
            accept_operator(token->op);
            bnf_multiplier();
        }
        std::cout << "Term out\n";
    }

    void Compiler::bnf_multiplier() {
        std::cout << "Multiplier in\n";
        if (token) {
            if (token->op == eto_not) {
                accept_operator(eto_not);
                bnf_multiplier();
            } else if (token->op == eto_minus || token->op == eto_plus) {
                accept_operator(token->op);
            }
            if (token->type == ett_identifier) {
                accept_identifier();
            } else if (token->type == ett_value) {
                accept_value();
            } else if (token->op == eto_left_parenthesis) {
                accept_operator(eto_left_parenthesis);
                bnf_expression();
                accept_operator(eto_right_parenthesis);
            }
        } else {

        }
        std::cout << "Multiplier out\n";
    }

    ErrorList Compiler::compile() {
        CError error;
        token = lexer->get_next_token(error);
        add_error(error);
        bnf_program();
        return errors;
    }
}
