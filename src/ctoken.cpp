#include "ctoken.hpp"

CToken::CToken(const ETokenType &type)
{
    this->type = type;
}
CToken::CToken(const EOperator &oper)
{
    this->oper = oper;
    type = ettOperator;
}
std::string CToken::to_string()
{
    switch (ettValue)
    {
    case 0:
        return "Operator";
    case 1:
        return "Identifier";
    case 2:
        return "Value";
    default:
        return "Null";
    }
}
