#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
class Field
{
public: 
	Field();
	~Field();

private:
	void draw(sf::RenderWindow& window, int tiles[constants::FIELD_HEIGHT][constants::FIELD_WIDTH]);
};

