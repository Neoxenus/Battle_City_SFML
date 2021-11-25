#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
class Field
{
public: 
	std::vector<std::vector<int>> blocks;
	Field();
	~Field();
	void draw(sf::RenderWindow& window);
};

