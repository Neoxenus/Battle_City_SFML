#pragma once
#include <sstream>
#include <vector>

char* convertToCharArray(int number);

char* convertToCharArray(double number);

int convertBackFromCharArrayToInt(char* cstr);

double convertBackFromCharArrayToDouble(char* cstr);

char* convertFromStringToCharArray(std::string data);

char* convertVectorToCharArray(std::vector<std::string>);

char* convertVectorToCharArray(std::vector<char*>);