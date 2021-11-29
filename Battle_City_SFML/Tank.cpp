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
    return constants::tankSpeed[4 * (!isPlayer)+tankType] * 16.0  / constants::TILES_LENGHT;
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

void Tank::setBullets(std::vector<Bullet> tmpbullets) 
{
    bullets = tmpbullets;
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

std::vector<Bullet> Tank::getBullets()
{
    return bullets;
}

int Tank::getAlreadyShot()
{
    return alreadyShot;
}
void Tank::setAlreadyShot(int value)
{
    alreadyShot = value;
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
                return true;
            }
        }
    return false;
}

bool Tank::tankWithTankCollision(Tank& tank)  //fix
{
    int x = tank.getCoordX(), y = tank.getCoordY();

    if ((this->getCoordY() == y + 2 && this->getCoordX() >=  x - 1 && this->getCoordX() <= x + 1) ||
        (this->getCoordX() + 2 == x && this->getCoordY() >= y - 1 && this->getCoordY() <= y + 1) ||
        (this->getCoordY() + 2 == y && this->getCoordX() >= x - 1 && this->getCoordX() <= x + 1) ||
        (this->getCoordX() == x + 2 && this->getCoordY() >= y - 1 && this->getCoordY() <= y + 1))
        return true;
    else
        return false;
}

