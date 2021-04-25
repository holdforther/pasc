#include "cvariant.hpp"

namespace pasc {
    CVariant::CVariant(const var_type type) : T(type) {}

    CIntVariant::CIntVariant(const long int val): CVariant(evt_int), val(val) {}

    std::string CIntVariant::to_string() {
        return std::to_string(val);
    }

    CRealVariant::CRealVariant(const long double val) : CVariant(evt_real), val(val) {}

    std::string CRealVariant::to_string() {
        return std::to_string(val);
    }

    CCharVariant::CCharVariant(const char val) : CVariant(evt_char), val(val) {}

    std::string CCharVariant::to_string() {
        return std::string(1, val);
    }

    CStringVariant::CStringVariant(const std::string &val) : CVariant(evt_string), val(val) {}

    std::string CStringVariant::to_string() {
        return val;
    }

    var_type CVariant::get_type() const {
        return T;
    }
}