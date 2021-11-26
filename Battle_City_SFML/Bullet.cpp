#include "Bullet.h"

Bullet::Bullet(constants::Directions direction, double coordX, double coordY, int tankType, bool isPlayer)
{
	this->direction = direction;
	this->coordX = coordX, this->coordY = coordY;
	this->speed = constants::bulletSpeed[tankType + 4 * (isPlayer == false)];
}

void Bullet::draw(sf::RenderWindow& window)
{
	sf::Texture texture_all;
	texture_all.loadFromFile("allSprites.png");
	sf::Sprite sprite_all(texture_all);
	if (direction == constants::Directions::UP || direction == constants::Directions::DOWN)
	{
		sprite_all.setTextureRect(sf::IntRect(20 * constants::BLOCK_LENGHT + static_cast<int>(direction) * constants::TILES_LENGHT + 2,
			6 * constants::BLOCK_LENGHT + 5, 5, 6));
		if(direction == constants::Directions::UP)
			sprite_all.setPosition(this->coordX * constants::TILES_LENGHT + 
				static_cast<int>(constants::BLOCK_LENGHT) / 2 - 3, this->coordY-- * constants::TILES_LENGHT - 5);
		else
			sprite_all.setPosition(this->coordX * constants::TILES_LENGHT + 
				static_cast<int>(constants::BLOCK_LENGHT) / 2 - 3, 
				this->coordY++ * constants::TILES_LENGHT + static_cast<int>(constants::BLOCK_LENGHT));
	}
	if (direction == constants::Directions::LEFT || direction == constants::Directions::RIGHT)
	{
		sprite_all.setTextureRect(sf::IntRect(20 * constants::BLOCK_LENGHT + static_cast<int>(direction) * constants::TILES_LENGHT + 2,
			6 * constants::BLOCK_LENGHT + 5, 6, 5));
		if (direction == constants::Directions::LEFT)
			sprite_all.setPosition(this->coordX-- * constants::TILES_LENGHT - 5, 
				this->coordY * constants::TILES_LENGHT + static_cast<int>(constants::BLOCK_LENGHT) / 2 - 3);
		else
			sprite_all.setPosition(this->coordX++ * constants::TILES_LENGHT + constants::BLOCK_LENGHT, this->coordY * constants::TILES_LENGHT + static_cast<int>(constants::BLOCK_LENGHT) / 2 - 3);
	}
	sprite_all.move(constants::WINDOW_OFFSET, constants::WINDOW_OFFSET);
	window.draw(sprite_all);
}
