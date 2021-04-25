#include "cscope.hpp"
#include "cvariant.hpp"
#include "standard_types.hpp"

#include <cctype>
#include <ostream>
#include <string>
#include <iostream>

namespace pasc {
    CScope::CScope(scope_ptr &parent_scope) {
        this->parent_scope = parent_scope;
        if (this->parent_scope) {
            depth = parent_scope->get_depth() + 1;
        } else {
            depth = 0;
        }
    }

    standard_type CScope::get_type_by_id(const std::string &id) {
        auto it = user_types.find(id);
        if (it == user_types.end()) {
            if (this->parent_scope) {
               return this->parent_scope->get_type_by_id(id);
            } else {
                return est_unknown;
            }
        } else {
            return it->second;
        }
    }

    var_ptr CScope::get_variable_by_id(const std::string &id){
        auto it = variables.find(id);
        if (it == variables.end()) {
            if (this->parent_scope) {
               return this->parent_scope->get_variable_by_id(id);
            } else {
                return nullptr;
            }
        } else {
            return it->second;
        }
    }

    void CScope::set_type_name(const std::string &id, standard_type type) {
        std::string name(id);
        for (auto &c: name) { c = std::toupper(c); }
        user_types[name] = type;
    }

    void CScope::add_variable(const std::string &name, standard_type type, bool is_const) {
        //std::string variable_name = name + "_" + std::to_string(depth);
        variables[name] = std::make_unique<CVariable>(name, type, is_const);
    }

    size_t CScope::get_depth() const {
        return depth;
    }

    void CScope::print_variables() {
        for (auto v : variables) {
            std::cout << v.first << " " << v.second->get_type() << std::endl;
        }
    }
}