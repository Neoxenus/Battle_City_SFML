#pragma once
#include "Constants.h"
#include "Tank.h"
class Bullet
{
private:
	constants::Directions direction;
	double coordX, coordY;
	int speed;
public:
	Bullet(Tank tank);
	void draw();
};

