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
    if(direc != -1)
    {
        if((direc == 0 && key == 'W') || (direc == 2 && key == 'D'))
            direc = 4;
        if((direc == 1 && key == 'W') || (direc == 2 && key == 'A'))
            direc = 5;
        if((direc == 0 && key == 'S') || (direc == 3 && key == 'D'))
            direc = 6;
        if((direc == 1 && key == 'S') || (direc == 3 && key == 'A'))
            direc = 7;
    }else
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
        case 4: //Derecha arriba
            setY(Y1 - (speed * deltaTime));
            setX(X1 + (speed * deltaTime));
            break;
        case 5: //Izquierda arriba
            setY(Y1 - (speed * deltaTime));
            setX(X1 - (speed * deltaTime));
            break;
        case 6: //Derecha abajo
            setY(Y1 + (speed * deltaTime));
            setX(X1 + (speed * deltaTime));
            break;
        case 7: //Izquierda abajo
            setY(Y1 + (speed * deltaTime));
            setX(X1 - (speed * deltaTime));
            break;
    }
}
