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

char* convertFromStringToCharArray(std::string data)
{
    char* ans = new char[data.size() + 1];
    ans[data.size()] = '\0';
    for (int i = 0; i < data.size(); ++i)
    {
        ans[i] = data[i];
    }
    ans[data.size()] = '\0';
    return ans;
}

char* convertVectorToCharArray(std::vector<std::string> data)
{
    char* ans = new char[(data.size() * 8 + 1)];
    for (int i = 0; i < (data.size() * 8 + 1); ++i)
    {
        ans[i] = '\0';
    }
    for (int j = 0; j < data.size(); ++j)
    {
        for (int i = 0; data[j][i] != '\0'; ++i)
            ans[i + j * 8] = data[j][i];
    }
    return ans;
}
char* convertVectorToCharArray(std::vector<char*> data)
{
    char* ans = new char[(data.size() * 8 + 1)];
    for (int i = 0; i < (data.size() * 8 + 1); ++i)
    {
        ans[i] = '\0';
    }
    for (int j = 0; j < data.size(); ++j)
    {
        for (int i = 0; data[j][i]!='\0'; ++i)
            ans[i + j * 8] = data[j][i];
    }
    return ans;
}

