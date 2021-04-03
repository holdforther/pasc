#include <cstdio>
#include <locale>
#include <memory>
#include <string>
#include <unordered_map>

#include "clexer.hpp"

std::unordered_map<std::string, pasc::EOperator> operators
{
    {"(", pasc::eoLeftBracet},
    {"/", pasc::eoDiv},
    {"-", pasc::eoMinus},
    {"*", pasc::eoMul},
    {"+", pasc::eoPlus},
    {")", pasc::eoRightBracet}
};

pasc::token_ptr pasc::CLexer::get_next_token(pasc::io_ptr &io)
{
    char cur_char, next_char;
    token_ptr token = nullptr;
    ETokenType ett = ettValue;
    std::stringstream ss;

    while (io->ifs->get(cur_char))
    {
        next_char = io->ifs->peek();
        if (std::isdigit(cur_char)) // Values
        {
            ett = ettValue;
        }
        else if (std::isalpha(cur_char)) // Identifiers
        {
            ett = ettIdentifier;
        }
        else // Operators
        {
            ett = ettOperator;
        }
        while (!std::isspace(next_char) && next_char != ';')
        {
            ss << cur_char;
            io->ifs->get(cur_char);
            next_char = io->ifs->peek();
        }
    }

    switch (ett) {
    case ettValue:
        token = std::make_unique<CToken>(ett);
        break;
    case ettIdentifier:
        token = std::make_unique<CToken>(ss.str());
        break;
    case ettOperator:
        token = std::make_unique<CToken>(operators[ss.str()]);
    }
    return token;
}
