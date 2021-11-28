#include "SFML/Graphics.hpp"
#include "Server.h"
#include "Client.h"
#include "Tank.h"
#include <ctime>
#include <iostream>
#include "windows.h"


int main()
{
    //hide console
    HWND Hide;
    AllocConsole();
    Hide = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Hide, 1);
    //

    Field field1;
    field1.setField(constants::field1);
    //Design_mode designm;
    Tank tank1(true , 0);
    std::vector<Bullet> bullets;

    /*Server serv;
    serv.server();*/

   
    sf::RenderWindow window(sf::VideoMode(768, 768), "", sf::Style::Titlebar | sf::Style::Close);

    sf::View view = window.getDefaultView();
    view.zoom(0.33f);
    window.setView(view);
    window.setFramerateLimit(240);

    sf::Clock clock;
    double timer = 0;


    bool isMP = false, isHost = false;
    if (!isMP )
        while (window.isOpen())
        {
            timer += clock.getElapsedTime().asMilliseconds();
            sf::Event event;
            if (timer > constants::delay)
            {
                while (window.pollEvent(event))
                {
                    tank1.control(window, field1, event);
                    
                    if (event.type == sf::Event::Closed)
                        window.close();
                }
                tank1.bullets_colision(field1);
                window.clear(sf::Color::Black);
                field1.draw(window);
                tank1.draw(window); // coord in tiles // spawn tank

                window.display();

                timer = 0;
                clock.restart();
            }
        }

    if (isMP && !isHost)
    {
        Client cl;
        cl.client();

    }
    
}