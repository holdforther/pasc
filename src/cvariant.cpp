#include "cvariant.hpp"
#include <string>

pasc::var_type pasc::CVariant::get_type()
{
    return this->T;
}

int pasc::CIntVariant::get_value()
{
    return this->val;
}

float pasc::CRealVariant::get_value()
{
    return this->val;
}

char pasc::CCharVariant::get_value()
{
    return this->val;
}

std::string pasc::CStringVariant::get_value()
{
    return this->val;
}