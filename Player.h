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
    bool haveDoubleShot(){return doubleShot;}
    void setDoubleShot(bool floatShot){this->doubleShot = floatShot;}
    int getBulletSpeed(){return bulletSpeed;}
    void setBulletSpeed(int bulletSpeed){this->bulletSpeed = bulletSpeed;}
    int getCoolDownShot(){return coolDownShot;}
    void setCoolDownShot(int coolDownShot){this->coolDownShot = coolDownShot;}
    bool haveDoublePoints() { return doublePoints; }
    void setDoublePoints(bool floatPoints) { this->doublePoints = doublePoints; }
    int getNumSpecialAttack() { return specialAttack; }
    void reduceNumSpecialAttack() { specialAttack--; }
    void increaseNumSpecialAttack() { specialAttack++; }
    void setNumSpecialAttack(int specialAttack) { this->specialAttack = specialAttack; }
    void setSpecialAttackShot(bool specialAttackShot) { this->specialAttackShot = specialAttackShot; }
    bool haveSpecialAttackShot() { return specialAttackShot; }
    bool haveItemDoubleShot() { return doubleShotItem; }
    bool haveItemDoublePoints() { return doublePointsItem; }
    bool haveItemPowerShopItem() { return powerUpShotItem; }
    void setItemDoubleShot(bool doubleShotItem) { this->doubleShotItem = doubleShotItem; }
    void setItemDoublePoints(bool doublePointsItem) { this->doublePointsItem = doublePointsItem; }
    void setItemPowerShopItem(bool powerUpShotItem) { this->powerUpShotItem = powerUpShotItem; coolDownShot = 2; }
    void setItemEffect(int type);
    int getNumItemShield() { return itemShield; }
    void reduceNumItemShield() { itemShield--; }
    void setNumItemShield(int itemShield) { this->itemShield = itemShield; }
    void kill(){ dead = true; speedAnimations = 1; }
    void setDirecionJoy(int direction);
    bool activePowerUps[4] = {false,false,false,false};
    float timeLeftPowerUp[4] = {3,3,3,3};
    bool flashingShield = true;
protected:
    bool up;
    bool down;
    bool right;
    bool left;
    bool dead;
    bool inmortal = false;
    bool doubleShot = false;
    bool doublePoints = false;
    bool doubleShotItem = false;
    bool doublePointsItem = false;
    bool powerUpShotItem = false;
    float normalSpeedCool;
    int bulletSpeed;
    int coolDownShot;
    int specialAttack = 3;
    bool specialAttackShot = false;
    int itemShield = 0;
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
