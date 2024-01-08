#ifndef BULLETS_H
#define BULLETS_H

#include "Object.h"

class BulletPlayer : public Object
{
public:
    BulletPlayer();
    BulletPlayer(HBITMAP sprite, float X1, float Y1);
    virtual ~BulletPlayer();
    void update(double deltaTime);
private:
    int speed;
};

class BulletEnemy : public Object
{
public:
    BulletEnemy();
    BulletEnemy(HBITMAP sprite, float X1, float Y1);
    virtual ~BulletEnemy();
    void update(double deltaTime);
private:
    int speed;  
};

#endif /* BULLETPLAYER_H */

