#include "SFML/Graphics.hpp"
#include "Server.h"
#include "Client.h"
#include "Tank.h"
#include <ctime>
#include <iostream>
#include "windows.h"


int main()
{
    srand(time(NULL)); // for random

    //hide console
    HWND Hide;
    AllocConsole();
    Hide = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Hide, 1);
    //

    Field field1;
    field1.setField(constants::field1);
    //Design_mode designm;
    //std::vector<Bullet> bullets;
    Tank tank1(true , 0);
    std::vector<Bullet> bullets;
    std::vector<Tank> tankAI{ {false, 0}, {false, 0}, {false, 0}, {false, 0} };
    std::vector<double> tankAIRespawnTime{ 0.0, 3.0, 6.0, 9.0};
    for (auto& tank : tankAI)
        std::cout << tank.getCoordX();

    /*Server serv;
    serv.server();
    serv.loop(field1, tank1);*/

    

   
    sf::RenderWindow window(sf::VideoMode(768, 768), "", sf::Style::Titlebar | sf::Style::Close);

    sf::View view = window.getDefaultView();
    view.zoom(0.33f);
    window.setView(view);
    window.setFramerateLimit(240);

    sf::Clock clock;
    double timer = 0;


    bool isMP = false, isHost = false;
    double delay = constants::delay;
    if (!isMP)
    {
        while (window.isOpen())
        {
            timer = clock.getElapsedTime().asMicroseconds() / 1000000.0;
            sf::Event event;
            std::cout << "out - " << timer << "\n";
            if (timer > delay)
            {
                ++fps;
                delay += constants::delay;
                //std::cout << timer << "\n";
                for (int i = 0; i < tankAIRespawnTime.size(); ++i)
                {
                    if (timer > tankAIRespawnTime[i])
                    {
                        for (auto& tank : tankAI)
                        {
                            if()
                        }
                        tankAI[i].setVisibility(true);
                        tankAIRespawnTime[i] = 0.0;
                    }
                }
                while (window.pollEvent(event))
                {
                    tank1.bullet_shoot(window, event);

                    if (event.type == sf::Event::Closed)
                        window.close();
                }
                tank1.control(window, field1, event);
                tank1.bullets_colision(field1);
                window.clear(sf::Color::Black);
                field1.draw(window);
                tank1.draw(window); // coord in tiles // spawn tank
                for (auto& tank : tankAI)
                    if (tank.isVisible())
                        tank.draw(window);

                window.display();

                //std::cout << timer << "\n";
            }
        }
        if (timer > constants::delay * 128 * 256)
        {
            delay = constants::delay;
            timer = 0;
            clock.restart();
        }
    }


    if (isMP && !isHost)
    {
        //Client cl;
        //cl.client();
        //cl.exchange(field1, tank1);
    }
    
}