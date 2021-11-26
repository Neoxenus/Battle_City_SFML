#pragma once
#include "Constants.h"
#include "SFML/Graphics.hpp"

class Bullet
{
private:
	constants::Directions direction;
	double coordX, coordY;
	int speed;
public:
	Bullet(constants::Directions direction, double coordX, double coordY, int tankType, bool isPlayer);
	void draw(sf::RenderWindow& window); 
	double getCoordX();
	double getCoordY();
	constants::Directions getDirection();
};

