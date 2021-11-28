#include "Tank.h"

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
        subCoordX = coordX = constants::DEFAULT_PLAYER_COORD_X[0];
        subCoordY = coordY = constants::DEFAULT_PLAYER_COORD_Y;
    }
    else
    {
       subCoordX = coordX = constants::DEFAULT_ENEMY_COORD_X[1];
       subCoordY = coordY = constants::DEFAULT_ENEMY_COORD_Y;
    }
}

double Tank::getTankSpeed()
{
    return constants::tankSpeed[4 * (isPlayer)+tankType] * 16.0 / constants::TILES_LENGHT;
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
    sprite_all.setPosition(this->subCoordX * constants::TILES_LENGHT, this->subCoordY * constants::TILES_LENGHT);
    sprite_all.move(constants::WINDOW_OFFSET, constants::WINDOW_OFFSET);
	window.draw(sprite_all);
    for (int i = 0; i < bullets.size(); ++i)
    {
        bullets[i].draw(window);
    }
}

void Tank::control(sf::RenderWindow& window, Field& field, sf::Event& event)
{
    double prevX = this->coordX, prevY = this->coordY;
    //if (event.type == sf::Event::KeyPressed)
    //{
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            this->direction = constants::Directions::UP;
            prevX = round(prevX);
            this->subCoordY -= getTankSpeed()*constants::delay;
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
            prevY = round(prevY);
            this->subCoordX += getTankSpeed() * constants::delay;
            this->coordY = round(subCoordY);
            this->subCoordY = this->coordY;
            if (subCoordX >= coordX)
            {
                this->coordX += 0.5;
            }
        }
        /*if (event.key.code == sf::Keyboard::Space)
        {
            if (this->alreadyShot != this->getMaxShots())
            {
                ++this->alreadyShot;
                this->shot();
            }
        }*/
    //}
    if (collision(field, this->coordX, this->coordY))
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

bool Tank::collision(Field& field, double X, double Y, int spriteSize)
{
    int x0 = X, y0 = Y, x1 = ceil(X + spriteSize), y1 = ceil(Y + spriteSize);
    for(int i = x0; i < x1; ++i)
        for (int j = y0; j < y1; ++j)
        {
            if (field.getField(i, j) != static_cast<int>(constants::Tiles::BLACK) && field.getField(i, j) != static_cast<int>(constants::Tiles::ICE) && field.getField(i, j) != static_cast<int>(constants::Tiles::TREE))
                return true;
        }
    return false;
}


std::vector<char*> Tank::sendToServer()
{
    std::vector<char*> dataVector
    { convertToCharArray(alreadyShot), convertToCharArray(coordX), convertToCharArray(coordY),
      convertToCharArray(subCoordX), convertToCharArray(subCoordY), convertToCharArray(tankType),
      convertToCharArray(static_cast<int>(direction)) 
    };
    for (int i = 0; i < bullets.size(); ++i)
    {
        dataVector.push_back(convertToCharArray(bullets[i].getCoordX()));
        dataVector.push_back(convertToCharArray(bullets[i].getCoordY()));
        dataVector.push_back(convertToCharArray(static_cast<int>(bullets[i].getDirection())));
        dataVector.push_back(convertToCharArray(bullets[i].getBulletSpeed()));
    }
    return dataVector;
}
