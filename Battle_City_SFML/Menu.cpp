#include "Menu.h"

Menu::Menu(float width, float height,int numberOfOptions, const std::string *text, const float offsetX, const float fontSize)
{
	this->height = height;
	this->width = width;
	this->numberOfOptions = numberOfOptions;
	menu.resize(numberOfOptions);
	if (!font.loadFromFile(constants::fontFile))
	{
		exit(-4);
	}
	//using namespace std;
	//cout << endl;
	for (int i = 0; i < numberOfOptions; i++)
	{
		menu[i].setFont(font);
		menu[i].setFillColor(sf::Color::White);
		menu[i].setPosition(0+ constants::WINDOW_OFFSET+ offsetX, 
			constants::menuOffset +	constants::WINDOW_OFFSET + (height / numberOfOptions * i)*constants::zoom);
		
		
		/*cout << menu[i].getPosition().x << " " << menu[i].getPosition().y;
		cout << endl;*/
		menu[i].setString(text[i]);
		menu[i].setCharacterSize(fontSize);
	}
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < numberOfOptions; i++)
	{
		window.draw(menu[i]);
	}
}

int Menu::choose(int posX, int posY)
{
	if (posX >= constants::windowWidth || posY >= constants::windowHeight || posX < 0 || posY < 0)
	{
		return -1;
	}
	for (int i = numberOfOptions-1; i >=0  ; --i)
	{
		
		if ((menu[i].getPosition().y-constants::WINDOW_OFFSET - constants::menuOffset) / constants::zoom  <= posY)
			return i;
	}
	return -2;
}