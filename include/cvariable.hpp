#pragma once
#include <memory>
#include <string>
#include "standard_types.hpp"

namespace pasc {
    class CVariable {
        std::string name;
        standard_type type;
        bool is_constant;
    public:
        CVariable(const std::string &name, standard_type type, bool is_constant)
            : name(name), type(type), is_constant(is_constant) {};
        bool is_const() const;
        standard_type get_type();
        std::string get_name() const;
    };

    typedef std::shared_ptr<CVariable> var_ptr;
}
