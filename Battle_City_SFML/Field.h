#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
class Field
{
public: 
	std::vector<std::vector<int>> blocks[constants::FIELD_HEIGHT][constants::FIELD_WIDTH];
	Field();
	~Field();

private:
	void draw(sf::RenderWindow& window);
};

