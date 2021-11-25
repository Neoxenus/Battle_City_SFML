#include "SFML\Graphics.hpp"
#include "windows.h"
#include "Field.h"


int main()
{
    //hide console
    HWND Hide;
    AllocConsole();
    Hide = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Hide, 0);
    //

    Field field1;
    field1.blocks = constants::field1;

    //768
    sf::RenderWindow window(sf::VideoMode(256,256), "", sf::Style::Titlebar | sf::Style::Close);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        field1.draw(window);
    }
    window.display();
}