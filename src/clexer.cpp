#include "clexer.hpp"
#include "cerror.hpp"

// pasc::CLexer::CLexer(std::string Expr)
// {
//     this->Expr = Expr;
//     std::stringstream ss(Expr);
//     std::string item;
//     while(std::getline(ss, item, ' '))
//     {
//         parsed.push_back(item);
//     }
//     pos = 0;
// }

// The input stream has to be trimmed
CToken pasc::CLexer::get_next_token(std::istream &is)
{
    char ch;
    ETokenType ett;
    if (!is.get(ch))
    {
        return CToken(ettNull);
    }

    std::stringstream ss;
    if(std::isdigit(ch))
    {
        ett = ettValue;
        while (is.get(ch) && std::isdigit(ch))
        {
            ss << ch;
        }
        return CToken(ett); 
    }
    else switch (ch)
    {
    case '(':
        return CToken(eoLeftBracet);
    case ')':
        return CToken(eoRightBracet);
    case '+':
        return CToken(eoPlus);
    case '-':
        return CToken(eoMinus);
    case '*':
        return CToken(eoMul);
    case '/':
        return CToken(eoDiv);
    default:
        return CToken(ettIdentifier);
    }
}