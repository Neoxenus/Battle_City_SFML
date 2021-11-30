#include "SFML/Graphics.hpp"
#include "Server.h"
#include "Client.h"
#include "Tank.h"
#include <ctime>
#include <iostream>
#include "windows.h"
#include "Menu.h"
#include "StatisticBox.h"
//при каждой отрисовке танка рисовать все пули?

void newGame(Tank& tank1, std::vector<Tank>& tankAI, Field& field1, std::vector<double>& tankAIRespawnTime)
{
    field1.setField(constants::field1);
    Tank buf(true, 0);
    tank1 = buf;
    std::vector<Tank> bufTankAI{ {false, 0}, {false, 0}, {false, 0}, {false, 0} };
    tankAI = bufTankAI;
    std::vector<double> bufTankAIRespawnTime{ 0.0, 3.0, 6.0, 9.0 };
    tankAIRespawnTime = bufTankAIRespawnTime;
}

int min(int a, int b)
{
    return (a > b) ? b : a;
}

int main()
{
    srand(time(NULL)); // for random

    //hide console
    HWND Hide;
    AllocConsole();
    Hide = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Hide, 1);//1 - show, 0 - hide
    //

    sf::Texture texture_all;
    texture_all.loadFromFile("allSprites.png");
    sf::Texture texture_block;
    texture_block.loadFromFile("tiles.png");
    sf::Texture texture_base;
    texture_base.loadFromFile("sprites.png");

    Field field1;
    field1.setField(constants::field1);
    Tank tank1(true , 0);
    std::vector<Tank> tankAI{ {false, 0}, {false, 0}, {false, 0}, {false, 0} };
    std::vector<double> tankAIRespawnTime{ 0.0, 3.0, 6.0, 9.0};

    sf::RenderWindow window(sf::VideoMode(constants::windowWidth, constants::windowHeight), "", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(240);
    sf::View view = window.getDefaultView();

    view.zoom(constants::zoom);
    window.setView(view);
   
    Menu menu(constants::windowWidth,constants::windowHeight, 
        constants::MAX_NUMBER_OPTIONS_MAIN_MENU, constants::mainMenu, constants::menuOffset,constants::fontSize);
    StatisticBox stat(0, constants::windowHeight, 1+(constants::FIELD_WIDTH -4)* constants::TILES_LENGHT, 2* constants::TILES_LENGHT);
    sf::Clock clock, mainClock;
    double timer = 0, mainTimer = 0;
    int fps = 0;
    double delay = constants::delay;
    std::vector<Bullet> tmpBullets;
    bool isGameActive = false;
    bool isMP = false , isHost = false;
    while (window.isOpen())
    {
        sf::Event event;
        if (!isGameActive)
        {
            while (window.pollEvent(event))
            {
                if (isGameActive)
                    break;
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                {
                    int x = sf::Mouse::getPosition(window).x, y = sf::Mouse::getPosition(window).y;
                    /*std::cout << std::endl;
                    std::cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << std::endl;
                    std::cout << menu.choose(x, y) << std::endl;*/
                    switch (menu.choose(x, y))
                    {
                    case 0://new s0l0 game
                        newGame(tank1, tankAI, field1, tankAIRespawnTime);
                        clock.restart(); mainClock.restart();
                        isGameActive = true;
                        isMP = false;
                        timer = 0; mainTimer = 0;
                        fps = 0;
                        delay = constants::delay;
                        stat.statisticReset();
                        break;
                    case 1://new host
                        isGameActive = true;
                        isMP = true;
                        isHost = true;
                        break;
                    case 2://new client
                        isGameActive = true;
                        isMP = true;
                        isHost = false;
                        break;
                    default:
                        //std::cout << "Something wrong with mouse coordinate\n";
                        break;
                    }
                }
            }

            window.clear(sf::Color::Black);
            menu.draw(window);
            window.display();
        }
        else
        {
            if (!isMP)
            {
                timer = clock.getElapsedTime().asMilliseconds() / 1000.0;
                mainTimer = mainClock.getElapsedTime().asSeconds();
                stat.SetStatistics(static_cast<long>(mainTimer), static_cast<int>(constants::Stat::TIME));
                sf::Event event;
                if (timer > delay)
                {
                    while (window.pollEvent(event))
                    {
                        tank1.bullet_shoot(window, event);

                        if (event.type == sf::Event::Closed)
                            window.close();
                        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        //    isGameActive = false;
                    }
                    for (int i = 0; i < tankAIRespawnTime.size(); ++i)
                    {
                        if (timer > tankAIRespawnTime[i] && abs(timer - tankAIRespawnTime[i]) <= 15)
                        {
                            int xSpawn = rand() % 3;
                            for (int j = 0; j < tankAI.size(); ++j)
                            {
                                if (abs(tankAI[j].getCoordX() - (constants::DEFAULT_ENEMY_COORD_X[xSpawn])) <= 2.0 && tankAI[j].getCoordY() - (constants::DEFAULT_ENEMY_COORD_Y) <= 2.0)
                                {
                                    tankAIRespawnTime[i] = (static_cast<int>(tankAIRespawnTime[i]) + 3) % 256;
                                    continue;
                                }
                            }
                            if (abs(tank1.getCoordX() - (constants::DEFAULT_ENEMY_COORD_X[xSpawn])) <= 2.0 && tank1.getCoordY() - (constants::DEFAULT_ENEMY_COORD_Y) <= 2.0)
                            {
                                tankAIRespawnTime[i] = static_cast<int>(tankAIRespawnTime[i] + 3) % 256;
                                continue;
                            }
                            tankAI[i].setVisibility(true);
                            tankAI[i].setCoordX(constants::DEFAULT_ENEMY_COORD_X[xSpawn]);
                            tankAI[i].setSubCoordX(tankAI[i].getCoordX());
                            tankAI[i].setCoordY(constants::DEFAULT_ENEMY_COORD_Y);
                            tankAI[i].setSubCoordY(tankAI[i].getCoordY());
                            tankAIRespawnTime[i] = 257;
                        }
                    }

                    tank1.animation(fps);
                    for (int i = 0; i < tankAI.size(); ++i)
                    {
                        if (tankAI[i].isVisible())
                        {
                            for (int j = 0; j < tankAI[i].getBullets().size(); ++j)
                            {
                                if (tank1.getBullets().size() > 0 && tankAI[i].getBullets()[j].bulletWithBulletCollision(tank1.getBullets()[0]))
                                {
                                    tmpBullets = tank1.getBullets();
                                    tmpBullets.erase(tmpBullets.begin());
                                    tank1.setBullets(tmpBullets);
                                    tank1.setAlreadyShot(tank1.getAlreadyShot() - 1);
                                    tmpBullets = tankAI[i].getBullets();
                                    tmpBullets.erase(tmpBullets.begin() + j);
                                    tankAI[i].setBullets(tmpBullets);
                                    tankAI[i].setAlreadyShot(tankAI[i].getAlreadyShot() - 1);
                                }
                            }
                        }
                        if (tankAI[i].isVisible())
                        {
                            if (rand() % 64 == 0)
                            {
                                if (tankAI[i].getAlreadyShot() != tankAI[i].getMaxShots())
                                {
                                    tankAI[i].setAlreadyShot(tankAI[i].getAlreadyShot() + 1);
                                    tankAI[i].shot();
                                }
                            }
                            tankAI[i].bullets_colision(field1);
                            tankAI[i].animation(fps);
                        }
                        if (tankAI[i].isVisible() && tankAI[i].tankDeath(tank1))
                        {
                            field1.setEnemyCount(field1.getEnemyCount() - 1);
                            stat.SetStatistics(field1.getEnemyCount(), static_cast<int>(constants::Stat::ENEMIES));
                            tankAI[i].setVisibility(false);
                            tankAI[i].setCoordX(-10);
                            tankAI[i].setCoordY(-10);
                            tankAIRespawnTime[i] = (static_cast<int>(timer) + 3) % 256;
                            if (field1.getEnemyCount() == 0)
                            {
                                std::cout << "You win!\0";
                                Sleep(1000);
                                isGameActive = false;
                                continue;
                            } 
                        }
                        if (tankAI[i].isVisible() && tank1.tankDeath(tankAI[i]))
                        {
                            field1.setPlayerLives(field1.getPlayerLives() - 1);
                            tank1.setDirection(constants::Directions::UP);
                            tank1.setCoordX(constants::DEFAULT_PLAYER_COORD_X[0]);
                            tank1.setSubCoordX(constants::DEFAULT_PLAYER_COORD_X[0]);
                            tank1.setCoordY(constants::DEFAULT_PLAYER_COORD_Y);
                            tank1.setSubCoordY(constants::DEFAULT_PLAYER_COORD_Y);
                            stat.SetStatistics(field1.getPlayerLives(), static_cast<int>(constants::Stat::HP));
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
                        for (auto& tank : tankAI)
                        {
                            if (tank.isVisible())
                            {
                                tank.moveAIToBase(window, field1, event, tankAI);
                            }
                        }
                    }


                    /*for (int i = 0; i < tankAI.size(); ++i)
                    {
                        if (tankAI[i].tankWithTankCollision(tankAI) != -1)
                        {
                            tankAI[i].setDirection(static_cast<constants::Directions>((static_cast<int>(tankAI[i].getDirection()) + 2) % 4));
                            tankAI[tankAI[i].tankWithTankCollision(tankAI)].setDirection(static_cast<constants::Directions>((static_cast<int>(tankAI[tankAI[i].tankWithTankCollision(tankAI)].getDirection()) + 2) % 4));
                        }
                    }*/

                    delay += constants::delay;

                    ++fps;
                    //if (timer > 1 && fps < 129)
                    //{
                    //    std::cout << fps << "\n";
                    //    //exit(1);
                    //}


                    window.clear(sf::Color::Black);

                    tank1.control(window, field1, event, tankAI);
                    tank1.bullets_colision(field1);
                    field1.draw(window, texture_block, texture_base);
                    tank1.draw(window, texture_all); // coord in tiles // spawn tank
                    stat.draw(window);
                    for (auto& tank : tankAI)
                        if (tank.isVisible())
                            tank.draw(window, texture_all);

                    timer = 0;
                    window.display();

                    //clock.restart();
                    if (!field1.isBaseAlive() || field1.getPlayerLives()<=0)
                    {

                        
                        std::cout << "Game over!\0";
                        Sleep(1000);
                        isGameActive = false;
                        continue;
                    }
                }
                if (timer > constants::delay * 128 * 256)
                {
                    delay = constants::delay;
                    timer = 0;
                    clock.restart();
                }
            }

            if (isMP)
            {
                if (isHost)
                {
                    Server serv;
                    serv.server();
                    serv.loop(field1, tank1);
                }
                else
                {
                    Client cl;
                    cl.client();
                    cl.exchange(field1, tank1);
                }
            }
        }
    }
}