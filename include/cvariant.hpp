#pragma once
#include <memory>
#include <string>

namespace pasc
{
    enum var_type
    {
        evt_int,
        evt_real,
        evt_char,
        evt_string
    };

    class CVariant
    {
    private:
        var_type T;
    public:
        explicit CVariant(const var_type T)
        {
            this->T = T;
        }
        var_type get_type();
    };
    typedef std::unique_ptr<CVariant> variant_ptr;

    class CIntVariant : public virtual CVariant
    {
    private:
        int val;
    public:
        explicit CIntVariant(const var_type val) : CVariant(val)
        {
            this->val = val;
        }
        int get_value();
    };

    class CRealVariant : public virtual CVariant
    {
    private:
        float val;
    public:
        explicit CRealVariant(const var_type val) : CVariant(val)
        {
            this->val = val;
        }
        float get_value();
    };

    class CCharVariant : public virtual CVariant
    {
    private:
        char val;
    public:
        explicit CCharVariant(const var_type val) : CVariant(val)
        {
            this->val = val;
        }
        char get_value();
    };

    class CStringVariant : public virtual CVariant
    {
    private:
        std::string val;
    public:
        explicit CStringVariant(const var_type val) : CVariant(val)
        {
            this->val = val;
        }
        std::string get_value();
    };
} // namespace pasc
