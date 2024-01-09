// Player.cpp
#include "Player.h"

Player::Player() : Object(nullptr, 0, 0)
{
}

Player::Player(SDL_Texture* texture, float X1, float Y1)
: Object(texture, X1, Y1)
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

void Player::move(SDL_Keycode key)
{
    switch (key)
    {
        case SDLK_d:
            right = true;
            break;
        case SDLK_a:
            left = true;
        break;
        case SDLK_w:
            up = true;
            break;
        case SDLK_s:
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

void Player::stop(SDL_Keycode key)
{
    switch (key)
    {
        case SDLK_d:
            right = false;
            break;
        case SDLK_a:
            left = false;
        break;
        case SDLK_w:
            up = false;
            break;
        case SDLK_s:
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
