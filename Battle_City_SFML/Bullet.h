#pragma once
#include "Constants.h"
#include "SFML/Graphics.hpp"
#include "Field.h"
class Bullet
{
private:
	constants::Directions direction;
	double coordX, coordY;
	int speed;
public:
	Bullet(constants::Directions direction, double coordX, double coordY, int tankType, bool isPlayer);
	void draw(sf::RenderWindow& window, sf::Texture& texture_all, bool isCLient = false);
	bool collision_bullet(Field& field);
	bool bulletWithBulletCollision(Bullet& bullet);
	double getCoordX();
	double getCoordY();
	void updateCoord();
	double getBulletSpeed();
	constants::Directions getDirection();
};

