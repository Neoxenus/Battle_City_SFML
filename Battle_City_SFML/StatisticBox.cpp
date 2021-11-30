#include "StatisticBox.h"
StatisticBox::StatisticBox(float width, float height, int posX, int posY)
{
	this->width = width;
	this->height = height;
	this->posX = posX;
	this->posY = posY;
	if (!font.loadFromFile(constants::fontFile))
	{
		exit(4);
	}
	for (int i = 0; i < constants::MAX_NUMBER_OF_STATISTICS_ITEMS; i++)
	{
		values[i] = constants::statisticDefault[i];
		text[i].setFont(font);
		text[i].setFillColor(sf::Color(0,0,0));
		text[i].setPosition(constants::WINDOW_OFFSET + posX,
			(i * height / constants::MAX_NUMBER_OF_STATISTICS_ITEMS) * constants::zoom + constants::WINDOW_OFFSET + posY);
		//0 + constants::WINDOW_OFFSET + offsetX,
		//	constants::menuOffset + constants::WINDOW_OFFSET + (height / numberOfOptions * i) * constants::zoom
		text[i].setCharacterSize(constants::staticsticFontSize);
		SetStatistics(values[i], i);
		//text[i].setString(constants::statisticsText[i] + std::to_string(static_cast<long>(values[i])));
		
	}
	
}

StatisticBox::~StatisticBox()
{
}

void StatisticBox::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < constants::MAX_NUMBER_OF_STATISTICS_ITEMS; i++)
	{
		window.draw(text[i]);
	}
}

void StatisticBox::SetStatistics(double value, int type)
{
	if (type < 0 || type >= constants::MAX_NUMBER_OF_STATISTICS_ITEMS)
		exit(-4);
	this->values[type] = value;
	text[type].setString(constants::statisticsText[type] + std::to_string(static_cast<long>(value)));
}

long double StatisticBox::GetStatistics(int type)
{
	if (type < 0 || type >= constants::MAX_NUMBER_OF_STATISTICS_ITEMS)
		exit(-5);
	return values[type];
}
