#pragma once

#include "Object.h"
#include "Bullets.h"
#include <cmath>

class EnemyBase : public Object 
{
public:
    EnemyBase();
    EnemyBase(std::vector<SDL_Texture*> textures, float X1, float Y1, bool direction, int movimentType, int bulletSpeed);
    virtual ~EnemyBase();
    void update(float deltaTime);
    virtual int isEnemyHit(std::vector<BulletPlayer*> bulletPlayer);
    virtual bool shot(float deltaTime);
    bool isDead();
    int getLife(){return life;}
    void reduceLife() { life--; }
    int getBulletSpeed();
    int getScore();
    bool isOffLimits() { return X2 < -50 || X1 > 750 || Y2 < -50 || Y1 > 850; }
protected:
    const int score = 15;
    int bulletSpeed;
    int life;
    bool direction;
    int movimentType;
    float coolDownShot;
    float angle;
    virtual void collisionBorder();
    void animationBase(float deltaTime);
    void animationDead(float deltaTime);
};

class EnemyLaser : public EnemyBase 
{
public:
    EnemyLaser();
    EnemyLaser(std::vector<SDL_Texture*> textures, float X1, float Y1, bool direction, int movimentType, float moveTo, int bulletSpeed);
    virtual ~EnemyLaser();
    bool shot(float deltaTime) override;
    void update(float deltaTime) override;
    bool isFirstShot();
    void setFirstShot();
protected:
    float laserSize;
    bool firstShot;
    float moveTo;
};

class EnemyStar : public EnemyLaser
{
public:
    EnemyStar();
    EnemyStar(std::vector<SDL_Texture*> textures, float X1, float Y1, bool direction, int movimentType, float moveTo, int bulletSpeed);
    virtual ~EnemyStar();
    void update(float deltaTime) override;
    int isEnemyHit(std::vector<BulletPlayer*> bulletPlayer) override;
    bool shot(float deltaTime) override;
protected:
    float hitTex;
};

class EnemyKamikaze : public EnemyBase
{
public:
    EnemyKamikaze();
    EnemyKamikaze(std::vector<SDL_Texture*> textures, float X1, float Y1);
    EnemyKamikaze(std::vector<SDL_Texture*> textures, float X1, float Y1, float speed);
    EnemyKamikaze(std::vector<SDL_Texture*> textures, float X1, float Y1, bool direction, int bulletSpeed);
    virtual ~EnemyKamikaze();
    virtual void update(float deltaTime, float targetX, float targetY);
    bool shot(float deltaTime) { return false; }
    void draw(SDL_Renderer* renderer) override;
    int playerIndex = -1;
protected:
    float angleRotation = 0;
};

class EnemyAngry : public EnemyKamikaze
{
public:
    EnemyAngry();
    EnemyAngry(std::vector<SDL_Texture*> textures, float X1, float Y1, bool direction, int bulletSpeed);
    virtual ~EnemyAngry();
    void update(float deltaTime, float targetX, float targetY) override;
    int isEnemyHit(std::vector<BulletPlayer*> bulletPlayer) override;
    void setAngry() { angry = true; }
    bool shot(float deltaTime) override;
    bool isAngry() const { return angry; }
    void collisionBorder() override {};
private:
    bool angry = false;
    int targetY;
    float slope;
    float intercept;
};

class EnemyMid : public EnemyBase
{
public:
    EnemyMid();
    EnemyMid(std::vector<SDL_Texture*> textures, float X1, float Y1, float moveTo, int bulletSpeed);
    virtual ~EnemyMid();
    int isEnemyHit(std::vector<BulletPlayer*> bulletPlayer) override;
    void update(float deltaTime) override;
protected:
    const int score = 50;
    bool move = true;
    float hitTex;
    float moveTo;
};

class EnemyMidGuide : public EnemyMid
{
public:
    EnemyMidGuide();
    EnemyMidGuide(std::vector<SDL_Texture*> textures, float X1, float Y1, float moveTo, int bulletSpeed);
    virtual ~EnemyMidGuide();
    void setAngleRotation(float targetX, float targetY);
    bool shot(float deltaTime) override;
    void draw(SDL_Renderer* renderer) override;
    int playerIndex = -1;
private:
    float angleRotation = 0;
};

class EnemyBoss : public EnemyMid
{
public:
    EnemyBoss();
    EnemyBoss(std::vector<SDL_Texture*> textures, float X1, float Y1, float moveTo, int bulletSpeed);
    virtual ~EnemyBoss();
    bool shot(float deltaTime);
    void update(float deltaTime) override;
    bool isSecondPart(){return secondFase;}
    bool isSecondPartP2(){return secondFaseP2;}
    bool isThirdPart(){return thirdFase;}
protected:
    bool secondFase;
    bool secondFaseP2;
    bool thirdFase;
private:
    const int score = 2500;
    float contSecondFaseShot;
    
};

class EnemySecondBoss : public EnemyBoss
{
public:
    EnemySecondBoss();
    EnemySecondBoss(std::vector<SDL_Texture*> textures, float X1, float Y1, float moveTo, int bulletSpeed);
    virtual ~EnemySecondBoss();
    bool shot(float deltaTime);
    void update(float deltaTime) override;
    bool canSpawnEnemies() { return spawnEnemies; }
    void falseSpawnEnemies() { spawnEnemies = false; }
    bool isFirstPart() { return firstFase; }
    int numSpawnEnemies = 2;
private:
    const int score = 3500;
    bool spawnEnemies = false;
    bool firstFase = true;
    float coolDownSpawnEnemies = 30;
    float timeSecondFase = 70;
    bool reachPosition = false;
    bool direction = true;
    float reachX = 0;
    float reachY = 0;
};
