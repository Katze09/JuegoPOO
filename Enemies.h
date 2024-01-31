#ifndef ENEMIES_H
#define ENEMIES_H

#include "Object.h"
#include "Bullets.h"
#include <cmath>

class EnemyBase : public Object 
{
public:
    EnemyBase();
    EnemyBase(vector<SDL_Texture*> textures, float X1, float Y1, bool direction, int movimentType, int bulletSpeed);
    virtual ~EnemyBase();
    void update(double deltaTime);
    virtual int isEnemyHit(vector<BulletPlayer*> bulletPlayer);
    virtual bool shot(double deltaTime);
    bool isDead();
    int getLife(){return life;}
    int getBulletSpeed();
    int getScore();
protected:
    const int score = 5;
    int bulletSpeed;
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
    EnemyLaser(vector<SDL_Texture*> textures, float X1, float Y1, bool direction, int movimentType, double moveTo, int bulletSpeed);
    virtual ~EnemyLaser();
    bool shot(double deltaTime) override;
    void update(double deltaTime) override;
    bool isFirstShot();
    void setFirstShot();
private:
    double laserSize;
    bool firstShot;
    double moveTo;
};

class EnemyMid : public EnemyBase
{
public:
    EnemyMid();
    EnemyMid(vector<SDL_Texture*> textures, float X1, float Y1, double moveTo, int bulletSpeed);
    virtual ~EnemyMid();
    int isEnemyHit(vector<BulletPlayer*> bulletPlayer) override;
    void update(double deltaTime) override;
protected:
    const int score = 20;
    double hitTex;
    double moveTo;
};

class EnemyBoss : public EnemyMid
{
public:
    EnemyBoss();
    EnemyBoss(vector<SDL_Texture*> textures, float X1, float Y1, double moveTo, int bulletSpeed);
    virtual ~EnemyBoss();
    bool shot(double deltaTime);
    void update(double deltaTime) override;
    bool isSecondPart(){return secondFase;}
    bool isSecondPartP2(){return secondFaseP2;}
    bool isThirdPart(){return thirdFase;}
private:
    const int score = 100;
    bool secondFase;
    bool secondFaseP2;
    bool thirdFase;
    double contSecondFaseShot;
    
};

#endif /* ENEMIES_H */

