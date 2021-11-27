#include "Tank.h"

Tank::Tank()
{
    alreadyShot = 0;
    maxShots = 1;
    isPlayer = false;
    tankType = 0;
    direction = constants::Directions::UP;
    coordX = constants::DEFAULT_ENEMY_COORD_X[1];
    coordY = constants::DEFAULT_ENEMY_COORD_Y;
}

Tank::Tank(bool isPlayer, int tankType)
{
    alreadyShot = 0;
    maxShots = 1;
    this->isPlayer = isPlayer;
    if (tankType < 0 || tankType > 3)
        tankType = 0;
    this->tankType = tankType;
    direction = isPlayer?constants::Directions::UP : constants::Directions::DOWN;

    if (isPlayer)
    {
        coordX = constants::DEFAULT_PLAYER_COORD_X[0];
        coordY = constants::DEFAULT_PLAYER_COORD_Y;
    }
    else
    {
        coordX = constants::DEFAULT_ENEMY_COORD_X[1];
        coordY = constants::DEFAULT_ENEMY_COORD_Y;
    }
}

double Tank::getTankSpeed()
{
    {
        if (isPlayer)
            return constants::tankSpeed[tankType] * 16.0;
        else
            return constants::tankSpeed[4 + tankType] * 16.0;
    }
}

constants::Directions Tank::getDirection()
{
    return direction;
}

double Tank::getCoordX()
{
    return coordX;
}

double Tank::getCoordY()
{
    return coordY;
}

int Tank::getTankType()
{
    return tankType;
}

bool Tank::getIsPlayer()
{
    return isPlayer;
}

void Tank::draw(sf::RenderWindow& window)
{
	sf::Texture texture_all;
	texture_all.loadFromFile("allSprites.png");
	sf::Sprite sprite_all(texture_all);

	sprite_all.setTextureRect(sf::IntRect(
        8 * constants::BLOCK_LENGHT*(isPlayer == false) + 2 * static_cast<int>(direction) * constants::BLOCK_LENGHT,
        4 * constants::BLOCK_LENGHT * (isPlayer == false) + tankType * constants::BLOCK_LENGHT,
        constants::BLOCK_LENGHT, constants::BLOCK_LENGHT));
    sprite_all.setPosition(this->coordX * constants::TILES_LENGHT, this->coordY * constants::TILES_LENGHT);
    sprite_all.move(constants::WINDOW_OFFSET, constants::WINDOW_OFFSET);
	window.draw(sprite_all);
}

void Tank::control(sf::RenderWindow& window, Field& field, sf::Event& event, std::vector<Bullet>& bullets)
{
    double prevX = this->coordX, prevY = this->coordY;
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::W)
        {
            this->direction = constants::Directions::UP;
            this->coordY-=(this->getTankSpeed()*constants::delay);
        }
        else if (event.key.code == sf::Keyboard::S)
        {            
            this->direction = constants::Directions::DOWN;
            this->coordY+= (this->getTankSpeed() * constants::delay);
        }
        else if (event.key.code == sf::Keyboard::A)
        {            
            this->direction = constants::Directions::LEFT;
            this->coordX-= (this->getTankSpeed() * constants::delay);
        }
        else if (event.key.code == sf::Keyboard::D)
        {
            this->direction = constants::Directions::RIGHT;
            this->coordX+= (this->getTankSpeed() * constants::delay);
        }
        else if (event.key.code == sf::Keyboard::Space)
        {
            if (this->alreadyShot != this->maxShots)
            {
                //++this->alreadyShot;
                this->shot(window, bullets);
            }
        }
    }
    if (collision_tank(field, this->coordX, this->coordY))
    {
        this->coordX = prevX;
        this->coordY = prevY;
    }
}

void Tank::shot(sf::RenderWindow& window, std::vector<Bullet>& bullets)
{
    Bullet bullet(this->getDirection(), this->getCoordX(), this->getCoordY(), this->getTankType(), this->getIsPlayer());

    bullets.push_back(bullet);
}

