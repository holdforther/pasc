#pragma once
#include "standard_types.hpp"
#include "cvariable.hpp"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace pasc {
    class CScope {
        std::shared_ptr<CScope> parent_scope;
        std::unordered_map<std::string, standard_type> user_types;
        std::unordered_map<std::string, var_ptr> variables;
        size_t depth;
    public:
        CScope() : parent_scope(nullptr), depth(0) {};
        CScope(std::shared_ptr<CScope> &parent_scope);
        standard_type get_type_by_id(const std::string &id);
        void add_variable(const std::string &name, standard_type type, bool is_const);
        var_ptr get_variable_by_id(const std::string &id);
        size_t get_depth() const;
        void set_type_name(const std::string &id, standard_type type);
        void print_variables();
    };

    typedef std::shared_ptr<CScope> scope_ptr;
}
