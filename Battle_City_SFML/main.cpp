#include "SFML\Graphics.hpp"
#include "windows.h"
#include "Field.h"
#include "Design_mode.h"


int main()
{
    //hide console
    HWND Hide;
    AllocConsole();
    Hide = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Hide, 0);
    //

    Field field1;
    field1.setField(constants::field1);
    Design_mode designm;

    sf::RenderWindow window(sf::VideoMode(768, 768), "", sf::Style::Titlebar | sf::Style::Close);

    sf::View view = window.getDefaultView();
    view.zoom(0.33f);
    window.setView(view);
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Tilde)
                {
                    window.close();
                    //designm.draw_dm();
                }
            }

            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        field1.draw(window);
    }
    window.display();
}