#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "cvariant.hpp"

namespace pasc
{
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
        variant_ptr value;
        std::string identifier;
    public:
        CToken(ETokenType type);
        CToken(EOperator oper);
        CToken(const std::string &identifier);
        std::string to_string();
    };
    typedef std::unique_ptr<CToken> token_ptr;
} // namespace pasc
