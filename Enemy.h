#ifndef ENEMY_H
#define ENEMY_H

#include "Object.h"
#include "BulletPlayer.h"

class Enemy : public Object
{
public:
    Enemy();
    Enemy(HBITMAP sprite, float X1, float Y1);
    virtual ~Enemy();
    void update(double deltaTime, vector<BulletPlayer> bulletPlayer);
    void update(double deltaTime);
    int isEnemyHit(vector<BulletPlayer> bulletPlayer);
    bool isDead();
    bool animationDestroy();
protected:
    int life;
    //vector<BulletPlayer> bulletPlayer;
    void collisionBorder();
};

#endif /* ENEMY_H */

