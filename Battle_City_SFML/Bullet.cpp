#include "Bullet.h"
#include "Tank.h"
#include "Constants.h"

Bullet::Bullet(Tank tank)
{
	direction = tank.getDirection();
	coordX = tank.getCoordX(), coordY = tank.getCoordY();
	speed = constants::bulletSpeed[tank.getTankType() + 4 * (tank.getIsPlayer() == false)];
}
