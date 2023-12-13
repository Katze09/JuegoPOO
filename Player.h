// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

using namespace std;

class Player : public Object 
{
public:
    Player();
    Player(HBITMAP sprite, float X1, float Y1);
    virtual ~Player();
    void update(double deltaTime);
    void move(WPARAM key);
    void stop(WPARAM key);
private:
    int speed;
    bool up;
    bool down;
    bool right;
    bool left;
    //int direc;
    void collisionBorder();
};

#endif // PLAYER_H
