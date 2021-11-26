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
	sf::Texture texture_block;
	texture_block.loadFromFile("sprites.png");
	sf::Sprite s_block(texture_block);

	window.clear(sf::Color::White);

	for(int i = 0; i < constants::FIELD_HEIGHT; i += 2)
		for (int j = 0; j < constants::FIELD_WIDTH; j += 2)
		{
			s_block.setTextureRect(sf::IntRect(constants::BLOCK_LENGHT * blocks[i][j], 0, constants::BLOCK_LENGHT, constants::BLOCK_LENGHT));
			s_block.setPosition(j * constants::BLOCK_LENGHT, i * constants::BLOCK_LENGHT);
			s_block.move(constants::WINDOW_OFFSET, constants::WINDOW_OFFSET);
			window.draw(s_block);

		}
	window.display();
}