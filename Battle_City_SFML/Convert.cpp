#include "Convert.h"
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

int convertBackFromCharArrayToInt(char* cstr)
{
    int number;
    sscanf_s(cstr, "%f", &number);
    return number;
}

double convertBackFromCharArrayToDouble(char* cstr)
{
    float number;
    sscanf_s(cstr, "%f", &number);
    return static_cast<double>(number);
}