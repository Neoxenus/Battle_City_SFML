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
    int tankType;//0 to 3
    double coordX, coordY;//coords with step 0.5 tiles
    double subCoordX, subCoordY;//absolute coords for drawing
    std::vector <Bullet> bullets;
public:
    Tank();
    Tank(bool isPlayer, int tankType);
    void newTank(Tank& tank, std::vector<char*>);
    constants::Directions getDirection();
    int getMaxShots();
    double getCoordX();
    void setCoordX(double x);
    void setSubCoordX(double x);
    double getCoordY();
    int getTankType();
    bool getIsPlayer();
    double getTankSpeed();
    void setVisibility(bool flag);
    bool isVisible();
    std::vector <Bullet> getBullets();
    bool getIsMoving();//pixel per 1 second
    void draw(sf::RenderWindow& window, sf::Texture& texture_all, int animation);
    bool collisionWithField(Field& field, double prevX, double prevY, int spriteSize = 2);
    bool tankWithTankCollision(Tank& tank);
    bool tankDeath(std::vector<Bullet> all_bullets);
    void control(sf::RenderWindow& window, Field& field, sf::Event& event);
    void bullet_shoot(sf::RenderWindow& window, sf::Event& event);
    void bullets_colision(Field& field);
    void shot();
    std::vector<char*> sendToServer();
    void moveAI(sf::RenderWindow& window, Field& field, sf::Event& event);
    void moveAIRandomly(sf::RenderWindow& window, Field& field, sf::Event& event);
    void moveAIToAlly(sf::RenderWindow& window, Field& field, sf::Event& event, Tank tank);
};



