// Player.cpp
#include "Player.h"

Player::Player() : Object(nullptr, 0, 0)
{
}

Player::Player(HBITMAP sprite, float X1, float Y1)
: Object(sprite, X1, Y1)
{
    speed = 500;
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
            direc = 0;
            break;
        case 'A':
            direc = 1;
            break;
        case 'W':
            direc = 2;
            break;
        case 'S':
            direc = 3;
            break;
            
    }
}

void Player::stop()
{
    direc = -1;
}

void Player::update(double deltaTime)
{
    this->deltaTime = deltaTime;
    switch(direc)
    {
        case 0: //Derecha
            setX(X1 + (speed * deltaTime));
            break;
        case 1: //Izquierda
            setX(X1 - (speed * deltaTime));
            break;
        case 2: //Arriba
            setY(Y1 - (speed * deltaTime));
            break;
        case 3: //Abajo
            setY(Y1 + (speed * deltaTime));
            break;
    }
}
