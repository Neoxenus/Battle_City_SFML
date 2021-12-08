#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Convert.h"

class Field
{
	std::vector<std::vector<int>> field;
	int enemyCount;
	int playerLives;
	int enemyToSpawn;
public: 
	Field();
	~Field();
	
	void setPlayerLives(int val);
	int getPlayerLives();
	void setEnemyCount(int val);
	int getEnemyCount();
	void setEnemyToSpawn(int val);
	int getEnemyToSpawn();
	bool isBaseAlive();

	int getField(int x, int y);
	void setField(int x, int y, constants::Tiles value);
	void setField(const std::vector<std::vector<int>>& level);
	void draw(sf::RenderWindow& window, sf::Texture& texture_block, sf::Texture& texture_base);
	std::vector<char*> sendToServer();

	void newField(std::vector<std::string>);
};

