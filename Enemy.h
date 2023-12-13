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
    bool isEnemyHit();
    bool animationDestroy();
protected:
    int life;
    vector<BulletPlayer> bulletPlayer;
};

#endif /* ENEMY_H */

