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
    void update(float deltaTime);
protected:
    int speed;
    bool direction;
    void animationBase(float deltaTime);
    void animationDead(float deltaTime);
};

class BulletPlayerSpecial : public BulletPlayer
{
public:
    BulletPlayerSpecial();
    BulletPlayerSpecial(SDL_Texture* texture, float X1, float Y1, float targetX, float targetY, int speed);
    virtual ~BulletPlayerSpecial();
    void update(float deltaTime) override;
    void draw(SDL_Renderer* renderer) override;
protected:
    float dx;
    float dy;
    float deltaX;
    float deltaY;
    float angleRotation;
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
    void update(float deltaTime);
    void draw(SDL_Renderer * renderer);
    void activeRotation() { rotation = true; }
private:
    bool rotation = false;
    float dx;
    float dy;
    float deltaX;
    float deltaY;
    float angleRotation = 0;
};

#endif /* BULLETPLAYER_H */

