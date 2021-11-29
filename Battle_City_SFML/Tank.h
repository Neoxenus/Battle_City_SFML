#pragma once
#include "Field.h"
#include "Bullet.h"

class Tank
{
    //3,3,3,3,2,4,2,2 ;tank speed //pixel per 4 frames
//2,4,4,4,2,2,4,2 ;bullet speed pixel per frame
private:
    bool visibility;
    int alreadyShot;
    bool isPlayer;//true - player
    constants::Directions direction;
    bool isMoving = false;
    bool anim = false;
    int tankType;//0 to 3
    double coordX, coordY;//coords with step 0.5 tiles
    double prX, prY;
    double subCoordX, subCoordY;//absolute coords for drawing
    std::vector <Bullet> bullets;
public:
    Tank();
    Tank(bool isPlayer, int tankType);
    void newTank(Tank& tank, std::vector<char*>);
    constants::Directions getDirection();
    int getMaxShots();
    double getCoordX();
    double getPrX();
    double getPrY();
    void setCoordX(double x);
    void setSubCoordX(double x);
    double getCoordY();
    void setCoordY(double x);
    void setSubCoordY(double x);
    void setDirection(constants::Directions dir);
    int getTankType();
    bool getIsPlayer();
    double getTankSpeed();
    void setVisibility(bool flag);
    bool isVisible();
    int getAlreadyShot();
    void setAlreadyShot(int value);
    void setBullets(std::vector<Bullet> tmpbullets);
    std::vector <Bullet> getBullets();
    bool getIsMoving();//pixel per 1 second
    void draw(sf::RenderWindow& window, sf::Texture& texture_all);
    bool collisionWithField(Field& field, double prevX, double prevY);
    int tankWithTankCollision(std::vector<Tank>& tanks);
    bool tankDeath(Tank& tank);
    void control(sf::RenderWindow& window, Field& field, sf::Event& event, std::vector<Tank>& tankAI);
    void bullet_shoot(sf::RenderWindow& window, sf::Event& event);
    void bullets_colision(Field& field);
    void shot();
    std::vector<char*> sendToServer();
    void moveAI(sf::RenderWindow& window, Field& field, sf::Event& event, std::vector<Tank>& tankAI, double& prevX, double& prevY);
    void moveAIRandomly(sf::RenderWindow& window, Field& field, sf::Event& event, std::vector<Tank>& tankAI);
    void moveAIToBase(sf::RenderWindow& window, Field& field, sf::Event& event, std::vector<Tank>& tankAI);
    void moveAIToAlly(sf::RenderWindow& window, Field& field, sf::Event& event, Tank& tank, std::vector<Tank>& tankAI);
    void animation(int fps);
};



