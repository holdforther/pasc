#include "clexer.hpp"

pasc::token_ptr pasc::CLexer::get_next_token(std::unique_ptr<std::ifstream> &ifs)
{
    char ch;
    ETokenType ett;
    if (!ifs->get(ch))
    {
        return nullptr;
    }

    std::stringstream ss;
    if(std::isdigit(ch))
    {
        ett = ettValue;
        while (ifs->get(ch) && std::isdigit(ch))
        {
            ss << ch;
        }
        return std::make_unique<CToken>(ett);
    }
    else switch (ch)
    {
    case '(':
        return std::make_unique<CToken>(eoLeftBracet);
    case ')':
        return std::make_unique<CToken>(eoRightBracet);
    case '+':
        return std::make_unique<CToken>(eoPlus);
    case '-':
        return std::make_unique<CToken>(eoMinus);
    case '*':
        return std::make_unique<CToken>(eoMul);
    case '/':
        return std::make_unique<CToken>(eoDiv);
    default:
        return std::make_unique<CToken>(ettIdentifier);
    }
}
