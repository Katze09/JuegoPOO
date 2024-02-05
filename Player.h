// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"
#include "Bullets.h"
#include "Obstacle.h"
#include "Enemies.h"

using namespace std;

class Player : public Object {
public:
    Player();
    Player(vector<SDL_Texture*> textures, float X1, float Y1);
    virtual ~Player();
    void update(float deltaTime);
    void draw(SDL_Renderer* renderer);
    int isPlayerHit(vector<BulletEnemy*> bulletsEnemy);
    int isPlayerHitObstacle(vector<Obstacle*> asteroids);
    int isPlayerHitEnemy(vector<EnemyBase*> enemy);
    virtual void move(SDL_Keycode key);
    virtual void stop(SDL_Keycode key);
    bool isDead(){return dead;}
    bool isInmortal(){return inmortal;}
    void setInmortal(bool inmortal){this->inmortal = inmortal;}
    bool havefloatShot(){return floatShot;}
    void setfloatShot(bool floatShot){this->floatShot = floatShot;}
    int getBulletSpeed(){return bulletSpeed;}
    void setBulletSpeed(int bulletSpeed){this->bulletSpeed = bulletSpeed;}
    int getCoolDownShot(){return coolDownShot;}
    void setCoolDownShot(int coolDownShot){this->coolDownShot = coolDownShot;}
    bool havefloatPoints() { return floatPoints; }
    void setfloatPoints(bool floatPoints) { this->floatPoints = floatPoints; }
    int getNumSpecialAttack() { return specialAttack; }
    void reduceNumSpecialAttack() { specialAttack--; }
    void increaseNumSpecialAttack() { specialAttack++; }
    void setNumSpecialAttack(int specialAttack) { this->specialAttack = specialAttack; }
    void setSpecialAttackShot(bool specialAttackShot) { this->specialAttackShot = specialAttackShot; }
    bool haveSpecialAttackShot() { return specialAttackShot; }
    void kill(){ dead = true; speedAnimations = 1; }
    bool activePowerUps[4] = {false,false,false,false};
    float timeLeftPowerUp[4] = {3,3,3,3};
    bool flashingShield = true;
protected:
    bool up;
    bool down;
    bool right;
    bool left;
    bool dead;
    bool inmortal;
    bool floatShot;
    bool floatPoints;
    float normalSpeedCool;
    int bulletSpeed;
    int coolDownShot;
    int specialAttack = 3;
    bool specialAttackShot = false;
    float flashingDelay = 0;
    void collisionBorder();
    void timeLetfPowerUps(float deltaTime);
    void animationBase(float deltaTime);
    void animationDead(float deltaTime);
};

class Player2 : public Player
{
public:
    Player2();
    Player2(vector<SDL_Texture*> textures, float X1, float Y1);
    virtual ~Player2();
    void move(SDL_Keycode key) override;
    void stop(SDL_Keycode key) override;
};

#endif // PLAYER_H
