#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Field.h"

class Tank
{
    //3,3,3,3,2,4,2,2 ;tank speed //pixel per 4 frames
//2,4,4,4,2,2,4,2 ;bullet speed pixel per frame
private:
        bool isPlayer;//true - player
        constants::Directions direction;
        bool isMoving = false;
        int tankType;//0 to 3
        double coordX, coordY;
public:
        Tank()
        {
            isPlayer = false;
            tankType = 0;
            direction = constants::Directions::UP;
            coordX = constants::DEFAULT_ENEMY_COORD_X[1];
            coordY = constants::DEFAULT_ENEMY_COORD_Y;
        }
        Tank(bool isPlayer, int tankType)
        {
            this->isPlayer = isPlayer;
            if (tankType < 0 || tankType > 3)
                tankType = 0;
            this->tankType = tankType;
            direction = constants::Directions::UP;
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
        double getTankSpeed();//pixel per 1 second
        void draw(sf::RenderWindow& window);
};

