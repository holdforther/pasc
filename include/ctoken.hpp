#pragma once
#include "cvariant.hpp"

enum ETokenType
{
    ettOperator,
    ettIdentifier,
    ettValue,
};

enum EOperator
{
    eoLeftBracet,
    eoRightBracet,
    eoPlus,
    eoMinus,
    eoMul,
    eoDiv
};

class CToken
{
private:
    ETokenType type;
    EOperator oper;
    pasc::CVariant* value;
    std::string identifier;
public:
    CToken(const ETokenType &type);
    CToken(const EOperator &oper);
    std::string to_string();
};
