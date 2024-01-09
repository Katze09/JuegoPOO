// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

using namespace std;

class Player : public Object 
{
public:
    Player();
    Player(SDL_Texture* texture, float X1, float Y1);
    virtual ~Player();
    void update(double deltaTime);
    void move(SDL_Keycode key);
    void stop(SDL_Keycode key);
private:
    bool up;
    bool down;
    bool right;
    bool left;
    void collisionBorder();
};

#endif // PLAYER_H
