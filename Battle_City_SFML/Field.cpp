#include "Field.h"

Field::Field()
{
	std::vector<std::vector<int>> field(constants::FIELD_HEIGHT, std::vector<int>(constants::FIELD_WIDTH, 0));
	this->field = field;
}

Field::~Field()
{
}

void Field::setPlayerLives(int val)
{
	this->playerLives = val;
}

int Field::getPlayerLives()
{
	return this->playerLives;
}

void Field::setEnemyCount(int val)
{
	this->enemyCount = val;
}

int Field::getEnemyCount()
{
	return this->enemyCount;
}

void Field::setEnemyToSpawn(int val)
{
	this->enemyToSpawn = val;
}

int Field::getEnemyToSpawn()
{
	return this->enemyToSpawn;
}

bool Field::isBaseAlive()
{
	int i = 28;  int j = 14;
		
	return (field[i][j] == constants::BASE && field[i][j + 1] == constants::BASE &&
		field[i + 1][j] == constants::BASE && field[i + 1][j + 1] == constants::BASE);
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

void Field::setField(const std::vector<std::vector<int>>& level)
{
	for (int i = 0; i < constants::FIELD_HEIGHT / 2; ++i)
		for (int j = 0; j < constants::FIELD_HEIGHT / 2; ++j)
		{
			int p = 0;
			this->setField(j * 2, i * 2, constants::toTiles[level[i][j]][p++]);
			this->setField(j * 2 + 1, i * 2, constants::toTiles[level[i][j]][p++]);
			this->setField(j * 2, i * 2 + 1, constants::toTiles[level[i][j]][p++]);
			this->setField(j * 2 + 1, i * 2 + 1, constants::toTiles[level[i][j]][p++]);				
		}
	this->setField(13,27, constants::BRICK1111);
	this->setField(16, 27, constants::BRICK1111);
	playerLives = constants::defultPlayerLives;
	enemyCount = constants::defaultEnemyCount;
	enemyToSpawn = constants::defaultEnemyCount;
}

void Field::draw(sf::RenderWindow& window, sf::Texture& texture_block, sf::Texture& texture_base)
{
	sf::Sprite s_block(texture_block);

	sf::Sprite s_default(texture_base);

	window.clear(sf::Color::White);

	s_default.setTextureRect(sf::IntRect(constants::BLOCK_LENGHT * (int)constants::Blocks::GRAY, 0, constants::BLOCK_LENGHT, constants::BLOCK_LENGHT));
	for(int i = 0; i < constants::FIELD_HEIGHT; ++i)
		for (int j = 0; j < constants::FIELD_WIDTH; ++j)
		{
			if (i == 0 || i == 31 || j == 0 || j == 29 || j == 31)
			{
				s_default.setPosition(j/2 * constants::BLOCK_LENGHT, i/2 * constants::BLOCK_LENGHT);
				s_default.move(constants::WINDOW_OFFSET, constants::WINDOW_OFFSET);
				window.draw(s_default);
			}
			else if (i == 1 || i == 32 || j == 1 || j == 30 || j == 32 || (i == 28 && j == 15) || (i == 29 && j == 14) || (i == 29 && j == 15))
			{
				continue;
			}
			else if (i == 28 && j == 14)
			{
				if (field[i][j] == constants::BASE && field[i][j + 1] == constants::BASE && field[i + 1][j] == constants::BASE && field[i + 1][j + 1] == constants::BASE)
				{
					s_default.setTextureRect(sf::IntRect(constants::BLOCK_LENGHT * (int)constants::Blocks::BASE, 0, constants::BLOCK_LENGHT, constants::BLOCK_LENGHT));
					s_default.setPosition(j / 2 * constants::BLOCK_LENGHT, i / 2 * constants::BLOCK_LENGHT);
					s_default.move(constants::WINDOW_OFFSET, constants::WINDOW_OFFSET);
					window.draw(s_default);
					s_default.setTextureRect(sf::IntRect(constants::BLOCK_LENGHT * (int)constants::Blocks::GRAY, 0, constants::BLOCK_LENGHT, constants::BLOCK_LENGHT));
				}
				else
				{
					s_default.setTextureRect(sf::IntRect(constants::BLOCK_LENGHT * (int)constants::Blocks::FLAG, 0, constants::BLOCK_LENGHT, constants::BLOCK_LENGHT));
					s_default.setPosition(j / 2 * constants::BLOCK_LENGHT, i / 2 * constants::BLOCK_LENGHT);
					s_default.move(constants::WINDOW_OFFSET, constants::WINDOW_OFFSET);
					window.draw(s_default);
					s_default.setTextureRect(sf::IntRect(constants::BLOCK_LENGHT * (int)constants::Blocks::GRAY, 0, constants::BLOCK_LENGHT, constants::BLOCK_LENGHT));
				}
			}
			else
			{
				s_block.setTextureRect(sf::IntRect(constants::TILES_LENGHT * field[i][j], 0, constants::TILES_LENGHT, constants::TILES_LENGHT));
				s_block.setPosition(j * constants::TILES_LENGHT, i * constants::TILES_LENGHT);
				s_block.move(constants::WINDOW_OFFSET, constants::WINDOW_OFFSET);
				window.draw(s_block);
			}
		}
	

	/*BASE
	s_default.setTextureRect(sf::IntRect(constants::BLOCK_LENGHT * (int)constants::Blocks::BASE, 0, constants::BLOCK_LENGHT, constants::BLOCK_LENGHT));
	s_default.setPosition(7 * constants::BLOCK_LENGHT, 14 * constants::BLOCK_LENGHT);
	s_default.move(constants::WINDOW_OFFSET, constants::WINDOW_OFFSET);
	window.draw(s_default);

	s_block.setTextureRect(sf::IntRect(constants::TILES_LENGHT * constants::Tiles::BRICK1111, 0, constants::TILES_LENGHT, constants::TILES_LENGHT));
	s_block.setPosition(13 * constants::TILES_LENGHT, 27 * constants::TILES_LENGHT);
	s_block.move(constants::WINDOW_OFFSET, constants::WINDOW_OFFSET);
	window.draw(s_block);

	s_block.setTextureRect(sf::IntRect(constants::TILES_LENGHT * constants::Tiles::BRICK1111, 0, constants::TILES_LENGHT, constants::TILES_LENGHT));
	s_block.setPosition(16 * constants::TILES_LENGHT, 27 * constants::TILES_LENGHT);
	s_block.move(constants::WINDOW_OFFSET, constants::WINDOW_OFFSET);
	window.draw(s_block);
	*/
}

std::vector<char*> Field::sendToServer()
{
	std::vector<char*> fieldCh;
	for (int i = 0; i < field.size(); ++i)
		for (int j = 0; j < field.size(); ++j)
			fieldCh.push_back(convertToCharArray(field[i][j]));
	return fieldCh;
}

void Field::newField(std::vector<std::string> data)
{
	for(int j =0;j<constants::FIELD_HEIGHT;++j)
		for (int i = 0; i < constants::FIELD_WIDTH; ++i)
		{
			this->setField(i, j, static_cast<constants::Tiles>(static_cast<int>(convertBackFromCharArrayToDouble(convertFromStringToCharArray(data[i+j* constants::FIELD_WIDTH])))));
		}
}
