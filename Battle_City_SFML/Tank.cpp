#include "Tank.h"
#include <iostream>

char* convertFromStringToCharArray(std::string data)
{
    char* ans = new char[data.size()];
    for (int i = 0; i < data.size(); ++i)
    {
        ans[i] = data[i];
    }
    return ans;
}

Tank::Tank()
{
    alreadyShot = 0;
    isPlayer = false;
    tankType = 0;
    direction = constants::Directions::UP;
    prX = subCoordX = coordX = constants::DEFAULT_ENEMY_COORD_X[1];
    prY = subCoordY = coordY = constants::DEFAULT_ENEMY_COORD_Y;
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
        prX = subCoordX = coordX = constants::DEFAULT_PLAYER_COORD_X[0];
        prY = subCoordY = coordY = constants::DEFAULT_PLAYER_COORD_Y;
    }
    else
    {
        isMoving = true;
        visibility = false;
        prX = subCoordX = coordX = constants::DEFAULT_ENEMY_COORD_X[rand() % 3];
        prY = subCoordY = coordY = constants::DEFAULT_ENEMY_COORD_Y;
    }
}

void Tank::newTank(std::vector<std::string> data)
{
    
    this->alreadyShot = static_cast<int>(convertBackFromCharArrayToDouble(convertFromStringToCharArray(data[static_cast<int>(constants::PacketsIndexes::TankAlreadyShot)])));
    this->coordX = convertBackFromCharArrayToDouble(convertFromStringToCharArray(data[static_cast<int>(constants::PacketsIndexes::TankCoordX)]));
    this->coordY = convertBackFromCharArrayToDouble(convertFromStringToCharArray(data[static_cast<int>(constants::PacketsIndexes::TankCoordY)]));
    this->subCoordX = convertBackFromCharArrayToDouble(convertFromStringToCharArray(data[static_cast<int>(constants::PacketsIndexes::TankSubCoordY)]));
    this->subCoordY = convertBackFromCharArrayToDouble(convertFromStringToCharArray(data[static_cast<int>(constants::PacketsIndexes::TankSubCoordX)]));
    this->tankType = static_cast<int>(convertBackFromCharArrayToDouble(convertFromStringToCharArray(data[static_cast<int>(constants::PacketsIndexes::TankType)])));
    this->direction = static_cast<constants::Directions>(static_cast<int>(
        convertBackFromCharArrayToDouble(convertFromStringToCharArray(data[static_cast<int>(constants::PacketsIndexes::TankDirecton)]))));
    int numOfBullets = static_cast<int>(convertBackFromCharArrayToDouble(convertFromStringToCharArray(data[static_cast<int>(constants::PacketsIndexes::TankBulletsSize)])));
    this->bullets = std::vector<Bullet>();

    this->visibility = static_cast<bool>(convertBackFromCharArrayToDouble(convertFromStringToCharArray(data[static_cast<int>(constants::PacketsIndexes::Visibility)])));
    this->isPlayer = static_cast<bool>(convertBackFromCharArrayToDouble(convertFromStringToCharArray(data[static_cast<int>(constants::PacketsIndexes::isPlayer)])));
    this->isMoving = static_cast<bool>(convertBackFromCharArrayToDouble(convertFromStringToCharArray(data[static_cast<int>(constants::PacketsIndexes::isMoving)])));
    this->anim = static_cast<bool>(convertBackFromCharArrayToDouble(convertFromStringToCharArray(data[static_cast<int>(constants::PacketsIndexes::anim)])));
    this-> prX = convertBackFromCharArrayToDouble(convertFromStringToCharArray(data[static_cast<int>(constants::PacketsIndexes::prX)]));
    this->prY = convertBackFromCharArrayToDouble(convertFromStringToCharArray(data[static_cast<int>(constants::PacketsIndexes::prY)]));
 

    for (int i = static_cast<int>(constants::PacketsIndexes::prY) + 1; i < static_cast<int>(constants::PacketsIndexes::prY) + 3 * numOfBullets; i += 3)
    {
        // constants::Directions dir = static_cast<constants::Directions> (convertBackFromCharArrayToInt(data[i + 2]));
        Bullet tmp(
            static_cast<constants::Directions>(static_cast<int>
            (convertBackFromCharArrayToDouble(convertFromStringToCharArray(data[i + static_cast<int>(constants::PacketsIndexes::BulletDirection)])))),
            convertBackFromCharArrayToDouble(convertFromStringToCharArray(data[i + static_cast<int>(constants::PacketsIndexes::BulletCoordX)])),
            convertBackFromCharArrayToDouble(convertFromStringToCharArray(data[i + static_cast<int>(constants::PacketsIndexes::BulletCoordY)])),
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

double Tank::getPrX()
{
    return prX;
}

double Tank::getPrY()
{
    return prY;
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

void Tank::setDirection(constants::Directions dir)
{
    direction = dir;
}

void Tank::setCoordY(double x)
{
    coordY = x;
}

void Tank::setSubCoordY(double x)
{
    subCoordY = x;
}

void Tank::draw(sf::RenderWindow& window, sf::Texture& texture_all)
{
	sf::Sprite sprite_all(texture_all);

	sprite_all.setTextureRect(sf::IntRect(
        8 * constants::BLOCK_LENGHT*(isPlayer == false) + 2 * static_cast<int>(direction) * constants::BLOCK_LENGHT + this->anim * constants::BLOCK_LENGHT,
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

void Tank::control(sf::RenderWindow& window, Field& field, sf::Event& event, std::vector<Tank>& tankAI)
{
    double prevX = this->coordX, prevY = this->coordY;
    this->prX = this->coordX;
    this->prY = this->coordY;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->direction = constants::Directions::UP;
        this->isMoving = true;
        prevX = round(prevX);
        prX = round(prX);
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
        prX = round(prX);
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
        prY = round(prY);
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
        prY = round(prY);
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

    int i = tankWithTankCollision(tankAI);
    if (i != -1)
    {
        if (isMoving)
        { 
            if(static_cast<int>(this->direction) == (static_cast<int>(tankAI[i].getDirection()) + 2) % 4)
                tankAI[i].setDirection(static_cast<constants::Directions>((static_cast<int>(tankAI[i].getDirection()) + 2) % 4));
        }
        else
            tankAI[i].setDirection(static_cast<constants::Directions>((static_cast<int>(tankAI[i].getDirection()) + 2) % 4));

        tankAI[i].setCoordX(tankAI[i].getPrX());
        tankAI[i].setCoordY(tankAI[i].getPrY());
        tankAI[i].setSubCoordX(tankAI[i].getPrX());
        tankAI[i].setSubCoordY(tankAI[i].getPrY());

        this->subCoordX = this->coordX = prevX;
        this->subCoordY = this->coordY = prevY;
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

bool Tank::collisionWithField(Field& field, double X, double Y)
{
    int x0 = X, y0 = Y, x1 = ceil(X + 2), y1 = ceil(Y + 2);
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

int Tank::tankWithTankCollision(std::vector<Tank>& tanks)
{
    double xenemy, yenemy, x, y;
    for (int i = 0; i < tanks.size(); ++i)
    {
        if (!tanks[i].isVisible())
            continue;

        xenemy = tanks[i].getCoordX();
        yenemy = tanks[i].getCoordY();

        x = this->getCoordX();
        y = this->getCoordY();

        if (x == xenemy && y == yenemy)
            continue;

        /*if (((this->getCoordY() == y + 2 || this->getCoordY() == y + 1) && this->getCoordX() >= x - 1 && this->getCoordX() <= x + 1) ||
            ((this->getCoordX() + 2 == x || this->getCoordX() + 1 == x) && this->getCoordY() >= y - 1 && this->getCoordY() <= y + 1) ||
            ((this->getCoordY() + 2 == y || this->getCoordY() + 1 == y) && this->getCoordX() >= x - 1 && this->getCoordX() <= x + 1) ||
            ((this->getCoordX() == x + 2 || this->getCoordX() == x + 1) && this->getCoordY() >= y - 1 && this->getCoordY() <= y + 1))
                return i;*/

        if ((this->direction == constants::Directions::UP || this->direction == constants::Directions::DOWN) && 
            xenemy >= x - 1 && xenemy <= x + 1 && yenemy >= y - 2 && yenemy <= y + 2)
            return i;
        else if ((this->direction == constants::Directions::RIGHT || this->direction == constants::Directions::LEFT) && 
            xenemy >= x - 2 && xenemy <= x + 2 && yenemy >= y - 1 && yenemy <= y + 1)
            return i;
    }
        
    return -1;
}

bool Tank::tankDeath(Tank& tank)
{
    double x0 = this->coordX, y0 = this->coordY, xb0, yb0;// , x1 = x0 + 2, y1 = y0 + 2, xb0, yb0, xb1, yb1;
    std::vector<Bullet> bullets = tank.getBullets();
    for (int i = 0; i < tank.getBullets().size(); ++i)
    {
        if (tank.getBullets()[i].getDirection() == constants::Directions::UP || tank.getBullets()[i].getDirection() == constants::Directions::DOWN)
        {
            if (tank.getBullets()[i].getDirection() == constants::Directions::UP)
            {
                xb0 = tank.getBullets()[i].getCoordX(); //- 1;
                yb0 = tank.getBullets()[i].getCoordY();
                //xb1 = xb0 + 2;//3;
                //yb1 = yb0 + 6.0 / 8;;

                //if ((xb0 <= x0 && xb0 >= x0 - 1 || xb1 <= x1 + 0.1 && xb1 >= x1 - 0.1) && (yb0 <= y1 && yb1 >= y0)) //&& xb1 >= x0 + 1) && (yb0 <= y1 && yb1 >= y0))
                //    if ((xb0 <= x0 && xb0 >= x0 - 1 || xb1 == x1) && (yb0 <= y1 && yb1 >= y0)) //&& xb1 >= x0 + 1) && (yb0 <= y1 && yb1 >= y0))
                    if(xb0 >= x0 - 1 && xb0 <= x0 + 1 && yb0 >= y0 - 2 && yb0 <= y0 + 6.0 / 8)
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
                yb0 = tank.getBullets()[i].getCoordY();// +6.0 / 8;
                //xb1 = xb0 + 2;//3;
                //yb1 = yb0 - 6.0 / 8;

                //if ((xb0 <= x0 && xb0 >= x0 - 1 || xb1 <= x1 && xb1 >= x0 - 1) && (yb0 >= y0 && yb1 <= y1))
                    //if ((xb0 <= x0 && xb0 >= x0 - 1 || xb1 == x1) && (yb0 >= y0 && yb1 <= y1))
                    if (xb0 >= x0 - 1 && xb0 <= x0 + 1 && yb0 >= y0 - 6.0 / 8 && yb0 <= y0 + 2)
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
                xb0 = tank.getBullets()[i].getCoordX();// +6.0 / 8;
                yb0 = tank.getBullets()[i].getCoordY(); //- 1;
                //xb1 = xb0 - 6.0 / 8;
                //yb1 = yb0 + 2;//3;

                //if ((yb0 <= y0 && yb0 >= y0 - 1 || yb1 <= y1 && yb1 >= y0 - 1) && (xb0 >= x0 && xb1 <= x1))
                    //if ((yb0 <= y0 && yb0 >= y0 - 1 || yb1 == y1) && (xb0 >= x0 && xb1 <= x1))
                    if (xb0 >= x0 - 6.0 / 8 && xb0 <= x0 + 2 && yb0 >= y0 - 1 && yb0 <= y0 + 1)
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
                //xb1 = xb0 + 6.0 / 8;
                //yb1 = yb0 + 2;// 3;

                //if ((yb0 <= y0 && yb0 >= y0 - 1 || yb1 <= y1 + 0.1 && yb1 >= y1 - 0.1) && (xb0 <= x1 && xb1 >= x0)) //&& yb1 >= y0 - 1) && (xb0 <= x1 && xb1 >= x0))
                    //if ((yb0 <= y0 && yb0 >= y0 - 1 || yb1 == y1) && (xb0 <= x1 && xb1 >= x0)) //&& yb1 >= y0 - 1) && (xb0 <= x1 && xb1 >= x0))
                    if (xb0 >= x0 && xb0 <= x0 + 2 && yb0 >= y0 - 1 && yb0 <= y0 + 1)
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
        convertToCharArray(static_cast<double>(tankType)),
        convertToCharArray(static_cast<double>(alreadyShot)),
        convertToCharArray((coordX)),
        convertToCharArray((coordY)),
        convertToCharArray(subCoordX),

        convertToCharArray(subCoordY),
        convertToCharArray(static_cast<double>(static_cast<int>(direction))),
        convertToCharArray(static_cast<double>(static_cast<int>(bullets.size()))),
        convertToCharArray(static_cast<double>(visibility)),
        convertToCharArray(static_cast<double>(isPlayer)),

        convertToCharArray(static_cast<double>(isMoving)),
        convertToCharArray(static_cast<double>(anim)),
        convertToCharArray(static_cast<double>(prX)),
        convertToCharArray(static_cast<double>(prY))
    };
    for (int i = 0; i < bullets.size(); ++i)
    {
        dataVector.push_back(convertToCharArray(static_cast<double>(static_cast<int>(bullets[i].getDirection()))));
        dataVector.push_back(convertToCharArray(bullets[i].getCoordX()));
        dataVector.push_back(convertToCharArray(bullets[i].getCoordY()));
    }
    return dataVector;
}

void Tank::moveAI(sf::RenderWindow& window, Field& field, sf::Event& event, std::vector<Tank>& tankAI, double& prevX, double& prevY)
{
    prX = prevX;
    prY = prevY;

    if (direction == constants::Directions::UP)
    {
        prevX = round(prevX);
        prX = prevX;
        this->subCoordY -= getTankSpeed() * constants::delay;
        this->coordX = round(subCoordX);
        this->subCoordX = this->coordX;
        if (this->subCoordY <= this->coordY)
            this->coordY -= 0.5;
    }
    if (direction == constants::Directions::LEFT)
    {
        prevY = round(prevY);
        prY = prevY;
        this->subCoordX -= getTankSpeed() * constants::delay;
        this->coordY = round(subCoordY);
        this->subCoordY = this->coordY;
        if (this->subCoordX <= this->coordX)
            this->coordX -= 0.5;
    }
    if (direction == constants::Directions::RIGHT)
    {
        prevY = round(prevY);
        prY = prevY;
        this->subCoordX += getTankSpeed() * constants::delay;
        this->coordY = round(subCoordY);
        this->subCoordY = this->coordY;
        if (this->subCoordX >= this->coordX)
            this->coordX += 0.5;
    }
    if (direction == constants::Directions::DOWN)
    {
        prevX = round(prevX);
        prX = prevX;
        this->subCoordY += getTankSpeed() * constants::delay;
        this->coordX = round(subCoordX);
        this->subCoordX = this->coordX;
        if (this->subCoordY >= this->coordY)
            this->coordY += 0.5;
    }

    //int i = tankWithTankCollision(tankAI);
    //if (i != -1)
    //{
    //    tankAI[i].setDirection(static_cast<constants::Directions>((static_cast<int>(tankAI[i].getDirection()) + 2) % 4));
    //    this->direction = static_cast<constants::Directions>((static_cast<int>(this->direction) + 2) % 4);
    //    this->subCoordX = this->coordX = prevX;
    //    this->subCoordY = this->coordY = prevY;
    //}
}

void Tank::moveAIRandomly(sf::RenderWindow& window, Field& field, sf::Event& event, std::vector<Tank>& tankAI)
{
    double prevX = this->coordX, prevY = this->coordY;
    moveAI(window, field, event, tankAI, prevX, prevY);
    if (collisionWithField(field, this->coordX, this->coordY))
    {
        this->subCoordX = this->coordX = prevX;
        this->subCoordY = this->coordY = prevY;
        direction = static_cast<constants::Directions>((static_cast<int>(direction) + rand()) % 4);
    }
    if (rand() % 500 == 0)
    {
        if (direction == constants::Directions::UP)
            direction = constants::Directions::DOWN;
        if (direction == constants::Directions::DOWN)
            direction = constants::Directions::UP;
        if (direction == constants::Directions::RIGHT)
            direction = constants::Directions::LEFT;
        if (direction == constants::Directions::LEFT)
            direction = constants::Directions::RIGHT;
    }
    if (direction == constants::Directions::UP && !collisionWithField(field, getCoordX(), getCoordY() - 1) || direction == constants::Directions::UP && !collisionWithField(field, getCoordX(), getCoordY() + 1 ) || direction == constants::Directions::DOWN && !collisionWithField(field, getCoordX(), getCoordY() - 1) || direction == constants::Directions::DOWN && !collisionWithField(field, getCoordX(), getCoordY() + 1))
    {
        if (!collisionWithField(field, getCoordX() + 1, getCoordY()) && !collisionWithField(field, getCoordX() - 1, getCoordY()))
        {
            if (rand() % 128 == 0)
            {
                if (rand() % 2)
                    direction = constants::Directions::LEFT;
                else
                    direction = constants::Directions::RIGHT;
            }
        }
        else if (!collisionWithField(field, getCoordX() + 1, getCoordY()))
        {
            if (rand() % 128 == 0)
                direction = constants::Directions::RIGHT;
        }
        else if (!collisionWithField(field, getCoordX() - 1, getCoordY()))
        {
            if(rand() % 128 == 0)
                direction = constants::Directions::LEFT;
        }
    }
    if (direction == constants::Directions::LEFT && !collisionWithField(field, getCoordX() - 1, getCoordY()) || direction == constants::Directions::LEFT && !collisionWithField(field, getCoordX() + 1, getCoordY()) || direction == constants::Directions::RIGHT && !collisionWithField(field, getCoordX() - 1, getCoordY()) || direction == constants::Directions::RIGHT && !collisionWithField(field, getCoordX() + 1, getCoordY()))
    {
        if (!collisionWithField(field, getCoordX(), getCoordY() + 1) && !collisionWithField(field, getCoordX(), getCoordY() - 1))
        {
            if (rand() % 128 == 0)
            {
                if (rand() % 2)
                    direction = constants::Directions::UP;
                else
                    direction = constants::Directions::DOWN;
            }
        }
        else if (!collisionWithField(field, getCoordX(), getCoordY() + 1))
        {
            if (rand() % 128 == 0)
                direction = constants::Directions::DOWN;
        }
        else if (!collisionWithField(field, getCoordX(), getCoordY() - 1))
        {
            if (rand() % 128 == 0)
                direction = constants::Directions::UP;
        }
    }

    int i = tankWithTankCollision(tankAI);
    if (i != -1)
    {
        tankAI[i].setDirection(static_cast<constants::Directions>((static_cast<int>(tankAI[i].getDirection()) + 2) % 4));
        this->direction = static_cast<constants::Directions>((static_cast<int>(this->direction) + 2) % 4);
        this->subCoordX = this->coordX = prevX;
        this->subCoordY = this->coordY = prevY;
    }
}

void Tank::moveAIToAlly(sf::RenderWindow& window, Field& field, sf::Event& event, Tank& tank, std::vector<Tank>& tankAI)
{
    double prevX = this->coordX, prevY = this->coordY;
    moveAI(window, field, event, tankAI, prevX, prevY);
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

    if (direction == constants::Directions::UP && !collisionWithField(field, getCoordX(), getCoordY() - 1) || direction == constants::Directions::UP && !collisionWithField(field, getCoordX(), getCoordY() + 1) || direction == constants::Directions::DOWN && !collisionWithField(field, getCoordX(), getCoordY() - 1) || direction == constants::Directions::DOWN && !collisionWithField(field, getCoordX(), getCoordY() + 1))
    {

        if (!collisionWithField(field, getCoordX() + 1, getCoordY()) && tank.getCoordX() >= this->getCoordX())
        {
            if (rand() % 128 == 0)
                direction = constants::Directions::RIGHT;
        }
        else if (!collisionWithField(field, getCoordX() - 1, getCoordY()) && tank.getCoordX() <= this->getCoordX())
        {
            if (rand() % 128 == 0)
                direction = constants::Directions::LEFT;
        }
    }
    else if (direction == constants::Directions::LEFT && !collisionWithField(field, getCoordX() - 1, getCoordY()) || direction == constants::Directions::LEFT && !collisionWithField(field, getCoordX() + 1, getCoordY()) || direction == constants::Directions::RIGHT && !collisionWithField(field, getCoordX() - 1, getCoordY()) || direction == constants::Directions::RIGHT && !collisionWithField(field, getCoordX() + 1, getCoordY()))
    {
        if (!collisionWithField(field, getCoordX(), getCoordY() + 1) && tank.getCoordY() >= this->getCoordX())
        {
            if (rand() % 128 == 0)
                direction = constants::Directions::DOWN;
        }
        else if (!collisionWithField(field, getCoordX(), getCoordY() - 1) && tank.getCoordY() <= this->getCoordX())
        {
            if (rand() % 128 == 0)
                direction = constants::Directions::UP;
        }
    }

    int i = tankWithTankCollision(tankAI);
    if (i != -1)
    {
        tankAI[i].setDirection(static_cast<constants::Directions>((static_cast<int>(tankAI[i].getDirection()) + 2) % 4));
        this->direction = static_cast<constants::Directions>((static_cast<int>(this->direction) + 2) % 4);
        this->subCoordX = this->coordX = prevX;
        this->subCoordY = this->coordY = prevY;
    }
}

void Tank::moveAIToBase(sf::RenderWindow& window, Field& field, sf::Event& event, std::vector<Tank>& tankAI)
{
    double prevX = this->coordX, prevY = this->coordY;
    moveAI(window, field, event, tankAI, prevX, prevY);
    if (collisionWithField(field, this->coordX, this->coordY))
    {
        this->subCoordX = this->coordX = prevX;
        this->subCoordY = this->coordY = prevY;
        if (14 >= this->getCoordX() && 28 >= this->getCoordY())
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
        else if (14 <= this->getCoordX() && 28 <= this->getCoordY())
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
        else if (14 <= this->getCoordX() && 28 >= this->getCoordY())
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
        else if (14 >= this->getCoordX() && 28 <= this->getCoordY())
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

    if (direction == constants::Directions::UP && !collisionWithField(field, getCoordX(), getCoordY() - 1) || direction == constants::Directions::UP && !collisionWithField(field, getCoordX(), getCoordY() + 1) || direction == constants::Directions::DOWN && !collisionWithField(field, getCoordX(), getCoordY() - 1) || direction == constants::Directions::DOWN && !collisionWithField(field, getCoordX(), getCoordY() + 1))
    {

        if (!collisionWithField(field, getCoordX() + 1, getCoordY()) && 14 >= this->getCoordX())
        {
            if (rand() % 128 == 0)
                direction = constants::Directions::RIGHT;
        }
        else if (!collisionWithField(field, getCoordX() - 1, getCoordY()) && 14 <= this->getCoordX())
        {
            if (rand() % 128 == 0)
                direction = constants::Directions::LEFT;
        }
    }
    else if (direction == constants::Directions::LEFT && !collisionWithField(field, getCoordX() - 1, getCoordY()) || direction == constants::Directions::LEFT && !collisionWithField(field, getCoordX() + 1, getCoordY()) || direction == constants::Directions::RIGHT && !collisionWithField(field, getCoordX() - 1, getCoordY()) || direction == constants::Directions::RIGHT && !collisionWithField(field, getCoordX() + 1, getCoordY()))
    {
        if (!collisionWithField(field, getCoordX(), getCoordY() + 1) && 28 >= this->getCoordX())
        {
            if (rand() % 128 == 0)
                direction = constants::Directions::DOWN;
        }
        else if (!collisionWithField(field, getCoordX(), getCoordY() - 1) && 28 <= this->getCoordX())
        {
            if (rand() % 128 == 0)
                direction = constants::Directions::UP;
        }
    }

    int i = tankWithTankCollision(tankAI);
    if (i != -1)
    {
        tankAI[i].setDirection(static_cast<constants::Directions>((static_cast<int>(tankAI[i].getDirection()) + 2) % 4));
        this->direction = static_cast<constants::Directions>((static_cast<int>(this->direction) + 2) % 4);
        this->subCoordX = this->coordX = prevX;
        this->subCoordY = this->coordY = prevY;
    }
}

void Tank::animation(int fps)
{
    if (fps % constants::ANIMATION_SPEED == 0 && this->isMoving)
        this->anim = !anim;
}