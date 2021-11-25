#include "windows.h"
#include "SFML\Graphics.hpp"



int main()
{
    //hide console
    HWND Hide;
    AllocConsole();
    Hide = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Hide, 0);
    //

}