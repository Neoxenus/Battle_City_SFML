#pragma once
#include "Tank.h"

class Bullet
{
private:
	constants::Directions direction;
	double coordX, coordY;
	int speed;
public:
	Bullet(Tank& tank);
	void draw(sf::RenderWindow& window);
};

