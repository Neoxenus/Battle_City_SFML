#include "Tank.h"

double Tank::getTankSpeed()
{
    {
        if (isPlayer)
        {
            return constants::tankSpeed[tankType] * 16.0;
        }
        else
            return constants::tankSpeed[4 + tankType] * 16.0;
    }
}

void Tank::draw(sf::RenderWindow& window)
{
	sf::Texture texture_all;
	texture_all.loadFromFile("allSprites.png");
	sf::Sprite sprite_all(texture_all);

	sprite_all.setTextureRect(sf::IntRect(2 * tankType * constants::BLOCK_LENGHT, 
        2 * static_cast<int>(direction) * constants::BLOCK_LENGHT,
        constants::BLOCK_LENGHT, constants::BLOCK_LENGHT));
    sprite_all.setPosition(constants::DEFAULT_PLAYER_COORD_X[0] * constants::TILES_LENGHT,
        constants::DEFAULT_PLAYER_COORD_Y * constants::TILES_LENGHT);
    sprite_all.move(constants::WINDOW_OFFSET, constants::WINDOW_OFFSET);
	window.draw(sprite_all);
}

void Tank::control(sf::RenderWindow& window, Field field)
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::W)
            {
                //if()
                this->coordY--;
            }
            else if (event.key.code == sf::Keyboard::S)
            {
                this->coordY++;
            }
            else if (event.key.code == sf::Keyboard::A)
            {
                this->coordX--;
            }
            else if (event.key.code == sf::Keyboard::D)
            {
                this->coordX++;
            }
        }
    }
}