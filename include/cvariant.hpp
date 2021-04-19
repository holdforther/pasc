#pragma once
#include <memory>
#include <string>

namespace pasc {
    enum var_type {
        evt_int,
        evt_real,
        evt_char,
        evt_string
    };

    class CVariant {
    private:
        var_type T;
    public:
        CVariant(const var_type T);
        virtual ~CVariant() {}
        var_type get_type();
        virtual std::string to_string() {return "";}
    };

    class CIntVariant : public CVariant {
    public:
        long int val;
        CIntVariant(const long int val);
        virtual std::string to_string() override;
    };

    class CRealVariant : public CVariant {
    public:
        long double val;
        CRealVariant(const long double val);
        virtual std::string to_string() override;
    };

    class CCharVariant : public CVariant {
    public:
        char val;
        CCharVariant(const char val);
        virtual std::string to_string() override;
    };

    class CStringVariant : public CVariant {
    public:
        std::string val;
        CStringVariant(const std::string &val);
        virtual std::string to_string() override;
    };

    typedef std::unique_ptr<CVariant> variant_ptr;
} // namespace pasc
