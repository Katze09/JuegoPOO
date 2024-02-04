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
    void update(double deltaTime);
    void draw(SDL_Renderer* renderer);
    int isPlayerHit(vector<BulletEnemy*> bulletsEnemy);
    int isPlayerHitObstacle(vector<Obstacle*> asteroids);
    int isPlayerHitEnemy(vector<EnemyBase*> enemy);
    virtual void move(SDL_Keycode key);
    virtual void stop(SDL_Keycode key);
    bool isDead(){return dead;}
    bool isInmortal(){return inmortal;}
    void setInmortal(bool inmortal){this->inmortal = inmortal;}
    bool haveDoubleShot(){return doubleShot;}
    void setDoubleShot(bool doubleShot){this->doubleShot = doubleShot;}
    int getBulletSpeed(){return bulletSpeed;}
    void setBulletSpeed(int bulletSpeed){this->bulletSpeed = bulletSpeed;}
    int getCoolDownShot(){return coolDownShot;}
    void setCoolDownShot(int coolDownShot){this->coolDownShot = coolDownShot;}
    bool haveDoublePoints() { return doublePoints; }
    void setDoublePoints(bool doublePoints) { this->doublePoints = doublePoints; }
    int getNumSpecialAttack() { return specialAttack; }
    void reduceNumSpecialAttack() { specialAttack--; }
    void increaseNumSpecialAttack() { specialAttack++; }
    void setNumSpecialAttack(int specialAttack) { this->specialAttack = specialAttack; }
    void setSpecialAttackShot(bool specialAttackShot) { this->specialAttackShot = specialAttackShot; }
    bool haveSpecialAttackShot() { return specialAttackShot; }
    bool activePowerUps[4] = {false,false,false,false};
    double timeLeftPowerUp[4] = {3,3,3,3};
    bool flashingShield = true;
protected:
    bool up;
    bool down;
    bool right;
    bool left;
    bool dead;
    bool inmortal;
    bool doubleShot;
    bool doublePoints;
    double normalSpeedCool;
    int bulletSpeed;
    int coolDownShot;
    int specialAttack = 3;
    bool specialAttackShot = false;
    double flashingDelay = 0;
    void collisionBorder();
    void timeLetfPowerUps(double deltaTime);
    void animationBase(double deltaTime);
    void animationDead(double deltaTime);
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
