#include "Tank.h"
#include <iostream>

Tank::Tank()
{
    alreadyShot = 0;
    isPlayer = false;
    tankType = 0;
    direction = constants::Directions::UP;
    subCoordX = coordX = constants::DEFAULT_ENEMY_COORD_X[1];
    subCoordY = coordY = constants::DEFAULT_ENEMY_COORD_Y;
}

Tank::Tank(bool isPlayer, int tankType)
{
    alreadyShot = 0;
    this->isPlayer = isPlayer;
    if (tankType < 0 || tankType > 3)
        tankType = 0;
    this->tankType = tankType;
    direction = isPlayer?constants::Directions::UP : constants::Directions::DOWN;

    if (isPlayer)
    {
        visibility = true;
        subCoordX = coordX = constants::DEFAULT_PLAYER_COORD_X[0];
        subCoordY = coordY = constants::DEFAULT_PLAYER_COORD_Y;
    }
    else
    {
        isMoving = true;
        visibility = false;
        subCoordX = coordX = constants::DEFAULT_ENEMY_COORD_X[rand() % 3];
        subCoordY = coordY = constants::DEFAULT_ENEMY_COORD_Y;
    }
}


void Tank::newTank(Tank& t, std::vector<char*> data)
{
    this->isPlayer = t.isPlayer;
    this->isMoving = t.isMoving;
    this->alreadyShot = convertBackFromCharArrayToInt(data[static_cast<int>(constants::PacketsIndexes::TankAlreadyShot)]);
    this->coordX = convertBackFromCharArrayToDouble(data[static_cast<int>(constants::PacketsIndexes::TankCoordX)]);
    this->coordY = convertBackFromCharArrayToDouble(data[static_cast<int>(constants::PacketsIndexes::TankCoordY)]);
    this->subCoordX = convertBackFromCharArrayToDouble(data[static_cast<int>(constants::PacketsIndexes::TankSubCoordY)]);
    this->subCoordY = convertBackFromCharArrayToDouble(data[static_cast<int>(constants::PacketsIndexes::TankSubCoordX)]);
    this->tankType = convertBackFromCharArrayToInt(data[static_cast<int>(constants::PacketsIndexes::TankType)]);
    this->direction = static_cast<constants::Directions>(convertBackFromCharArrayToDouble(data[static_cast<int>(constants::PacketsIndexes::TankDirecton)]));
    int numOfBullets = convertBackFromCharArrayToInt(data[static_cast<int>(constants::PacketsIndexes::TankBulletsSize)]);
       this->bullets = std::vector<Bullet>();
    
    for (int i = 8; i < 3 * numOfBullets; i+=4)
    {
       // constants::Directions dir = static_cast<constants::Directions> (convertBackFromCharArrayToInt(data[i + 2]));
        Bullet tmp(static_cast<constants::Directions> 
            (convertBackFromCharArrayToInt(data[i+ static_cast<int>(constants::PacketsIndexes::BulletDirection)])),
            convertBackFromCharArrayToDouble(data[i + static_cast<int>(constants::PacketsIndexes::BulletCoordX)]), 
            convertBackFromCharArrayToDouble(data[i+ static_cast<int>(constants::PacketsIndexes::BulletCoordY)]),
            this->tankType, this->isPlayer);
        bullets.push_back(tmp);
    }
}

double Tank::getTankSpeed()
{
    return constants::tankSpeed[4 * (isPlayer)+tankType] * 16.0  / constants::TILES_LENGHT;
}

constants::Directions Tank::getDirection()
{
    return direction;
}

int Tank::getMaxShots()
{
    return constants::maxShots[4 * (isPlayer)+tankType];
}


double Tank::getCoordX()
{
    return coordX;
}

void Tank::setCoordX(double x)
{
    coordX = x;
}

