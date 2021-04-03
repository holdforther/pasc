#include "ctoken.hpp"
#include <string>

pasc::CToken::CToken(pasc::variant_ptr value)
{
    this->type = ettValue;
    // std::move()
}

pasc::CToken::CToken(const std::string &identifier)
{
    this->type = ettIdentifier;
    this->identifier = identifier;
}

pasc::CToken::CToken(EOperator oper)
{
    this->oper = oper;
    type = ettOperator;
}

std::unordered_map<int, std::string> operator_repr
{
    {pasc::eoLeftBracet, "("},
    {pasc::eoDiv, "/"},
    {pasc::eoMinus, "-"},
    {pasc::eoMul, "*"},
    {pasc::eoPlus, "+"},
    {pasc::eoRightBracet, ")"}
};

std::string pasc::CToken::to_string()
{
    std::string token_type, token_repr;
    switch (type)
    {
    case 0:
        token_type = "Operator ";
        token_repr = operator_repr[oper];
        break;
    case 1:
        token_type = "Identifier ";
        token_repr = identifier;
        break;
    default:
        token_type = "Value ";
        break;
    }
    return token_type.append(token_repr);
}
