#ifndef ENEMIES_H
#define ENEMIES_H

#include "Object.h"
#include "Bullets.h"
#include <cmath>

class EnemyBase : public Object 
{
public:
    EnemyBase();
    EnemyBase(vector<SDL_Texture*> textures, float X1, float Y1, bool direction, int movimentType);
    virtual ~EnemyBase();
    void update(double deltaTime);
    virtual int isEnemyHit(vector<BulletPlayer*> bulletPlayer);
    virtual bool shot(double deltaTime);
    bool isDead();
protected:
    int life;
    bool direction;
    int movimentType;
    double coolDownShot;
    double angle;
    void collisionBorder();
    void animationBase(double deltaTime);
    void animationDead(double deltaTime);
};

class EnemyLaser : public EnemyBase 
{
public:
    EnemyLaser();
    EnemyLaser(vector<SDL_Texture*> textures, float X1, float Y1, bool direction, int movimentType);
    virtual ~EnemyLaser();
    bool shot(double deltaTime) override;
    void update(double deltaTime) override;
    bool isFirstShot();
    void setFirstShot();
private:
    bool firstShot;
};

class EnemyMid : public EnemyBase
{
public:
    EnemyMid();
    EnemyMid(vector<SDL_Texture*> textures, float X1, float Y1);
    virtual ~EnemyMid();
    int isEnemyHit(vector<BulletPlayer*> bulletPlayer) override;
    void update(double deltaTime) override;
private:
    double hitTex;
};

#endif /* ENEMIES_H */

