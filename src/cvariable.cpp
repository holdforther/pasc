#include "cvariable.hpp"

namespace pasc {
    bool CVariable::is_const() const {
        return is_constant;
    }

    std::string CVariable::get_name() const {
        return name;
    }

    standard_type CVariable::get_type() {
        return this->type;
    }
}
