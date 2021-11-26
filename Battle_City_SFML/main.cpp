#include "SFML\Graphics.hpp"
#include "windows.h"
#include "Field.h"
#include "Design_mode.h"
#include "Tank.h"
#include "Bullet.h"
#include <vector>
#include <ctime>

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
    //Design_mode designm;
    Tank tank1(true , 0);
    std::vector<Bullet> bullets;

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
            window.display();

            timer = 0;
            clock.restart();
        }
    }
    
}