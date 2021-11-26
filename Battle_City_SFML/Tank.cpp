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

//void Tank::draw(sf::RenderWindow& window)
//{
//	sf::Texture texture_block;
//	texture_block.loadFromFile("tiles.png");
//	sf::Sprite s_block(texture_block);
//
//	window.clear(sf::Color::White);
//
//	for (int i = 0; i < constants::FIELD_HEIGHT; i += 2)
//		for (int j = 0; j < constants::FIELD_WIDTH; j += 2)
//		{
//			s_block.setTextureRect(sf::IntRect(constants::BLOCK_LENGHT * field[i][j], 0, constants::BLOCK_LENGHT, constants::BLOCK_LENGHT));
//			s_block.setPosition(j * constants::BLOCK_LENGHT, i * constants::BLOCK_LENGHT);
//			s_block.move(constants::WINDOW_OFFSET, constants::WINDOW_OFFSET);
//			window.draw(s_block);
//
//		}
//}
