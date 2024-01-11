#ifndef ENEMIES_H
#define ENEMIES_H

#include "Object.h"
#include "Bullets.h"

class EnemyBase : public Object
{
public:
    EnemyBase();
    EnemyBase(vector<SDL_Texture*> textures, float X1, float Y1, bool direction);
    virtual ~EnemyBase();
    void update(double deltaTime);
    int isEnemyHit(vector<BulletPlayer*> bulletPlayer);
    virtual bool shot(double deltaTime);
    bool isDead();
protected:
    int life;
    bool direction;
    double coolDownShot;
    void collisionBorder();
    void animationBase(double deltaTime);
    void animationDead(double deltaTime);
};

class EnemyLaser : public EnemyBase
{
public:
    EnemyLaser();
    EnemyLaser(vector<SDL_Texture*> textures, float X1, float Y1, bool direction);
    virtual ~EnemyLaser();
    bool shot(double deltaTime) override;
    void update(double deltaTime) override;
    bool isFirstShot();
    void setFirstShot();
private:
    bool firstShot;
};

#endif /* ENEMIES_H */

