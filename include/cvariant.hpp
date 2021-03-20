#pragma once
#include <string>

enum EVarType
{
    evtInt,
    evtFloat,
    evtChar,
    evtString
};

class CVariant
{
private:
    EVarType T;
public:
    explicit CVariant(const EVarType& T)
    {
        this->T = T;
    }
};

class CIntVariant : public virtual CVariant
{
private:
    int val;
public:
    explicit CIntVariant(const EVarType& val) : CVariant(val)
    {
        this->val = val;
    }
};

class CFloatVariant : public virtual CVariant
{
private:
    float val;
public:
    explicit CFloatVariant(const EVarType& val) : CVariant(val)
    {
        this->val = val;
    }
};

class CCharVariant : public virtual CVariant
{
private:
    char val;
public:
    explicit CCharVariant(const EVarType& val) : CVariant(val)
    {
        this->val = val;
    }
};

class CStringVariant : public virtual CVariant
{
private:
    std::string val;
public:
    explicit CStringVariant(const EVarType& val) : CVariant(val)
    {
        this->val = val;
    }
};