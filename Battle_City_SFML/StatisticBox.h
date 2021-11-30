#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
class StatisticBox
{
public:
	StatisticBox(float width, float height, int posX, int posY);
	~StatisticBox();
	void draw(sf::RenderWindow& window);
	void SetStatistics(double value, int type);
	long double GetStatistics(int type);
	void statisticReset();
private:
	double values[constants::MAX_NUMBER_OF_STATISTICS_ITEMS];
	sf::Font font;
	sf::Text text[constants::MAX_NUMBER_OF_STATISTICS_ITEMS];
	float width, height;
	int posX, posY;
};
