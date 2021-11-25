#include "SFML\Graphics.hpp"
#include "windows.h"



int main()
{
    //hide console
    HWND Hide;
    AllocConsole();
    Hide = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Hide, 1);
    //
}