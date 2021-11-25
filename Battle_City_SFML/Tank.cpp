#include "Tank.h"

int Tank::getTankSpeed()
{
    {
        if (isPlayer)
        {
            return constants::tankSpeed[tankType];
        }
        else
            return constants::tankSpeed[4 + tankType];
    }
}
