#ifndef BULLETS_H
#define BULLETS_H

#include "Object.h"

class BulletPlayer : public Object
{
public:
    BulletPlayer();
    BulletPlayer(SDL_Texture* texture, float X1, float Y1, bool direction);
    virtual ~BulletPlayer();
    void update(double deltaTime);
protected:
    int speed;
    bool direction;
};

class BulletEnemy : public BulletPlayer
{
public:
    BulletEnemy();
    BulletEnemy(SDL_Texture* texture, float X1, float Y1, bool direction);
    virtual ~BulletEnemy();
    //void update(double deltaTime);
private:
    //int speed;  
};

#endif /* BULLETPLAYER_H */

