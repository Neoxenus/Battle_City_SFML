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
    return  this->speed * 1.0;
}

constants::Directions Bullet::getDirection()
{
    return direction;
}

bool Bullet::collision_bullet(Field& field)
{
    int x0, y0, xr, yd;
    constants::Directions direction = this->direction;
    x0 = floor(this->getCoordX());
    y0 = floor(this->getCoordY());
    xr = floor(this->getCoordX() + 6.0 / 8);//+ 6.0 / 8);
    yd = floor(this->getCoordY() + 6.0 / 8);//+ 6.0 / 8);

    if (direction == constants::Directions::UP)
    {
        if (field.getField(x0, y0) == constants::Tiles::BRICK1111)
        {
            field.setField(x0, y0, constants::Tiles::BRICK1100);
            if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1111)
                field.setField(x0 + 1, y0, constants::Tiles::BRICK1100);

            return true;
        }
        else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1111)
        {
            field.setField(x0 + 1, y0, constants::Tiles::BRICK1100);
            return true;
        }

        //2

        else if (field.getField(x0, y0) == constants::Tiles::BRICK1100 && field.getField(x0 + 1, y0) != constants::Tiles::METAL)
        {
            field.setField(x0, y0, constants::Tiles::BLACK);
            if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1100)
                field.setField(x0 + 1, y0, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1100 && field.getField(x0, y0) != constants::Tiles::METAL)
        {
            field.setField(x0 + 1, y0, constants::Tiles::BLACK);
            return true;
        }

        else if (field.getField(x0, y0) == constants::Tiles::BRICK0011)
        {
            field.setField(x0, y0, constants::Tiles::BLACK);
            if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0011)
                field.setField(x0 + 1, y0, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0011)
        {
            field.setField(x0 + 1, y0, constants::Tiles::BLACK);
            return true;
        }

        else if (field.getField(x0, y0) == constants::Tiles::BRICK1010)
        {
            field.setField(x0, y0, constants::Tiles::BRICK1000);
            if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1010)
                field.setField(x0 + 1, y0, constants::Tiles::BRICK1000);

            return true;
        }
        else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1010)
        {
            field.setField(x0 + 1, y0, constants::Tiles::BRICK1000);
            return true;
        }

        else if (field.getField(x0, y0) == constants::Tiles::BRICK0101)
        {
            field.setField(x0, y0, constants::Tiles::BRICK0100);
            if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0101)
                field.setField(x0 + 1, y0, constants::Tiles::BRICK0100);

            return true;
        }
        else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0101)
        {
            field.setField(x0 + 1, y0, constants::Tiles::BRICK0100);
            return true;
        }

        //3

        else if (field.getField(x0, y0) == constants::Tiles::BRICK0111)
        {
            field.setField(x0, y0, constants::Tiles::BRICK0100);
            if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0111)
                field.setField(x0 + 1, y0, constants::Tiles::BRICK0100);

            return true;
        }
        else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0111)
        {
            field.setField(x0 + 1, y0, constants::Tiles::BRICK0100);
            return true;
        }

        else if (field.getField(x0, y0) == constants::Tiles::BRICK1011)
        {
            field.setField(x0, y0, constants::Tiles::BRICK1000);
            if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1011)
                field.setField(x0 + 1, y0, constants::Tiles::BRICK1000);

            return true;
        }
        else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1011)
        {
            field.setField(x0 + 1, y0, constants::Tiles::BRICK1000);
            return true;
        }

        else if (field.getField(x0, y0) == constants::Tiles::BRICK1101)
        {
            field.setField(x0, y0, constants::Tiles::BRICK1100);
            if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1101)
                field.setField(x0 + 1, y0, constants::Tiles::BRICK1100);

            return true;
        }
        else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1101)
        {
            field.setField(x0 + 1, y0, constants::Tiles::BRICK1100);
            return true;
        }

        else if (field.getField(x0, y0) == constants::Tiles::BRICK1110)
        {
            field.setField(x0, y0, constants::Tiles::BRICK1100);
            if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1110)
                field.setField(x0 + 1, y0, constants::Tiles::BRICK1100);

            return true;
        }
        else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1110)
        {
            field.setField(x0 + 1, y0, constants::Tiles::BRICK1100);
            return true;
        }


        //1
        else if (field.getField(x0, y0) == constants::Tiles::BRICK1000 && field.getField(x0 + 1, y0) != constants::Tiles::METAL)
        {
            field.setField(x0, y0, constants::Tiles::BLACK);
            if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1000)
                field.setField(x0 + 1, y0, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1000 && field.getField(x0, y0) != constants::Tiles::METAL)
        {
            field.setField(x0 + 1, y0, constants::Tiles::BLACK);
            return true;
        }

        else if (field.getField(x0, y0) == constants::Tiles::BRICK0100 && field.getField(x0 + 1, y0) != constants::Tiles::METAL)
        {
            field.setField(x0, y0, constants::Tiles::BLACK);
            if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0100)
                field.setField(x0 + 1, y0, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0100 && field.getField(x0, y0) != constants::Tiles::METAL)
        {
            field.setField(x0 + 1, y0, constants::Tiles::BLACK);
            return true;
        }

        else if (field.getField(x0, y0) == constants::Tiles::BRICK0010)
        {
            field.setField(x0, y0, constants::Tiles::BLACK);
            if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0010)
                field.setField(x0 + 1, y0, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0010)
        {
            field.setField(x0 + 1, y0, constants::Tiles::BLACK);
            return true;
        }

        else if (field.getField(x0, y0) == constants::Tiles::BRICK0001)
        {
            field.setField(x0, y0, constants::Tiles::BLACK);
            if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0001)
                field.setField(x0 + 1, y0, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0001)
        {
            field.setField(x0 + 1, y0, constants::Tiles::BLACK);
            return true;
        }

        //0

        else if (field.getField(x0, y0) != constants::Tiles::BLACK && field.getField(x0, y0) != constants::Tiles::ICE && field.getField(x0, y0) != constants::Tiles::TREE &&
        field.getField(x0, y0) != constants::Tiles::WATER1 && field.getField(x0, y0) != constants::Tiles::WATER2 && field.getField(x0, y0) != constants::Tiles::WATER3)
        {
            return true;
        }
    }

    else if (direction == constants::Directions::DOWN)
    {
        if (field.getField(x0, yd) == constants::Tiles::BRICK1111)
        {
            field.setField(x0, yd, constants::Tiles::BRICK0011);
            if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1111)
                field.setField(x0 + 1, yd, constants::Tiles::BRICK0011);

            return true;
        }
        else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1111)
        {
            field.setField(x0 + 1, yd, constants::Tiles::BRICK0011);
            return true;
        }

        //2

        else if (field.getField(x0, yd) == constants::Tiles::BRICK1100)
        {
            field.setField(x0, yd, constants::Tiles::BLACK);
            if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1100)
                field.setField(x0 + 1, yd, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1100)
        {
            field.setField(x0 + 1, yd, constants::Tiles::BLACK);
            return true;
        }

        else if (field.getField(x0, yd) == constants::Tiles::BRICK0011 && field.getField(x0 + 1, yd) != constants::Tiles::METAL)
        {
            field.setField(x0, yd, constants::Tiles::BLACK);
            if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0011)
                field.setField(x0 + 1, yd, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0011 && field.getField(x0, yd) != constants::Tiles::METAL)
        {
            field.setField(x0 + 1, yd, constants::Tiles::BLACK);
            return true;
        }

        else if (field.getField(x0, yd) == constants::Tiles::BRICK1010)
        {
            field.setField(x0, yd, constants::Tiles::BRICK0010);
            if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1010)
                field.setField(x0 + 1, yd, constants::Tiles::BRICK0010);

            return true;
        }
        else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1010)
        {
            field.setField(x0 + 1, yd, constants::Tiles::BRICK0010);
            return true;
        }

        else if (field.getField(x0, yd) == constants::Tiles::BRICK0101)
        {
            field.setField(x0, yd, constants::Tiles::BRICK0001);
            if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0101)
                field.setField(x0 + 1, yd, constants::Tiles::BRICK0001);

            return true;
        }
        else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0101)
        {
            field.setField(x0 + 1, yd, constants::Tiles::BRICK0001);
            return true;
        }

        //3

        else if (field.getField(x0, yd) == constants::Tiles::BRICK0111)
        {
            field.setField(x0, yd, constants::Tiles::BRICK0011);
            if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0111)
                field.setField(x0 + 1, yd, constants::Tiles::BRICK0011);

            return true;
        }
        else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0111)
        {
            field.setField(x0 + 1, yd, constants::Tiles::BRICK0011);
            return true;
        }

        else if (field.getField(x0, yd) == constants::Tiles::BRICK1011)
        {
            field.setField(x0, yd, constants::Tiles::BRICK0011);
            if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1011)
                field.setField(x0 + 1, yd, constants::Tiles::BRICK0011);

            return true;
        }
        else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1011)
        {
            field.setField(x0 + 1, yd, constants::Tiles::BRICK0011);
            return true;
        }

        else if (field.getField(x0, yd) == constants::Tiles::BRICK1101)
        {
            field.setField(x0, yd, constants::Tiles::BRICK0001);
            if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1101)
                field.setField(x0 + 1, yd, constants::Tiles::BRICK0001);

            return true;
        }
        else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1101)
        {
            field.setField(x0 + 1, yd, constants::Tiles::BRICK0001);
            return true;
        }

        else if (field.getField(x0, yd) == constants::Tiles::BRICK1110)
        {
            field.setField(x0, yd, constants::Tiles::BRICK0010);
            if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1110)
                field.setField(x0 + 1, yd, constants::Tiles::BRICK0010);

            return true;
        }
        else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1110)
        {
            field.setField(x0 + 1, yd, constants::Tiles::BRICK0010);
            return true;
        }


        //1

        else if (field.getField(x0, yd) == constants::Tiles::BRICK1000)
        {
            field.setField(x0, yd, constants::Tiles::BLACK);
            if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1000)
                field.setField(x0 + 1, yd, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1000)
        {
            field.setField(x0 + 1, yd, constants::Tiles::BLACK);
            return true;
        }

        else if (field.getField(x0, yd) == constants::Tiles::BRICK0100)
        {
            field.setField(x0, yd, constants::Tiles::BLACK);
            if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0100)
                field.setField(x0 + 1, yd, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0100)
        {
            field.setField(x0 + 1, yd, constants::Tiles::BLACK);
            return true;
        }

        else if (field.getField(x0, yd) == constants::Tiles::BRICK0010 && field.getField(x0 + 1, yd) != constants::Tiles::METAL)
        {
            field.setField(x0, yd, constants::Tiles::BLACK);
            if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0010)
                field.setField(x0 + 1, yd, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0010 && field.getField(x0, yd) != constants::Tiles::METAL)
        {
            field.setField(x0 + 1, yd, constants::Tiles::BLACK);
            return true;
        }

        else if (field.getField(x0, yd) == constants::Tiles::BRICK0001 && field.getField(x0 + 1, yd) != constants::Tiles::METAL)
        {
            field.setField(x0, yd, constants::Tiles::BLACK);
            if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0001)
                field.setField(x0 + 1, yd, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0001 && field.getField(x0, yd) != constants::Tiles::METAL)
        {
            field.setField(x0 + 1, yd, constants::Tiles::BLACK);
            return true;
        }

        //0

        else if (field.getField(x0, yd) != constants::Tiles::BLACK && field.getField(x0, yd) != constants::Tiles::ICE && field.getField(x0, yd) != constants::Tiles::TREE &&
        field.getField(x0, yd) != constants::Tiles::WATER1 && field.getField(x0, yd) != constants::Tiles::WATER2 && field.getField(x0, yd) != constants::Tiles::WATER3)
        {
            return true;
        }
    }

    else if (direction == constants::Directions::LEFT)
    {
        if (field.getField(x0, y0) == constants::Tiles::BRICK1111)
        {
            field.setField(x0, y0, constants::Tiles::BRICK1010);
            if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1111)
                field.setField(x0, y0 + 1, constants::Tiles::BRICK1010);

            return true;
        }
        else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1111)
        {
            field.setField(x0, y0 + 1, constants::Tiles::BRICK1010);
            return true;
        }

        //2

        else if (field.getField(x0, y0) == constants::Tiles::BRICK1100)
        {
            field.setField(x0, y0, constants::Tiles::BRICK1000);
            if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1100)
                field.setField(x0, y0 + 1, constants::Tiles::BRICK1000);

            return true;
        }
        else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1100)
        {
            field.setField(x0, y0 + 1, constants::Tiles::BRICK1000);
            return true;
        }

        else if (field.getField(x0, y0) == constants::Tiles::BRICK0011)
        {
            field.setField(x0, y0, constants::Tiles::BRICK0010);
            if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0011)
                field.setField(x0, y0 + 1, constants::Tiles::BRICK0010);

            return true;
        }
        else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0011)
        {
            field.setField(x0, y0 + 1, constants::Tiles::BRICK0010);
            return true;
        }

        else if (field.getField(x0, y0) == constants::Tiles::BRICK1010 && field.getField(x0, y0 + 1) != constants::Tiles::METAL)
        {
            field.setField(x0, y0, constants::Tiles::BLACK);
            if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1010)
                field.setField(x0, y0 + 1, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1010 && field.getField(x0, y0) != constants::Tiles::METAL)
        {
            field.setField(x0, y0 + 1, constants::Tiles::BLACK);
            return true;
        }

        else if (field.getField(x0, y0) == constants::Tiles::BRICK0101)
        {
            field.setField(x0, y0, constants::Tiles::BLACK);
            if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0101)
                field.setField(x0, y0 + 1, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0101)
        {
            field.setField(x0, y0 + 1, constants::Tiles::BLACK);
            return true;
        }

        //3

        else if (field.getField(x0, y0) == constants::Tiles::BRICK0111)
        {
            field.setField(x0, y0, constants::Tiles::BRICK0010);
            if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0111)
                field.setField(x0, y0 + 1, constants::Tiles::BRICK0010);

            return true;
        }
        else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0111)
        {
            field.setField(x0, y0 + 1, constants::Tiles::BRICK0010);
            return true;
        }

        else if (field.getField(x0, y0) == constants::Tiles::BRICK1011)
        {
            field.setField(x0, y0, constants::Tiles::BRICK1010);
            if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1011)
                field.setField(x0, y0 + 1, constants::Tiles::BRICK1010);

            return true;
        }
        else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1011)
        {
            field.setField(x0, y0 + 1, constants::Tiles::BRICK1010);
            return true;
        }

        else if (field.getField(x0, y0) == constants::Tiles::BRICK1101)
        {
            field.setField(x0, y0, constants::Tiles::BRICK1000);
            if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1101)
                field.setField(x0, y0 + 1, constants::Tiles::BRICK1000);

            return true;
        }
        else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1101)
        {
            field.setField(x0, y0 + 1, constants::Tiles::BRICK1000);
            return true;
        }

        else if (field.getField(x0, y0) == constants::Tiles::BRICK1110)
        {
            field.setField(x0, y0, constants::Tiles::BRICK1000);
            if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1110)
                field.setField(x0, y0 + 1, constants::Tiles::BRICK1000);

            return true;
        }
        else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1110)
        {
            field.setField(x0, y0 + 1, constants::Tiles::BRICK1000);
            return true;
        }


        //1
        else if (field.getField(x0, y0) == constants::Tiles::BRICK1000 && field.getField(x0, y0 + 1) != constants::Tiles::METAL)
        {
            field.setField(x0, y0, constants::Tiles::BLACK);
            if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1000)
                field.setField(x0, y0 + 1, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1000 && field.getField(x0, y0) != constants::Tiles::METAL)
        {
            field.setField(x0, y0 + 1, constants::Tiles::BLACK);
            return true;
        }

        else if (field.getField(x0, y0) == constants::Tiles::BRICK0100)
        {
            field.setField(x0, y0, constants::Tiles::BLACK);
            if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0100)
                field.setField(x0, y0 + 1, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0100)
        {
            field.setField(x0, y0 + 1, constants::Tiles::BLACK);
            return true;
        }

        else if (field.getField(x0, y0) == constants::Tiles::BRICK0010 && field.getField(x0, y0 + 1) != constants::Tiles::METAL)
        {
            field.setField(x0, y0, constants::Tiles::BLACK);
            if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0010)
                field.setField(x0, y0 + 1, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0010 && field.getField(x0, y0) != constants::Tiles::METAL)
        {
            field.setField(x0, y0 + 1, constants::Tiles::BLACK);
            return true;
        }

        else if (field.getField(x0, y0) == constants::Tiles::BRICK0001)
        {
            field.setField(x0, y0, constants::Tiles::BLACK);
            if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0001)
                field.setField(x0, y0 + 1, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0001)
        {
            field.setField(x0, y0 + 1, constants::Tiles::BLACK);
            return true;
        }

        //0

        else if (field.getField(x0, y0) != constants::Tiles::BLACK && field.getField(x0, y0) != constants::Tiles::ICE && field.getField(x0, y0) != constants::Tiles::TREE &&
        field.getField(x0, y0) != constants::Tiles::WATER1 && field.getField(x0, y0) != constants::Tiles::WATER2 && field.getField(x0, y0) != constants::Tiles::WATER3)
        {
            return true;
        }
    }

    else if (direction == constants::Directions::RIGHT)
    {
        if (field.getField(xr, y0) == constants::Tiles::BRICK1111)
        {
            field.setField(xr, y0, constants::Tiles::BRICK0101);
            if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1111)
                field.setField(xr, y0 + 1, constants::Tiles::BRICK0101);

            return true;
        }
        else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1111)
        {
            field.setField(xr, y0 + 1, constants::Tiles::BRICK0101);
            return true;
        }

        //2

        else if (field.getField(xr, y0) == constants::Tiles::BRICK1100)
        {
            field.setField(xr, y0, constants::Tiles::BRICK0100);
            if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1100)
                field.setField(xr, y0 + 1, constants::Tiles::BRICK0100);

            return true;
        }
        else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1100)
        {
            field.setField(xr, y0 + 1, constants::Tiles::BRICK0100);
            return true;
        }

        else if (field.getField(xr, y0) == constants::Tiles::BRICK0011)
        {
            field.setField(xr, y0, constants::Tiles::BRICK0001);
            if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0011)
                field.setField(xr, y0 + 1, constants::Tiles::BRICK0001);

            return true;
        }
        else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0011)
        {
            field.setField(xr, y0 + 1, constants::Tiles::BRICK0001);
            return true;
        }

        else if (field.getField(xr, y0) == constants::Tiles::BRICK1010)
        {
            field.setField(xr, y0, constants::Tiles::BLACK);
            if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1010)
                field.setField(xr, y0 + 1, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1010)
        {
            field.setField(xr, y0 + 1, constants::Tiles::BLACK);
            return true;
        }

        else if (field.getField(xr, y0) == constants::Tiles::BRICK0101 && field.getField(xr, y0 + 1) != constants::Tiles::METAL)
        {
            field.setField(xr, y0, constants::Tiles::BLACK);
            if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0101)
                field.setField(xr, y0 + 1, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0101 && field.getField(xr, y0) != constants::Tiles::METAL)
        {
            field.setField(xr, y0 + 1, constants::Tiles::BLACK);
            return true;
        }

        //3

        else if (field.getField(xr, y0) == constants::Tiles::BRICK0111)
        {
            field.setField(xr, y0, constants::Tiles::BRICK0101);
            if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0111)
                field.setField(xr, y0 + 1, constants::Tiles::BRICK0101);

            return true;
        }
        else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0111)
        {
            field.setField(xr, y0 + 1, constants::Tiles::BRICK0101);
            return true;
        }

        else if (field.getField(xr, y0) == constants::Tiles::BRICK1011)
        {
            field.setField(xr, y0, constants::Tiles::BRICK0001);
            if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1011)
                field.setField(xr, y0 + 1, constants::Tiles::BRICK0001);

            return true;
        }
        else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1011)
        {
            field.setField(xr, y0 + 1, constants::Tiles::BRICK0001);
            return true;
        }

        else if (field.getField(xr, y0) == constants::Tiles::BRICK1101)
        {
            field.setField(xr, y0, constants::Tiles::BRICK0101);
            if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1101)
                field.setField(xr, y0 + 1, constants::Tiles::BRICK0101);

            return true;
        }
        else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1101)
        {
            field.setField(xr, y0 + 1, constants::Tiles::BRICK0101);
            return true;
        }

        else if (field.getField(xr, y0) == constants::Tiles::BRICK1110)
        {
            field.setField(xr, y0, constants::Tiles::BRICK0100);
            if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1110)
                field.setField(xr, y0 + 1, constants::Tiles::BRICK0100);

            return true;
        }
        else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1110)
        {
            field.setField(xr, y0 + 1, constants::Tiles::BRICK0100);
            return true;
        }


        //1
        else if (field.getField(xr, y0) == constants::Tiles::BRICK1000)
        {
            field.setField(xr, y0, constants::Tiles::BLACK);
            if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1000)
                field.setField(xr, y0 + 1, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1000)
        {
            field.setField(xr, y0 + 1, constants::Tiles::BLACK);
            return true;
        }

        else if (field.getField(xr, y0) == constants::Tiles::BRICK0100 && field.getField(xr, y0 + 1) != constants::Tiles::METAL)
        {
            field.setField(xr, y0, constants::Tiles::BLACK);
            if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0100)
                field.setField(xr, y0 + 1, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0100 && field.getField(xr, y0) != constants::Tiles::METAL)
        {
            field.setField(xr, y0 + 1, constants::Tiles::BLACK);
            return true;
        }

        else if (field.getField(xr, y0) == constants::Tiles::BRICK0010)
        {
            field.setField(xr, y0, constants::Tiles::BLACK);
            if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0010)
                field.setField(xr, y0 + 1, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0010)
        {
            field.setField(xr, y0 + 1, constants::Tiles::BLACK);
            return true;
        }

        else if (field.getField(xr, y0) == constants::Tiles::BRICK0001 && field.getField(xr, y0 + 1) != constants::Tiles::METAL)
        {
            field.setField(xr, y0, constants::Tiles::BLACK);
            if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0001)
                field.setField(xr, y0 + 1, constants::Tiles::BLACK);

            return true;
        }
        else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0001 && field.getField(xr, y0) != constants::Tiles::METAL)
        {
            field.setField(xr, y0 + 1, constants::Tiles::BLACK);
            return true;
        }

        //0

        else if (field.getField(xr, y0) != constants::Tiles::BLACK && field.getField(xr, y0) != constants::Tiles::ICE && field.getField(xr, y0) != constants::Tiles::TREE &&
        field.getField(xr, y0) != constants::Tiles::WATER1 && field.getField(xr, y0) != constants::Tiles::WATER2 && field.getField(xr, y0) != constants::Tiles::WATER3)
        {
            return true;
        }
    }

    return false;
}
