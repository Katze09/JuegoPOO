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
    void stop();
private:
    int speed;
    int direc;
    void collisionBorder();
};

#endif // PLAYER_H
