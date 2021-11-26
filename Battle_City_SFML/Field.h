#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
class Field
{
	std::vector<std::vector<int>> field;
public: 
	Field();
	~Field();
	int getField(int x, int y);
	void setField(int x, int y, constants::Tiles value);
	void setField(const std::vector<std::vector<int>> level);
	void draw(sf::RenderWindow& window);
};

