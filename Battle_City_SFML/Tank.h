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
    Tank();
    Tank(bool isPlayer, int tankType);
    constants::Directions getDirection();
    double getCoordX();
    double getCoordY();
    int getTankType();
    bool getIsPlayer();
    double getTankSpeed();//pixel per 1 second
    void draw(sf::RenderWindow& window);
};

