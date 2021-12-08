#pragma once
#include <sstream>
#include <vector>

char* convertToCharArray(int number);

char* convertToCharArray(double number);

int convertBackFromCharArrayToInt(char* cstr);

double convertBackFromCharArrayToDouble(char* cstr);

std::vector <std::string> ConvertFromCharArrayToStringVector(char* buf, int bufSize);

char* convertFromStringToCharArray(std::string data);

char* convertVectorToCharArray(std::vector<std::string>);

char* convertVectorToCharArray(std::vector<char*>);