void Tank::setSubCoordX(double x)
{
    subCoordX = x;
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

bool Tank::getIsMoving()
{
    return isMoving;
}

void Tank::setVisibility(bool flag)
{
    visibility = flag;
}

bool Tank::isVisible()
{
    return visibility;
}

void Tank::draw(sf::RenderWindow& window, sf::Texture& texture_all, int animation)
{
	sf::Sprite sprite_all(texture_all);

	sprite_all.setTextureRect(sf::IntRect(
        8 * constants::BLOCK_LENGHT*(isPlayer == false) + 2 * static_cast<int>(direction) * constants::BLOCK_LENGHT + animation * constants::BLOCK_LENGHT,
        4 * constants::BLOCK_LENGHT * (isPlayer == false) + tankType * constants::BLOCK_LENGHT,
        constants::BLOCK_LENGHT, constants::BLOCK_LENGHT));
    sprite_all.setPosition(this->subCoordX * constants::TILES_LENGHT, this->subCoordY * constants::TILES_LENGHT);
    sprite_all.move(constants::WINDOW_OFFSET, constants::WINDOW_OFFSET);
	window.draw(sprite_all);
    for (int i = 0; i < bullets.size(); ++i)
    {
        bullets[i].draw(window, texture_all);
    }
}

void Tank::control(sf::RenderWindow& window, Field& field, sf::Event& event)
{
    double prevX = this->coordX, prevY = this->coordY;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->direction = constants::Directions::UP;
        this->isMoving = true;
        prevX = round(prevX);
        this->subCoordY -= getTankSpeed() * constants::delay;
        this->coordX = round(subCoordX);
        this->subCoordX = this->coordX;
        if (this->subCoordY <= this->coordY)
        {
            this->coordY -= 0.5;
        }

    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->direction = constants::Directions::DOWN;
        this->isMoving = true;
        prevX = round(prevX);
        this->subCoordY += getTankSpeed() * constants::delay;
        this->coordX = round(subCoordX);
        this->subCoordX = this->coordX;
        if (subCoordY >= coordY)
        {
            this->coordY += 0.5;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->direction = constants::Directions::LEFT;
        this->isMoving = true;
        prevY = round(prevY);
        this->subCoordX -= getTankSpeed() * constants::delay;
        this->coordY = round(subCoordY);
        this->subCoordY = this->coordY;
        if (subCoordX <= coordX)
        {
            this->coordX -= 0.5;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->direction = constants::Directions::RIGHT;
        this->isMoving = true;
        prevY = round(prevY);
        this->subCoordX += getTankSpeed() * constants::delay;
        this->coordY = round(subCoordY);
        this->subCoordY = this->coordY;
        if (subCoordX >= coordX)
        {
            this->coordX += 0.5;
        }
    }
    else
    {
        this->isMoving = false;
    }

    if (collisionWithField(field, this->coordX, this->coordY))
    {
        this->subCoordX = this->coordX = prevX;
        this->subCoordY = this->coordY = prevY;
    }
}

void Tank::bullet_shoot(sf::RenderWindow& window, sf::Event& event)
{
    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Space)
        {
            if (this->alreadyShot != this->getMaxShots())
            {
                ++this->alreadyShot;
                this->shot();
            }
        }
    }
}

void Tank::bullets_colision(Field& field)
{
    for (int i = 0; i < bullets.size(); ++i)
    {
        bullets[i].updateCoord();
        if (bullets[i].collision_bullet(field))
        {
            bullets.erase(bullets.begin() + i);
            --this->alreadyShot;
            continue;
        }
    }
}

void Tank::shot()
{
    Bullet bullet(this->getDirection(), this->getCoordX(), this->getCoordY(), this->getTankType(), this->getIsPlayer());

    bullets.push_back(bullet);
}

bool Tank::collisionWithField(Field& field, double X, double Y, int spriteSize)
{
    int x0 = X, y0 = Y, x1 = ceil(X + spriteSize), y1 = ceil(Y + spriteSize);
    for(int i = x0; i < x1; ++i)
        for (int j = y0; j < y1; ++j)
        {
            if (field.getField(i, j) != static_cast<int>(constants::Tiles::BLACK) && field.getField(i, j) != static_cast<int>(constants::Tiles::ICE) && field.getField(i, j) != static_cast<int>(constants::Tiles::TREE))
            {
                std::cout << "TRUE\n";
                return true;
            }
        }
    std::cout << "FALSE\n";
    return false;
}

bool Tank::tankWithTankCollision(Tank& tank1, Tank& tank2)  //fix
{
    int x1 = tank1.getCoordX(), y1 = tank1.getCoordY(), x2 = tank2.getCoordX(), y2 = tank2.getCoordY();

    if (y1 == y2 + 2 || x1 + 2 == x2 || y1 + 2 == y2 || x1 == x2 + 2)
        return true;
    else
        return false;
}

