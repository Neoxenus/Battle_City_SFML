#pragma once
#include <sstream>

char* convertToCharArray(int number)
{
    std::ostringstream strs;
    strs << number;
    std::string str = strs.str();
    char* cstr = new char[str.length() + 1];
    str.copy(cstr, str.length());
    cstr[str.length()] = '\0';
    return cstr;
}

char* convertToCharArray(double number)
{
    std::ostringstream strs;
    strs << number;
    std::string str = strs.str();
    char* cstr = new char[str.length() + 1];
    str.copy(cstr, str.length());
    cstr[str.length()] = '\0';
    return cstr;
}

int converBackFromCharArrayInt(char* cstr)
{
    int number;
    sscanf_s(cstr, "%f", &number);
    return number;
}

double converBackFromCharArrayIntDouble(char* cstr)
{
    double number;
    sscanf_s(cstr, "%f", &number);
    return number;
}