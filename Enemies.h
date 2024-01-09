#ifndef ENEMIES_H
#define ENEMIES_H

#include "Object.h"
#include "Bullets.h"

class EnemyBase : public Object
{
public:
    EnemyBase();
    EnemyBase(SDL_Texture* texture, float X1, float Y1, bool direction);
    virtual ~EnemyBase();
    void update(double deltaTime);
    int isEnemyHit(vector<BulletPlayer*> bulletPlayer);
    bool shot(double deltaTime);
    bool isDead();
    bool animationDestroy();
protected:
    int life;
    bool direction;
    double coolDownShot;
    void collisionBorder();
};

class EnemyLaser : public EnemyBase
{
public:
    EnemyLaser();
    EnemyLaser(SDL_Texture* texture, float X1, float Y1, bool direction);
    virtual ~EnemyLaser();
    void update(double deltaTime) override;
protected:
};

#endif /* ENEMIES_H */

