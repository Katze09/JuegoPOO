// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"
#include "Bullets.h"
#include "Obstacle.h"

using namespace std;

class Player : public Object {
public:
    Player();
    Player(vector<SDL_Texture*> textures, float X1, float Y1);
    virtual ~Player();
    void update(double deltaTime);
    int isPlayerHit(vector<BulletEnemy*> bulletsEnemy);
    int isPlayerHitObstacle(vector<Obstacle*> asteroids);
    void move(SDL_Keycode key);
    void stop(SDL_Keycode key);
    bool isDead();
    bool isInmortal();
    void setInmortal(bool inmortal);
    int getBulletSpeed();
    void setBulletSpeed(int bulletSpeed);
    int getCoolDownShot();
    void setCoolDownShot(int coolDownShot);
    bool activePowerUps[2];
    double timeLeftPowerUp[2];
private:
    bool up;
    bool down;
    bool right;
    bool left;
    bool dead;
    bool inmortal;
    double normalSpeedCool;
    int bulletSpeed;
    int coolDownShot;
    void collisionBorder();
    void timeLetfPowerUps(double deltaTime);
    void animationBase(double deltaTime);
    void animationDead(double deltaTime);
};

#endif // PLAYER_H
