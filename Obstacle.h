#include "Object.h"
#include "Loader.h"
#include "Bullets.h"
#include "Player.h"

#ifndef OBSTACLE_H
#define OBSTACLE_H

class Player;

class Obstacle : public Object 
{
public:
    Obstacle();
    Obstacle(std::vector<SDL_Texture*> textures);
    Obstacle(std::vector<SDL_Texture*> textures, float X1, float Y1);
    virtual ~Obstacle();
    void update(float deltaTime);
    void animationBase(float deltaTime);
    void animationDead(float deltaTime);
    int isObstacleHit(std::vector<BulletPlayer*> bulletPlayer);
    bool isCollsionBorder();
    bool isDead();
    void reduceLife();
    int getScore();
    virtual void draw(SDL_Renderer* renderer);
protected:
    const int score = 15;
    int life;
    float targetY;
    bool direction;
    float slope;
    float intercept;
    int angleRotation;
};

class Asteroid : public Obstacle 
{
public:
    Asteroid();
    Asteroid(std::vector<SDL_Texture*> textures);
    Asteroid(std::vector<SDL_Texture*> textures, float X1, float Y1);
    virtual ~Asteroid();
protected:
};

class PowerUp : public Obstacle
{
public:
    PowerUp();
    PowerUp(std::vector<SDL_Texture*> textures, int type);
    PowerUp(std::vector<SDL_Texture*> textures, float X1, float Y1, int type);
    virtual ~PowerUp();
    bool isCollisionPlayer(Player* player);
    void setPowerEffect(Player* player);
private:
    int type;
};

#endif /* OBSTACLE_H */

