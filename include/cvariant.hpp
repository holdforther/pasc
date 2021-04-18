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
    protected:
        CVariant(const var_type T);
    public:
        var_type get_type();
        virtual std::string to_string() = 0;
    };

    class CIntVariant : public CVariant {
    public:
        int val;
        CIntVariant(const int val);
        virtual std::string to_string() override;
    };

    class CRealVariant : public CVariant {
    public:
        float val;
        CRealVariant(const float val);
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
