#ifndef BULLETS_H
#define BULLETS_H

#include "Object.h"
#include <cmath>

class BulletPlayer : public Object
{
public:
    BulletPlayer();
    BulletPlayer(SDL_Texture* texture, float X1, float Y1, bool direction, int speed);
    virtual ~BulletPlayer();
    void update(double deltaTime);
protected:
    int speed;
    bool direction;
    void animationBase(double deltaTime);
    void animationDead(double deltaTime);
};

class BulletEnemy : public BulletPlayer
{
public:
    BulletEnemy();
    BulletEnemy(SDL_Texture* texture, float X1, float Y1, bool direction, int speed);
    virtual ~BulletEnemy();
};

class BulletEnemyDiagonal : public BulletEnemy
{
public:
    BulletEnemyDiagonal();
    //BulletEnemyDiagonal(SDL_Texture* texture, float X1, float Y1, bool direction, int speed, double targetX);
    BulletEnemyDiagonal(SDL_Texture* texture, float X1, float Y1, bool direction, int speed, double targetX, double targetY);
    virtual ~BulletEnemyDiagonal();
    void update(double deltaTime);
    void draw(SDL_Renderer * renderer);
private:
    bool up = false;
    double slope;
    double intercept;
    double angleRotation;
};

#endif /* BULLETPLAYER_H */

