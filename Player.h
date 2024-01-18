// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"
#include "Bullets.h"

using namespace std;

class Player : public Object {
public:
    Player();
    Player(vector<SDL_Texture*> textures, float X1, float Y1);
    virtual ~Player();
    void update(double deltaTime);
    int isPlayerHit(vector<BulletEnemy*> bulletsEnemy);
    void move(SDL_Keycode key);
    void stop(SDL_Keycode key);
    bool isDead();
private:
    bool up;
    bool down;
    bool right;
    bool left;
    bool dead;
    void collisionBorder();
    void animationBase(double deltaTime);
    void animationDead(double deltaTime);
};

#endif // PLAYER_H
