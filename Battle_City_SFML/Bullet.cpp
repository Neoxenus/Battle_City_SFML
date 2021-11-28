#include "Bullet.h"

Bullet::Bullet(constants::Directions direction, double coordX, double coordY, int tankType, bool isPlayer)
{
	this->direction = direction;
    this->coordX = coordX + ((direction == constants::Directions::LEFT) ? constants::bulletSpawnOffset1 : 0) +
        ((direction == constants::Directions::RIGHT) ? constants::bulletSpawnOffset2 : 0);
    this->coordY = coordY + ((direction == constants::Directions::UP)? constants::bulletSpawnOffset1 :0) +
        ((direction == constants::Directions::DOWN) ? constants::bulletSpawnOffset2 : 0);
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
		if (direction == constants::Directions::UP)
		{
			this->coordY -= 0.1;
			sprite_all.setPosition(this->coordX * constants::TILES_LENGHT + constants::bulletOffset,
                this->coordY * constants::TILES_LENGHT );
		}
		else
		{
			this->coordY += 0.1;
			sprite_all.setPosition(this->coordX * constants::TILES_LENGHT + constants::bulletOffset,
                this->coordY * constants::TILES_LENGHT);
		}
	}
	if (direction == constants::Directions::LEFT || direction == constants::Directions::RIGHT)
	{
		sprite_all.setTextureRect(sf::IntRect(20 * constants::BLOCK_LENGHT + static_cast<int>(direction) * constants::TILES_LENGHT + 2,
			6 * constants::BLOCK_LENGHT + 5, 6, 5));
		if (direction == constants::Directions::LEFT)
		{
			this->coordX -= 0.1;
			sprite_all.setPosition(this->coordX * constants::TILES_LENGHT,
				this->coordY * constants::TILES_LENGHT + constants::bulletOffset);
		}
		else
		{
			this->coordX += 0.1;
			sprite_all.setPosition(this->coordX * constants::TILES_LENGHT,
                this->coordY * constants::TILES_LENGHT + constants::bulletOffset);
		}
	}
	sprite_all.move(constants::WINDOW_OFFSET, constants::WINDOW_OFFSET);
	window.draw(sprite_all);
}
double Bullet::getCoordX()
{
    return coordX;
}

double Bullet::getCoordY()
{
    return coordY;
}

void Bullet::updateCoord()
{
    if (direction == constants::Directions::UP || direction == constants::Directions::DOWN)
    {
        if (direction == constants::Directions::UP)
            this->coordY -= getBulletSpeed() * constants::delay;
        else
            this->coordY += getBulletSpeed() * constants::delay;
    }
    if (direction == constants::Directions::LEFT || direction == constants::Directions::RIGHT)
    {
        if (direction == constants::Directions::LEFT)
            this->coordX -= getBulletSpeed() * constants::delay;
        else
            this->coordX += getBulletSpeed() * constants::delay;
    }

}

double Bullet::getBulletSpeed()
{
    return  this->speed / 2;// * .0 / constants::TILES_LENGHT;
}

constants::Directions Bullet::getDirection()
{
    return direction;
}

bool Bullet::collision_bullet(Field& field)
{
    int x0, y0, curl, curr;
    constants::Directions direction = this->direction;

    if (direction == constants::Directions::UP || direction == constants::Directions::DOWN)
    {
        if (direction == constants::Directions::UP)
        {
            x0 = floor(this->getCoordX());
            y0 = floor(this->getCoordY());
        }
        else
        {
            x0 = floor(this->getCoordX());
            y0 = floor(this->getCoordY() + 6.0 / 8);
        }

        curl = static_cast<int>(field.getField(x0, y0));
        curr = static_cast<int>(field.getField(x0 + 1, y0));

        if (field.getField(x0, y0) != constants::Tiles::BLACK && field.getField(x0, y0) != constants::Tiles::ICE && field.getField(x0, y0) != constants::Tiles::TREE &&
            field.getField(x0, y0) != constants::Tiles::WATER1 && field.getField(x0, y0) != constants::Tiles::WATER2 && field.getField(x0, y0) != constants::Tiles::WATER3 ||
            field.getField(x0 + 1, y0) != constants::Tiles::BLACK && field.getField(x0 + 1, y0) != constants::Tiles::ICE && field.getField(x0 + 1, y0) != constants::Tiles::TREE &&
            field.getField(x0 + 1, y0) != constants::Tiles::WATER1 && field.getField(x0 + 1, y0) != constants::Tiles::WATER2 && field.getField(x0 + 1, y0) != constants::Tiles::WATER3)
        {
            field.setField(x0, y0, constants::bullet_collision[static_cast<int>(direction)][curl]);
            if (curl != static_cast<int>(constants::Tiles::BRICK0101) || curr != static_cast<int>(constants::Tiles::BRICK1100))
                field.setField(x0 + 1, y0, constants::bullet_collision[static_cast<int>(direction)][curr]);
            return true;
        }
        else
            return false;
    }
    else
    {
        if (direction == constants::Directions::LEFT)
        {
            x0 = floor(this->getCoordX());
            y0 = floor(this->getCoordY());
        }
        else
        {
            x0 = floor(this->getCoordX() + 6.0 / 8);
            y0 = floor(this->getCoordY());
        }

        curl = static_cast<int>(field.getField(x0, y0));
        curr = static_cast<int>(field.getField(x0, y0 + 1));

        if (field.getField(x0, y0) != constants::Tiles::BLACK && field.getField(x0, y0) != constants::Tiles::ICE && field.getField(x0, y0) != constants::Tiles::TREE &&
            field.getField(x0, y0) != constants::Tiles::WATER1 && field.getField(x0, y0) != constants::Tiles::WATER2 && field.getField(x0, y0) != constants::Tiles::WATER3 ||
            field.getField(x0, y0 + 1) != constants::Tiles::BLACK && field.getField(x0, y0 + 1) != constants::Tiles::ICE && field.getField(x0, y0 + 1) != constants::Tiles::TREE &&
            field.getField(x0, y0 + 1) != constants::Tiles::WATER1 && field.getField(x0, y0 + 1) != constants::Tiles::WATER2 && field.getField(x0, y0 + 1) != constants::Tiles::WATER3)
        {
            field.setField(x0, y0, constants::bullet_collision[static_cast<int>(direction)][curl]);
            if (curl != static_cast<int>(constants::Tiles::BRICK0011) || curr != static_cast<int>(constants::Tiles::BRICK0101))
                field.setField(x0, y0 + 1, constants::bullet_collision[static_cast<int>(direction)][curr]);
            return true;
        }
        else
            return false;
    }
}
