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

class BulletPlayerSpecial : public BulletPlayer
{
public:
    BulletPlayerSpecial();
    BulletPlayerSpecial(SDL_Texture* texture, float X1, float Y1, float targetX, float targetY, int speed);
    virtual ~BulletPlayerSpecial();
    void update(double deltaTime) override;
    void draw(SDL_Renderer* renderer) override;
protected:
    double dx;
    double dy;
    double deltaX;
    double deltaY;
    double angleRotation;
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
    BulletEnemyDiagonal(SDL_Texture* texture, float X1, float Y1, float targetX, float targetY, int speed);
    virtual ~BulletEnemyDiagonal();
    void update(double deltaTime);
    void draw(SDL_Renderer * renderer);
private:
    double dx;
    double dy;
    double deltaX;
    double deltaY;
    double angleRotation;
};

#endif /* BULLETPLAYER_H */

