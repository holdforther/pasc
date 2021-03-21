#pragma once
#include <memory>

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
        std::unique_ptr<CToken> value;
        std::string identifier;
    public:
        CToken(const ETokenType &type);
        CToken(const EOperator &oper);
        std::string to_string();
    };
    typedef std::unique_ptr<CToken> token_ptr;
} // namespace pasc
