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
    Player(vector<SDL_Texture*> textures, float X1, float Y1, bool player1);
    virtual ~Player();
    void update(double deltaTime);
    void draw(SDL_Renderer* renderer);
    int isPlayerHit(vector<BulletEnemy*> bulletsEnemy);
    int isPlayerHitObstacle(vector<Obstacle*> asteroids);
    void move(SDL_Keycode key);
    void stop(SDL_Keycode key);
    bool isDead();
    bool isInmortal();
    void setInmortal(bool inmortal);
    bool haveDoubleShot();
    void setDoubleShot(bool doubleShot);
    int getBulletSpeed();
    void setBulletSpeed(int bulletSpeed);
    int getCoolDownShot();
    void setCoolDownShot(int coolDownShot);
    bool activePowerUps[3];
    double timeLeftPowerUp[3];
private:
    bool up;
    bool down;
    bool right;
    bool left;
    bool dead;
    bool inmortal;
    bool doubleShot;
    double normalSpeedCool;
    int bulletSpeed;
    int coolDownShot;
    bool player1;
    void collisionBorder();
    void timeLetfPowerUps(double deltaTime);
    void animationBase(double deltaTime);
    void animationDead(double deltaTime);
};

#endif // PLAYER_H
