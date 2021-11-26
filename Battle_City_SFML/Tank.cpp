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

	sprite_all.setTextureRect(sf::IntRect(0, 0, constants::BLOCK_LENGHT, constants::BLOCK_LENGHT));
    sprite_all.setPosition(5 * constants::BLOCK_LENGHT, 14 * constants::BLOCK_LENGHT);
    sprite_all.move(constants::WINDOW_OFFSET, constants::WINDOW_OFFSET);
	window.draw(sprite_all);
}
