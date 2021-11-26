#include "Field.h"

Field::Field()
{
	std::vector<std::vector<int>> field(constants::FIELD_HEIGHT, std::vector<int>(constants::FIELD_WIDTH, 0));
	this->field = field;
}

Field::~Field()
{
}

int Field::getField(int x, int y)
{
	if (x < 0 || x >= constants::FIELD_WIDTH || y < 0 || y >= constants::FIELD_HEIGHT)
		return -1;
	return field[y][x];
}

void Field::setField(int x, int y, constants::Tiles value)
{
	if (x < 0 || x >= constants::FIELD_WIDTH || y < 0 || y >= constants::FIELD_HEIGHT)
		exit(-1);
	field[y][x] = static_cast<int>(value);
	return;
}

void Field::setField(const std::vector<std::vector<int>> level)
{
	for (int i = 0; i < constants::BLOCK_HEIGHT; ++i)
		for (int j = 0; j < constants::BLOCK_WIDTH; ++j)
		{
			int p = 0;
			this->setField(j * 2, i * 2, constants::toTiles[level[i][j]][p++]);
			this->setField(j * 2 + 1, i * 2, constants::toTiles[level[i][j]][p++]);
			this->setField(j * 2, i * 2 + 1, constants::toTiles[level[i][j]][p++]);
			this->setField(j * 2 + 1, i * 2 + 1, constants::toTiles[level[i][j]][p++]);
				
		}
}

void Field::draw(sf::RenderWindow& window)
{
	sf::Texture texture_block;
	texture_block.loadFromFile("tiles.png");
	sf::Sprite s_block(texture_block);

	sf::Texture texture_base;
	texture_base.loadFromFile("sprites.png");
	sf::Sprite s_default(texture_base);

	window.clear(sf::Color::White);

	for(int i = 0; i < constants::FIELD_HEIGHT; ++i)
		for (int j = 0; j < constants::FIELD_WIDTH; ++j)
		{
			s_block.setTextureRect(sf::IntRect(constants::TILES_LENGHT * field[i][j], 0, constants::TILES_LENGHT, constants::TILES_LENGHT));
			s_block.setPosition(j * constants::TILES_LENGHT, i * constants::TILES_LENGHT);
			s_block.move(constants::WINDOW_OFFSET, constants::WINDOW_OFFSET);
			window.draw(s_block);
		}

	s_default.setTextureRect(sf::IntRect(constants::BLOCK_LENGHT * (int)constants::Blocks::BASE, 0, constants::BLOCK_LENGHT, constants::BLOCK_LENGHT));
	s_default.setPosition(7 * constants::BLOCK_LENGHT, 14 * constants::BLOCK_LENGHT);
	s_default.move(constants::WINDOW_OFFSET, constants::WINDOW_OFFSET);
	window.draw(s_default);

		}
}