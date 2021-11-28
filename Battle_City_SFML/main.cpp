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
    std::vector<Tank> tankAI{ {false, 0}, {false, 0}, {false, 0}, {false, 0} };
    std::vector<double> tankAIRespawnTime{ 0.0, 3.0, 6.0, 9.0};

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
    if (!isMP)
    {
        while (window.isOpen())
        {
            timer += clock.getElapsedTime().asMilliseconds() / 1000.0;
            sf::Event event;
            if (timer > constants::delay)
            {
                std::cout << timer << "\n";
                for (int i = 0; i < tankAIRespawnTime.size(); ++i)
                {
                    if (timer > tankAIRespawnTime[i])
                    {
                        tankAI[i].setVisibility(true);
                        tankAIRespawnTime[i] = 0.0;
                    }
                }
                while (window.pollEvent(event))
                {
                    tank1.control(window, field1, event);
                    tank1.bullet_shoot(window, event);

                    if (event.type == sf::Event::Closed)
                        window.close();
                }
                tank1.bullets_colision(field1);
                window.clear(sf::Color::Black);
                field1.draw(window);
                tank1.draw(window); // coord in tiles // spawn tank
                for (auto& tank : tankAI)
                    if (tank.isVisible())
                        tank.draw(window);

                window.display();
                timer = 0;
                clock.restart();

            }
        }
        if (timer > constants::delay * 128 * 256)
        {
            timer = 0;
            clock.restart();
        }
    }


    if (isMP && !isHost)
    {
       // Client cl;
//        cl.client();

    }
    
}