#ifndef ENEMIES_H
#define ENEMIES_H

#include "Object.h"
#include "Bullets.h"

class EnemyBase : public Object
{
public:
    EnemyBase();
    EnemyBase(HBITMAP sprite, float X1, float Y1, bool direction);
    virtual ~EnemyBase();
    //void update(double deltaTime, vector<BulletPlayer> bulletPlayer);
    void update(double deltaTime);
    int isEnemyHit(vector<BulletPlayer> bulletPlayer);
    bool isDead();
    bool animationDestroy();
protected:
    int life;
    bool direction;
    //vector<BulletPlayer> bulletPlayer;
    void collisionBorder();
};

class EnemyLaser : public EnemyBase
{
public:
    EnemyLaser();
    EnemyLaser(HBITMAP sprite, float X1, float Y1, bool direction);
    virtual ~EnemyLaser();
    //void update(double deltaTime, vector<BulletPlayer> bulletPlayer);
    void update(double deltaTime);
    //int isEnemyHit(vector<BulletPlayer> bulletPlayer);
    //bool isDead();
    //bool animationDestroy();
protected:
    //vector<BulletPlayer> bulletPlayer;
    //void collisionBorder();
};

#endif /* ENEMY_H */

