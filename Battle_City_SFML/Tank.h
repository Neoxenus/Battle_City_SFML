#pragma once
#include "Constants.h"
class Tank
{
    //3,3,3,3,2,4,2,2 ;tank speed //pixel per 4 frames
//2,4,4,4,2,2,4,2 ;bullet speed pixel per frame
private:
        bool isPlayer;//true - player
        int directionX = 0, directionY = 0;
        bool isMoving = false;
        int tankType;//0 to 3
public:
        Tank()
        {
            isPlayer = false;
            tankType = 0;
        }
        Tank(bool isPlayer, int tankType)
        {
            this->isPlayer = isPlayer;
            if (tankType < 0 || tankType > 3)
                tankType = 0;
            this->tankType = tankType;
        }
        int getTankSpeed();//pixel per 4 frames
};

