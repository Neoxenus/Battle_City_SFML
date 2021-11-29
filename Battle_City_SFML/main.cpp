#include "SFML/Graphics.hpp"
#include "Server.h"
#include "Client.h"
#include "Tank.h"
#include <ctime>
#include <iostream>
#include "windows.h"

//при каждой отрисовке танка рисовать все пули?

int main()
{
    srand(time(NULL)); // for random

    //hide console
    HWND Hide;
    AllocConsole();
    Hide = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Hide, 1);
    //

    sf::Texture texture_all;
    texture_all.loadFromFile("allSprites.png");
    sf::Texture texture_block;
    texture_block.loadFromFile("tiles.png");
    sf::Texture texture_base;
    texture_base.loadFromFile("sprites.png");

    Field field1;
    field1.setField(constants::field1);
    //Design_mode designm;
    //std::vector<Bullet> bullets;
    Tank tank1(true , 0);
    std::vector<Bullet> bullets;
    std::vector<Tank> tankAI{ {false, 0}, {false, 0}, {false, 0}, {false, 0} };
    std::vector<double> tankAIRespawnTime{ 0.0, 3.0, 6.0, 9.0};

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
    int fps = 0;
    double delay = constants::delay;

    bool isMP = false, isHost = false;
    if (!isMP )
        while (window.isOpen())
        {
            timer = clock.getElapsedTime().asMilliseconds() / 1000.0;
            sf::Event event;
            if (timer > delay)
            {
                while (window.pollEvent(event))
                {
                    tank1.bullet_shoot(window, event);

                    if (event.type == sf::Event::Closed)
                        window.close();
                }

                for (int i = 0; i < tankAIRespawnTime.size(); ++i)
                {
                    if (timer > tankAIRespawnTime[i] && abs(timer - tankAIRespawnTime[i]) <= 15)
                    {
                        /*for (auto& tank : tankAI)
                        {
                            if ()
                        }*/
                        tankAI[i].setVisibility(true);
                        tankAI[i].setCoordX(constants::DEFAULT_ENEMY_COORD_X[rand() % 2]);
                        tankAI[i].setSubCoordX(tankAI[i].getCoordX());
                        tankAI[i].setCoordY(constants::DEFAULT_ENEMY_COORD_Y);
                        tankAI[i].setSubCoordY(tankAI[i].getCoordY());
                        tankAIRespawnTime[i] = 257;
                    }
                }

                tank1.animation(fps);
                for (int i = 0; i < tankAI.size(); ++i)
                {
                    tankAI[i].animation(fps);
                    if (tankAI[i].isVisible() && tankAI[i].tankDeath(tank1))
                    {
                        tankAI[i].setVisibility(false);
                        tankAI[i].setCoordX(0);
                        tankAI[i].setCoordY(0);
                        tankAIRespawnTime[i] = (static_cast<int>(timer) + 3) % 256;
                    }
                }

                if (timer < 24.0)
                {
                    for (auto& tank : tankAI)
                    {
                        if (tank.isVisible())
                        {
                            tank.moveAIRandomly(window, field1, event, tankAI);
                        }
                    }
                }
                else if (timer < 48.0)
                {
                    for (auto& tank : tankAI)
                    {
                        if (tank.isVisible())
                        {
                            tank.moveAIToAlly(window, field1, event, tank1, tankAI);
                        }
                    }
                }
                else
                {

                }

                for (int i = 0; i < tankAI.size(); ++i)
                {
                    if (tankAI[i].tankWithTankCollision(tankAI) != -1)
                    {
                        tankAI[i].setDirection(static_cast<constants::Directions>((static_cast<int>(tankAI[i].getDirection()) + 2) % 4));
                        tankAI[tankAI[i].tankWithTankCollision(tankAI)].setDirection(static_cast<constants::Directions>((static_cast<int>(tankAI[tankAI[i].tankWithTankCollision(tankAI)].getDirection()) + 2) % 4));
                    }
                }

                delay += constants::delay;

                ++fps;
                //if (timer > 1 && fps < 129)
                //{
                //    std::cout << fps << "\n";
                //    //exit(1);
                //}
               
                window.clear(sf::Color::Black);                           
                field1.draw(window, texture_block, texture_base);
                tank1.draw(window, texture_all); // coord in tiles // spawn tank
                tank1.control(window, field1, event, tankAI);
                tank1.bullets_colision(field1); 

                for (auto& tank : tankAI)
                    if (tank.isVisible())
                        tank.draw(window, texture_all);
                
                timer = 0;
                window.display();
                
                //clock.restart();
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
        Client cl;
        cl.client();
        cl.exchange(field1, tank1);
    }
    
}