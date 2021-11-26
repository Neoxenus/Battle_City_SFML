#include "Bullet.h"
#include "Tank.h"
#include "Constants.h"

Bullet::Bullet(Tank tank)
{
	direction = tank.getDirection();
	coordX = tank.getCoordX(), coordY = tank.getCoordY();
	speed = constants::bulletSpeed[tank.getTankType() + 4 * (tank.getIsPlayer() == false)];
}

void Bullet::draw(sf::RenderWindow& window)
{
	sf::Texture texture_all;
	texture_all.loadFromFile("allSprites.png");
	sf::Sprite sprite_all(texture_all);
	sprite_all.setTextureRect(sf::IntRect(20 * constants::BLOCK_LENGHT + static_cast<int>(direction) * constants::BLOCK_LENGHT,
		6 * constants::BLOCK_LENGHT, constants::BLOCK_LENGHT, constants::BLOCK_LENGHT));
	sprite_all.setPosition(this->coordX++ * constants::TILES_LENGHT, this->coordY++ * constants::TILES_LENGHT);
	sprite_all.move(constants::WINDOW_OFFSET, constants::WINDOW_OFFSET);
	window.draw(sprite_all);
}
