#include "Field.h"

Field::Field()
{
	std::vector<std::vector<int>> blocks(constants::FIELD_HEIGHT, std::vector<int>(constants::FIELD_WIDTH));
}

Field::~Field()
{
}

void Field::draw(sf::RenderWindow& window)
{
	sf::Texture texture;
	texture.loadFromFile("tiles.png");
	sf::Sprite sprites(texture);

	for(int i = 0; i < constants::FIELD_HEIGHT; ++i)
		for (int j = 0; j < constants::FIELD_WIDTH; ++j)
		{
			//sprites.setTextureRect(sf::IntRect(constants::BLOCK_LENGHT * blocks[i][j], 0, constants::BLOCK_LENGHT, constants::BLOCK_LENGHT));
			sprites.setPosition(i * constants::BLOCK_LENGHT, j * constants::BLOCK_LENGHT);
			window.draw(sprites);
		}
}