bool Tank::tankDeath(std::vector<Bullet>& all_bullets)
{
    double x0 = this->coordX, y0 = this->coordY, x1 = x0 + 2, y1 = x0 + 2, xb0, yb0, xb1, yb1;

    for (int i = 0; i < all_bullets.size(); ++i)
    {
        if (all_bullets[i].getDirection() == constants::Directions::UP || all_bullets[i].getDirection() == constants::Directions::DOWN)
        {
            if (all_bullets[i].getDirection() == constants::Directions::UP)
            {
                xb0 = all_bullets[i].getCoordX() - 1;
                yb0 = all_bullets[i].getCoordY();

                xb1 = xb0 + 3;
                yb1 = yb0 - 6.0 / 8;;

                if (x0 > xb0 || x1 < xb1 && yb0 < y1)
                {                   
                    return true;
                }
            }
            else
            {
                xb0 = all_bullets[i].getCoordX() - 1;
                yb0 = all_bullets[i].getCoordY() + 6.0 / 8;

                xb1 = xb0 + 3;
                yb1 = yb0 - 6.0 / 8;

                if (x0 > xb0 || x1 < xb1 && yb0 > y0)
                {
                    return true;
                }
            }
        }
        else if (all_bullets[i].getDirection() == constants::Directions::RIGHT || all_bullets[i].getDirection() == constants::Directions::LEFT)
        {
            if (all_bullets[i].getDirection() == constants::Directions::RIGHT)
            {
                xb0 = all_bullets[i].getCoordX() + 6.0 / 8;
                yb0 = all_bullets[i].getCoordY() - 1;

                xb1 = xb0 - 6.0 / 8;
                yb1 = yb0 + 3;

                if (y0 > yb0 || y1 < yb1 && xb0 > x0)
                {
                    return true;
                }
            }
            else
            {
                xb0 = all_bullets[i].getCoordX();
                yb0 = all_bullets[i].getCoordY() - 1;

                xb1 = xb0 + 6.0 / 8;
                yb1 = yb0 + 3;

                if (y0 > yb0 || y1 < yb1 && xb0 < x0)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

std::vector<char*> Tank::sendToServer()
{
    std::vector<char*> dataVector
    {   
        convertToCharArray(tankType),
        convertToCharArray(alreadyShot),
        convertToCharArray(coordX),
         convertToCharArray(subCoordX),
       convertToCharArray(subCoordY),
        convertToCharArray(static_cast<int>(direction)),
        convertToCharArray(static_cast<int>(bullets.size()))
    };
    for (int i = 0; i < bullets.size(); ++i)
    {
        dataVector.push_back(convertToCharArray(static_cast<int>(bullets[i].getDirection())));
        dataVector.push_back(convertToCharArray(bullets[i].getCoordX()));
        dataVector.push_back(convertToCharArray(bullets[i].getCoordY()));
    }
    return dataVector;
}

void Tank::moveAI(sf::RenderWindow& window, Field& field, sf::Event& event)
{
    double prevX = this->coordX, prevY = this->coordY;
    if (direction == constants::Directions::UP)
    {
        prevX = round(prevX);
        this->subCoordY -= getTankSpeed() * constants::delay;
        this->coordX = round(subCoordX);
        this->subCoordX = this->coordX;
        if (this->subCoordY <= this->coordY)
            this->coordY -= 0.5;
    }
    if (direction == constants::Directions::LEFT)
    {
        prevY = round(prevY);
        this->subCoordX -= getTankSpeed() * constants::delay;
        this->coordY = round(subCoordY);
        this->subCoordY = this->coordY;
        if (this->subCoordX <= this->coordX)
            this->coordX -= 0.5;
    }
    if (direction == constants::Directions::RIGHT)
    {
        prevY = round(prevY);
        this->subCoordX += getTankSpeed() * constants::delay;
        this->coordY = round(subCoordY);
        this->subCoordY = this->coordY;
        if (this->subCoordX <= this->coordX)
            this->coordX += 0.5;
    }
    if (direction == constants::Directions::DOWN)
    {
        prevX = round(prevX);
        this->subCoordY += getTankSpeed() * constants::delay;
        this->coordX = round(subCoordX);
        this->subCoordX = this->coordX;
        if (this->subCoordY <= this->coordY)
            this->coordY += 0.5;
    }
    if (collisionWithField(field, this->coordX, this->coordY))
    {
        this->subCoordX = this->coordX = prevX;
        this->subCoordY = this->coordY = prevY;
        direction = static_cast<constants::Directions>((static_cast<int>(direction) + 1) % 4);
    }
}

