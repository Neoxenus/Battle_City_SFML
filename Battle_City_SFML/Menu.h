#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <iostream>
class Menu
{
public:
	Menu(float width, float height, int numberOfOptions, const std::string* text, const float offsetX, const float fontSize);
	~Menu();
	void draw(sf::RenderWindow& window);
	int choose(int posX, int posY);
private:
	sf::Font font;
	float height, width;
	int numberOfOptions;
	std::vector<sf::Text> menu;
};

