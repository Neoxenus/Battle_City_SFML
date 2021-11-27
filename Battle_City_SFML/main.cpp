#include "SFML\Graphics.hpp"
#include "windows.h"
#include "Field.h"
#include "Design_mode.h"
#include "Tank.h"
#include "Bullet.h"
#include <vector>
#include <ctime>
#include <iostream>

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

    for (int i = 0; i < constants::FIELD_HEIGHT; ++i)
    {
        for (int j = 0; j < constants::FIELD_WIDTH; ++j)
        {
            std::cout << field1.getField(j, i) << " ";
        }
        std::cout << "\n";
    }

    sf::RenderWindow window(sf::VideoMode(768, 768), "", sf::Style::Titlebar | sf::Style::Close);

    sf::View view = window.getDefaultView();
    view.zoom(0.33f);
    window.setView(view);
    window.setFramerateLimit(240);

    sf::Clock clock;
    double timer = 0;
    while (window.isOpen())
    {
        timer += clock.getElapsedTime().asMilliseconds();
        sf::Event event;
        if (timer > constants::delay)
        {
            while (window.pollEvent(event))
            {

                tank1.control(window, field1, event, bullets);

                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear(sf::Color::Black);
            field1.draw(window);
            tank1.draw(window); // coord in tiles // spawn tank
            for (int i = 0; i < bullets.size(); ++i)
                bullets[i].draw(window);

            // kyda pichnyt next?
            tank1.collision_bullet(field1, bullets);

            window.display();

            timer = 0;
            clock.restart();
        }
    }
    
}