bool Tank::collision_tank(Field& field, double X, double Y)
{
    int x0 = floor(X), y0 = floor(Y), x1 = ceil(X + 2), y1 = ceil(Y + 2);
    for(int i = x0; i < x1; ++i)
        for (int j = y0; j < y1; ++j)
        {
            if (field.getField(i, j) != static_cast<int>(constants::Tiles::BLACK) && field.getField(i, j) != static_cast<int>(constants::Tiles::ICE) && field.getField(i, j) != static_cast<int>(constants::Tiles::TREE))
                return true;
        }
    return false;
}

void Tank::collision_bullet(Field& field, std::vector<Bullet>& bullets)
{
    int x0, y0, xr, yd;
    constants::Directions direction;
     for (int i = 0; i < bullets.size(); ++i)
    {
        x0 = floor(bullets[i].getCoordX());
        y0 = floor(bullets[i].getCoordY());
        xr = floor(bullets[i].getCoordX() + 5.0 / 8) + 2;//+ 6.0 / 8);
        yd = floor(bullets[i].getCoordY() + 3.0 / 8) + 2;//+ 6.0 / 8);
        direction = bullets[i].getDirection();
  
        //if(bullets[i].getCoordX() < 2.625 || bullets[i].getCoordX() > 25.375 || bullets[i].getCoordY() < 2.575 || bullets[i].getCoordY() > 27.325)
        //    bullets.erase(bullets.begin() + i);

        if (direction == constants::Directions::UP)
        {
            if (field.getField(x0, y0) == constants::Tiles::BRICK1111)
            {
                field.setField(x0, y0, constants::Tiles::BRICK1100);
                if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1111)
                    field.setField(x0 + 1, y0, constants::Tiles::BRICK1100);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1111)
            {
                field.setField(x0 + 1, y0, constants::Tiles::BRICK1100);
                bullets.erase(bullets.begin() + i);
            }

            //2

            else if (field.getField(x0, y0) == constants::Tiles::BRICK1100)
            {
                field.setField(x0, y0, constants::Tiles::BLACK);
                if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1100)
                    field.setField(x0 + 1, y0, constants::Tiles::BLACK);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1100)
            {
                field.setField(x0 + 1, y0, constants::Tiles::BLACK);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, y0) == constants::Tiles::BRICK0011)
            {
                field.setField(x0, y0, constants::Tiles::BLACK);
                if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0011)
                    field.setField(x0 + 1, y0, constants::Tiles::BLACK);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0011)
            {
                field.setField(x0 + 1, y0, constants::Tiles::BLACK);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, y0) == constants::Tiles::BRICK1010)
            {
                field.setField(x0, y0, constants::Tiles::BRICK1000);
                if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1010)
                    field.setField(x0 + 1, y0, constants::Tiles::BRICK1000);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1010)
            {
                field.setField(x0 + 1, y0, constants::Tiles::BRICK1000);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, y0) == constants::Tiles::BRICK0101)
            {
                field.setField(x0, y0, constants::Tiles::BRICK0100);
                if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0101)
                    field.setField(x0 + 1, y0, constants::Tiles::BRICK0100);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0101)
            {
                field.setField(x0 + 1, y0, constants::Tiles::BRICK0100);
                bullets.erase(bullets.begin() + i);
            }

            //3

            else if (field.getField(x0, y0) == constants::Tiles::BRICK0111)
            {
                field.setField(x0, y0, constants::Tiles::BRICK0100);
                if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0111)
                    field.setField(x0 + 1, y0, constants::Tiles::BRICK0100);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0111)
            {
                field.setField(x0 + 1, y0, constants::Tiles::BRICK0100);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, y0) == constants::Tiles::BRICK1011)
            {
                field.setField(x0, y0, constants::Tiles::BRICK1000);
                if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1011)
                    field.setField(x0 + 1, y0, constants::Tiles::BRICK1000);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1011)
            {
                field.setField(x0 + 1, y0, constants::Tiles::BRICK1000);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, y0) == constants::Tiles::BRICK1101)
            {
                field.setField(x0, y0, constants::Tiles::BRICK1100);
                if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1101)
                    field.setField(x0 + 1, y0, constants::Tiles::BRICK1100);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1101)
            {
                field.setField(x0 + 1, y0, constants::Tiles::BRICK1100);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, y0) == constants::Tiles::BRICK1110)
            {
            field.setField(x0, y0, constants::Tiles::BRICK1100);
            if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1110)
                field.setField(x0 + 1, y0, constants::Tiles::BRICK1100);

            bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1110)
            {
            field.setField(x0 + 1, y0, constants::Tiles::BRICK1100);
            bullets.erase(bullets.begin() + i);
            }


            //1
            else if (field.getField(x0, y0) == constants::Tiles::BRICK1000)
            {
            field.setField(x0, y0, constants::Tiles::BLACK);
            if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1000)
                field.setField(x0 + 1, y0, constants::Tiles::BLACK);

            bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK1000)
            {
            field.setField(x0 + 1, y0, constants::Tiles::BLACK);
            bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, y0) == constants::Tiles::BRICK0100)
            {
            field.setField(x0, y0, constants::Tiles::BLACK);
            if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0100)
                field.setField(x0 + 1, y0, constants::Tiles::BLACK);

            bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0100)
            {
            field.setField(x0 + 1, y0, constants::Tiles::BLACK);
            bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, y0) == constants::Tiles::BRICK0010)
            {
            field.setField(x0, y0, constants::Tiles::BLACK);
            if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0010)
                field.setField(x0 + 1, y0, constants::Tiles::BLACK);

            bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0010)
            {
            field.setField(x0 + 1, y0, constants::Tiles::BLACK);
            bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, y0) == constants::Tiles::BRICK0001)
            {
            field.setField(x0, y0, constants::Tiles::BLACK);
            if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0001)
                field.setField(x0 + 1, y0, constants::Tiles::BLACK);

            bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, y0) == constants::Tiles::BRICK0001)
            {
            field.setField(x0 + 1, y0, constants::Tiles::BLACK);
            bullets.erase(bullets.begin() + i);
            }
        }

        else if (direction == constants::Directions::DOWN)
        {
            if (field.getField(x0, yd) == constants::Tiles::BRICK1111)
            {
                field.setField(x0, yd, constants::Tiles::BRICK0011);
                if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1111)
                    field.setField(x0 + 1, yd, constants::Tiles::BRICK0011);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1111)
            {
                field.setField(x0 + 1, yd, constants::Tiles::BRICK0011);
                bullets.erase(bullets.begin() + i);
            }

            //2

            else if (field.getField(x0, yd) == constants::Tiles::BRICK1100)
            {
                field.setField(x0, yd, constants::Tiles::BLACK);
                if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1100)
                    field.setField(x0 + 1, yd, constants::Tiles::BLACK);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1100)
            {
                field.setField(x0 + 1, yd, constants::Tiles::BLACK);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, yd) == constants::Tiles::BRICK0011)
            {
                field.setField(x0, yd, constants::Tiles::BLACK);
                if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0011)
                    field.setField(x0 + 1, yd, constants::Tiles::BLACK);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0011)
            {
                field.setField(x0 + 1, yd, constants::Tiles::BLACK);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, yd) == constants::Tiles::BRICK1010)
            {
                field.setField(x0, yd, constants::Tiles::BRICK0010);
                if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1010)
                    field.setField(x0 + 1, yd, constants::Tiles::BRICK0010);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1010)
            {
                field.setField(x0 + 1, yd, constants::Tiles::BRICK0010);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, yd) == constants::Tiles::BRICK0101)
            {
                field.setField(x0, yd, constants::Tiles::BRICK0001);
                if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0101)
                    field.setField(x0 + 1, yd, constants::Tiles::BRICK0001);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0101)
            {
                field.setField(x0 + 1, yd, constants::Tiles::BRICK0001);
                bullets.erase(bullets.begin() + i);
            }

            //3

            else if (field.getField(x0, yd) == constants::Tiles::BRICK0111)
            {
                field.setField(x0, yd, constants::Tiles::BRICK0011);
                if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0111)
                    field.setField(x0 + 1, yd, constants::Tiles::BRICK0011);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0111)
            {
                field.setField(x0 + 1, yd, constants::Tiles::BRICK0011);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, yd) == constants::Tiles::BRICK1011)
            {
                field.setField(x0, yd, constants::Tiles::BRICK0011);
                if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1011)
                    field.setField(x0 + 1, yd, constants::Tiles::BRICK0011);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1011)
            {
                field.setField(x0 + 1, yd, constants::Tiles::BRICK0011);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, yd) == constants::Tiles::BRICK1101)
            {
                field.setField(x0, yd, constants::Tiles::BRICK0001);
                if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1101)
                    field.setField(x0 + 1, yd, constants::Tiles::BRICK0001);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1101)
            {
                field.setField(x0 + 1, yd, constants::Tiles::BRICK0001);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, yd) == constants::Tiles::BRICK1110)
            {
                field.setField(x0, yd, constants::Tiles::BRICK0010);
                if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1110)
                    field.setField(x0 + 1, yd, constants::Tiles::BRICK0010);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1110)
            {
                field.setField(x0 + 1, yd, constants::Tiles::BRICK0010);
                bullets.erase(bullets.begin() + i);
            }


            //1
            else if (field.getField(x0, yd) == constants::Tiles::BRICK1000)
            {
                field.setField(x0, yd, constants::Tiles::BLACK);
                if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1000)
                    field.setField(x0 + 1, yd, constants::Tiles::BLACK);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK1000)
            {
                field.setField(x0 + 1, yd, constants::Tiles::BLACK);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, yd) == constants::Tiles::BRICK0100)
            {
                field.setField(x0, yd, constants::Tiles::BLACK);
                if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0100)
                    field.setField(x0 + 1, yd, constants::Tiles::BLACK);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0100)
            {
                field.setField(x0 + 1, yd, constants::Tiles::BLACK);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, yd) == constants::Tiles::BRICK0010)
            {
                field.setField(x0, yd, constants::Tiles::BLACK);
                if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0010)
                    field.setField(x0 + 1, yd, constants::Tiles::BLACK);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0010)
            {
                field.setField(x0 + 1, yd, constants::Tiles::BLACK);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, yd) == constants::Tiles::BRICK0001)
            {
                field.setField(x0, yd, constants::Tiles::BLACK);
                if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0001)
                    field.setField(x0 + 1, yd, constants::Tiles::BLACK);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0 + 1, yd) == constants::Tiles::BRICK0001)
            {
                field.setField(x0 + 1, yd, constants::Tiles::BLACK);
                bullets.erase(bullets.begin() + i);
            }
        }

        else if (direction == constants::Directions::LEFT)
        {
            if (field.getField(x0, y0) == constants::Tiles::BRICK1111)
            {
                field.setField(x0, y0, constants::Tiles::BRICK1010);
                if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1111)
                    field.setField(x0, y0 + 1, constants::Tiles::BRICK1010);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1111)
            {
                field.setField(x0, y0 + 1, constants::Tiles::BRICK1010);
                bullets.erase(bullets.begin() + i);
            }

            //2

            else if (field.getField(x0, y0) == constants::Tiles::BRICK1100)
            {
                field.setField(x0, y0, constants::Tiles::BRICK1000);
                if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1100)
                    field.setField(x0, y0 + 1, constants::Tiles::BRICK1000);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1100)
            {
                field.setField(x0, y0 + 1, constants::Tiles::BRICK1000);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, y0) == constants::Tiles::BRICK0011)
            {
                field.setField(x0, y0, constants::Tiles::BRICK0010);
                if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0011)
                    field.setField(x0, y0 + 1, constants::Tiles::BRICK0010);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0011)
            {
                field.setField(x0, y0 + 1, constants::Tiles::BRICK0010);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, y0) == constants::Tiles::BRICK1010)
            {
                field.setField(x0, y0, constants::Tiles::BLACK);
                if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1010)
                    field.setField(x0, y0 + 1, constants::Tiles::BLACK);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1010)
            {
                field.setField(x0, y0 + 1, constants::Tiles::BLACK);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, y0) == constants::Tiles::BRICK0101)
            {
                field.setField(x0, y0, constants::Tiles::BLACK);
                if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0101)
                    field.setField(x0, y0 + 1, constants::Tiles::BLACK);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0101)
            {
                field.setField(x0, y0 + 1, constants::Tiles::BLACK);
                bullets.erase(bullets.begin() + i);
            }

            //3

            else if (field.getField(x0, y0) == constants::Tiles::BRICK0111)
            {
                field.setField(x0, y0, constants::Tiles::BRICK0010);
                if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0111)
                    field.setField(x0, y0 + 1, constants::Tiles::BRICK0010);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0111)
            {
                field.setField(x0, y0 + 1, constants::Tiles::BRICK0010);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, y0) == constants::Tiles::BRICK1011)
            {
                field.setField(x0, y0, constants::Tiles::BRICK1010);
                if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1011)
                    field.setField(x0, y0 + 1, constants::Tiles::BRICK1010);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1011)
            {
                field.setField(x0, y0 + 1, constants::Tiles::BRICK1010);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, y0) == constants::Tiles::BRICK1101)
            {
                field.setField(x0, y0, constants::Tiles::BRICK1000);
                if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1101)
                    field.setField(x0, y0 + 1, constants::Tiles::BRICK1000);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1101)
            {
                field.setField(x0, y0 + 1, constants::Tiles::BRICK1000);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, y0) == constants::Tiles::BRICK1110)
            {
                field.setField(x0, y0, constants::Tiles::BRICK1000);
                if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1110)
                    field.setField(x0, y0 + 1, constants::Tiles::BRICK1000);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1110)
            {
                field.setField(x0, y0 + 1, constants::Tiles::BRICK1000);
                bullets.erase(bullets.begin() + i);
            }


            //1
            else if (field.getField(x0, y0) == constants::Tiles::BRICK1000)
            {
                field.setField(x0, y0, constants::Tiles::BLACK);
                if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1000)
                    field.setField(x0, y0 + 1, constants::Tiles::BLACK);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK1000)
            {
                field.setField(x0, y0 + 1, constants::Tiles::BLACK);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, y0) == constants::Tiles::BRICK0100)
            {
                field.setField(x0, y0, constants::Tiles::BLACK);
                if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0100)
                    field.setField(x0, y0 + 1, constants::Tiles::BLACK);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0100)
            {
                field.setField(x0, y0 + 1, constants::Tiles::BLACK);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, y0) == constants::Tiles::BRICK0010)
            {
                field.setField(x0, y0, constants::Tiles::BLACK);
                if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0010)
                    field.setField(x0, y0 + 1, constants::Tiles::BLACK);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0010)
            {
                field.setField(x0, y0 + 1, constants::Tiles::BLACK);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(x0, y0) == constants::Tiles::BRICK0001)
            {
                field.setField(x0, y0, constants::Tiles::BLACK);
                if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0001)
                    field.setField(x0, y0 + 1, constants::Tiles::BLACK);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(x0, y0 + 1) == constants::Tiles::BRICK0001)
            {
                field.setField(x0, y0 + 1, constants::Tiles::BLACK);
                bullets.erase(bullets.begin() + i);
            }
        }

        else if (direction == constants::Directions::RIGHT)
        {
            if (field.getField(xr, y0) == constants::Tiles::BRICK1111)
            {
                field.setField(xr, y0, constants::Tiles::BRICK0101);
                if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1111)
                    field.setField(xr, y0 + 1, constants::Tiles::BRICK0101);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1111)
            {
                field.setField(xr, y0 + 1, constants::Tiles::BRICK0101);
                bullets.erase(bullets.begin() + i);
            }

            //2

            else if (field.getField(xr, y0) == constants::Tiles::BRICK1100)
            {
                field.setField(xr, y0, constants::Tiles::BRICK0100);
                if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1100)
                    field.setField(xr, y0 + 1, constants::Tiles::BRICK0100);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1100)
            {
                field.setField(xr, y0 + 1, constants::Tiles::BRICK0100);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(xr, y0) == constants::Tiles::BRICK0011)
            {
                field.setField(xr, y0, constants::Tiles::BRICK0001);
                if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0011)
                    field.setField(xr, y0 + 1, constants::Tiles::BRICK0001);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0011)
            {
                field.setField(xr, y0 + 1, constants::Tiles::BRICK0001);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(xr, y0) == constants::Tiles::BRICK1010)
            {
                field.setField(xr, y0, constants::Tiles::BLACK);
                if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1010)
                    field.setField(xr, y0 + 1, constants::Tiles::BLACK);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1010)
            {
                field.setField(xr, y0 + 1, constants::Tiles::BLACK);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(xr, y0) == constants::Tiles::BRICK0101)
            {
                field.setField(xr, y0, constants::Tiles::BLACK);
                if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0101)
                    field.setField(xr, y0 + 1, constants::Tiles::BLACK);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0101)
            {
                field.setField(xr, y0 + 1, constants::Tiles::BLACK);
                bullets.erase(bullets.begin() + i);
            }

            //3

            else if (field.getField(xr, y0) == constants::Tiles::BRICK0111)
            {
                field.setField(xr, y0, constants::Tiles::BRICK0101);
                if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0111)
                    field.setField(xr, y0 + 1, constants::Tiles::BRICK0101);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0111)
            {
                field.setField(xr, y0 + 1, constants::Tiles::BRICK0101);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(xr, y0) == constants::Tiles::BRICK1011)
            {
                field.setField(xr, y0, constants::Tiles::BRICK0001);
                if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1011)
                    field.setField(xr, y0 + 1, constants::Tiles::BRICK0001);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1011)
            {
                field.setField(xr, y0 + 1, constants::Tiles::BRICK0001);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(xr, y0) == constants::Tiles::BRICK1101)
            {
                field.setField(xr, y0, constants::Tiles::BRICK0101);
                if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1101)
                    field.setField(xr, y0 + 1, constants::Tiles::BRICK0101);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1101)
            {
                field.setField(xr, y0 + 1, constants::Tiles::BRICK0101);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(xr, y0) == constants::Tiles::BRICK1110)
            {
                field.setField(xr, y0, constants::Tiles::BRICK0100);
                if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1110)
                    field.setField(xr, y0 + 1, constants::Tiles::BRICK0100);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1110)
            {
                field.setField(xr, y0 + 1, constants::Tiles::BRICK0100);
                bullets.erase(bullets.begin() + i);
            }


            //1
            else if (field.getField(xr, y0) == constants::Tiles::BRICK1000)
            {
                field.setField(xr, y0, constants::Tiles::BLACK);
                if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1000)
                    field.setField(xr, y0 + 1, constants::Tiles::BLACK);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK1000)
            {
                field.setField(xr, y0 + 1, constants::Tiles::BLACK);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(xr, y0) == constants::Tiles::BRICK0100)
            {
                field.setField(xr, y0, constants::Tiles::BLACK);
                if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0100)
                    field.setField(xr, y0 + 1, constants::Tiles::BLACK);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0100)
            {
                field.setField(xr, y0 + 1, constants::Tiles::BLACK);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(xr, y0) == constants::Tiles::BRICK0010)
            {
                field.setField(xr, y0, constants::Tiles::BLACK);
                if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0010)
                    field.setField(xr, y0 + 1, constants::Tiles::BLACK);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0010)
            {
                field.setField(xr, y0 + 1, constants::Tiles::BLACK);
                bullets.erase(bullets.begin() + i);
            }

            else if (field.getField(xr, y0) == constants::Tiles::BRICK0001)
            {
                field.setField(xr, y0, constants::Tiles::BLACK);
                if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0001)
                    field.setField(xr, y0 + 1, constants::Tiles::BLACK);

                bullets.erase(bullets.begin() + i);
            }
            else if (field.getField(xr, y0 + 1) == constants::Tiles::BRICK0001)
            {
                field.setField(xr, y0 + 1, constants::Tiles::BLACK);
                bullets.erase(bullets.begin() + i);
            }
        }
    }
}