bool Tank::tankDeath(Tank& tank)
{
    double x0 = this->coordX, y0 = this->coordY, x1 = x0 + 2, y1 = y0 + 2, xb0, yb0, xb1, yb1;
    std::vector<Bullet> bullets = tank.getBullets();

    for (int i = 0; i < tank.getBullets().size(); ++i)
    {
        if (tank.getBullets()[i].getDirection() == constants::Directions::UP || tank.getBullets()[i].getDirection() == constants::Directions::DOWN)
        {
            if (tank.getBullets()[i].getDirection() == constants::Directions::UP)
            {
                xb0 = tank.getBullets()[i].getCoordX(); //- 1;
                yb0 = tank.getBullets()[i].getCoordY();

                xb1 = xb0 + 2;//3;
                yb1 = yb0 + 6.0 / 8;;

                if ((xb0 <= x0 && xb0 >= x0 - 1 || xb1 <= x1 && xb1 >= x0 - 1) && (yb0 <= y1 && yb1 >= y0))
                {                   
                    bullets.erase(bullets.begin() + i);
                    tank.setBullets(bullets);
                    tank.setAlreadyShot(tank.getAlreadyShot() - 1);
                    return true;
                }
            }
            else
            {
                xb0 = tank.getBullets()[i].getCoordX(); //- 1;
                yb0 = tank.getBullets()[i].getCoordY() + 6.0 / 8;

                xb1 = xb0 + 2;//3;
                yb1 = yb0 - 6.0 / 8;

                if ((xb0 <= x0 && xb0 >= x0 - 1 || xb1 <= x1 && xb1 >= x0 - 1) && (yb0 >= y0 && yb1 <= y1))
                {
                    bullets.erase(bullets.begin() + i);
                    tank.setBullets(bullets);
                    tank.setAlreadyShot(tank.getAlreadyShot() - 1);
                    return true;
                }
            }
        }
        else if (tank.getBullets()[i].getDirection() == constants::Directions::RIGHT || tank.getBullets()[i].getDirection() == constants::Directions::LEFT)
        {
            if (tank.getBullets()[i].getDirection() == constants::Directions::RIGHT)
            {
                xb0 = tank.getBullets()[i].getCoordX() + 6.0 / 8;
                yb0 = tank.getBullets()[i].getCoordY(); //- 1;

                xb1 = xb0 - 6.0 / 8;
                yb1 = yb0 + 2;//3;

                if ((yb0 <= y0 && yb0 >= y0 - 1 || yb1 <= y1 && yb1 >= y0 - 1) && (xb0 >= x0 && xb1 <= x1))
                {
                    bullets.erase(bullets.begin() + i);
                    tank.setBullets(bullets);
                    tank.setAlreadyShot(tank.getAlreadyShot() - 1);
                    return true;
                }
            }
            else
            {
                xb0 = tank.getBullets()[i].getCoordX();
                yb0 = tank.getBullets()[i].getCoordY();//- 1;

                xb1 = xb0 + 6.0 / 8;
                yb1 = yb0 + 2;// 3;

                if ((yb0 <= y0 && yb0 >= y0 - 1 || yb1 <= y1 && yb1 >= y0 - 1) && (xb0 <= x1 && xb1 >= x0))
                {
                    bullets.erase(bullets.begin() + i);
                    tank.setBullets(bullets);
                    tank.setAlreadyShot(tank.getAlreadyShot() - 1);
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
        if (this->subCoordX >= this->coordX)
            this->coordX += 0.5;
    }
    if (direction == constants::Directions::DOWN)
    {
        prevX = round(prevX);
        this->subCoordY += getTankSpeed() * constants::delay;
        this->coordX = round(subCoordX);
        this->subCoordX = this->coordX;
        if (this->subCoordY >= this->coordY)
            this->coordY += 0.5;
    }
}

void Tank::moveAIRandomly(sf::RenderWindow& window, Field& field, sf::Event& event)
{
    double prevX = this->coordX, prevY = this->coordY;
    moveAI(window, field, event);
    if (rand() % 16 == 0)
    {
        if (direction == constants::Directions::UP)
        {
        }
    }
    if (collisionWithField(field, this->coordX, this->coordY))
    {
        this->subCoordX = this->coordX = prevX;
        this->subCoordY = this->coordY = prevY;
        direction = static_cast<constants::Directions>((static_cast<int>(direction) + rand()) % 4);
    }
}

void Tank::moveAIToAlly(sf::RenderWindow& window, Field& field, sf::Event& event, Tank tank)
{
    double prevX = this->coordX, prevY = this->coordY;
    moveAI(window, field, event);
    if (collisionWithField(field, this->coordX, this->coordY))
    {
        this->subCoordX = this->coordX = prevX;
        this->subCoordY = this->coordY = prevY;
        if (tank.getCoordX() >= this->getCoordX() && tank.getCoordY() >= this->getCoordY())
        {
            if (!collisionWithField(field, this->getCoordX() + 1, this->getCoordY()) && direction != constants::Directions::LEFT)
                direction = constants::Directions::RIGHT;
            else if (!collisionWithField(field, this->getCoordX(), this->getCoordY() + 1) && direction != constants::Directions::UP)
                direction = constants::Directions::DOWN;
            else if (!collisionWithField(field, this->getCoordX(), this->getCoordY() - 1) && direction != constants::Directions::DOWN)
                direction = constants::Directions::UP;
            else 
                direction = constants::Directions::LEFT;
        }
        else if (tank.getCoordX() <= this->getCoordX() && tank.getCoordY() <= this->getCoordY())
        {
            if (!collisionWithField(field, this->getCoordX() - 1, this->getCoordY()) && direction != constants::Directions::RIGHT)
                direction = constants::Directions::LEFT;
            else if (!collisionWithField(field, this->getCoordX(), this->getCoordY() - 1) && direction != constants::Directions::DOWN)
                direction = constants::Directions::UP;
            else if (!collisionWithField(field, this->getCoordX(), this->getCoordY() + 1) && direction != constants::Directions::UP)
                direction = constants::Directions::DOWN;
            else
                direction = constants::Directions::RIGHT;
            
        }
        else if (tank.getCoordX() <= this->getCoordX() && tank.getCoordY() >= this->getCoordY())
        {
            if (!collisionWithField(field, this->getCoordX() - 1, this->getCoordY()) && direction != constants::Directions::RIGHT)
                direction = constants::Directions::LEFT;
            else if (!collisionWithField(field, this->getCoordX(), this->getCoordY() + 1) && direction != constants::Directions::UP)
                direction = constants::Directions::DOWN;
            else if (!collisionWithField(field, this->getCoordX(), this->getCoordY() - 1) && direction != constants::Directions::DOWN)
                direction = constants::Directions::UP;
            else 
                direction = constants::Directions::RIGHT;      
        }
        else if (tank.getCoordX() >= this->getCoordX() && tank.getCoordY() <= this->getCoordY())
        {
            if (!collisionWithField(field, this->getCoordX() + 1, this->getCoordY()) && direction != constants::Directions::LEFT)
                direction = constants::Directions::RIGHT;
            else if (!collisionWithField(field, this->getCoordX(), this->getCoordY() - 1) && direction != constants::Directions::DOWN)
                direction = constants::Directions::UP;
            else if (!collisionWithField(field, this->getCoordX(), this->getCoordY() + 1) && direction != constants::Directions::UP)
                direction = constants::Directions::DOWN;
            else 
                direction = constants::Directions::LEFT;
        }
    }
}
