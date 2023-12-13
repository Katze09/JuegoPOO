// Player.cpp
#include "Player.h"

Player::Player() : Object(nullptr, 0, 0)
{
}

Player::Player(HBITMAP sprite, float X1, float Y1)
: Object(sprite, X1, Y1)
{
    speed = 500;
    up = false;
    down = false;
    right = false;
    left = false;
}

Player::~Player()
{
    // Destructor de Player
}

void Player::move(WPARAM key)
{
    switch (key)
    {
        case 'D':
            right = true;
            break;
        case 'A':
            left = true;
        break;
        case 'W':
            up = true;
            break;
        case 'S':
            down = true;
        break;
    }
}

void Player::collisionBorder()
{
    if(X1 < -20)
        Player::setX(-15);
    if(X2 >= 700)
        Player::setX(650);
    if(Y1 < -20)
        Player::setY(-20);
    if(Y2 >= 900)
        Player::setY(850);
}

void Player::stop(WPARAM key)
{
    switch (key)
    {
        case 'D':
            right = false;
            break;
        case 'A':
            left = false;
        break;
        case 'W':
            up = false;
            break;
        case 'S':
            down = false;
        break;
    }
}

void Player::update(double deltaTime)
{
    this->deltaTime = deltaTime;
    if(right)
        setX(X1 + (speed * deltaTime));
    if(left)
        setX(X1 - (speed * deltaTime));
    if(up)
        setY(Y1 - (speed * deltaTime));
    if(down)
        setY(Y1 + (speed * deltaTime));
    collisionBorder();
}
