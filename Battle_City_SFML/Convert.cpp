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
    float number;
    sscanf_s(cstr, "%f", &number);
    return static_cast<int>(number);
}

double convertBackFromCharArrayToDouble(char* cstr)
{
    float number;
    sscanf_s(cstr, "%f", &number);
    return static_cast<double>(number);
}

std::vector <std::string> ConvertFromCharArrayToStringVector(char* buf)
{
    std::vector <std::string> ans;
    std::string tmp;
    for (int i = 0; i < sizeof(buf); i+=8)
    {
        tmp = "";
        for (int j = i; j < i + 8 && buf[j] != '\0'; ++j)
        {
            tmp += buf[j];        
        }
        ans.push_back(tmp);
    }
    return ans;
}