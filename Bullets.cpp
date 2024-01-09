#include "Bullets.h"

BulletPlayer::BulletPlayer() : Object(nullptr, 0, 0)
{
}

BulletPlayer::BulletPlayer(SDL_Texture* texture, float X1, float Y1, bool direction) : Object(texture, X1, Y1)
{
    speed = 1000;
    this->direction = direction;
}

BulletPlayer::~BulletPlayer()
{
    //Destructor
}

void BulletPlayer::update(double deltaTime)
{
    if(direction)
        BulletPlayer::setY(Y1 - (speed * deltaTime));
    else
        BulletPlayer::setY(Y1 + (speed * deltaTime));
}

//
//Clase Bullet Enemy
//

BulletEnemy::BulletEnemy() : BulletPlayer(nullptr, 0, 0, false)
{
}

BulletEnemy::BulletEnemy(SDL_Texture* texture, float X1, float Y1, bool direction) : BulletPlayer(texture, X1, Y1, direction)
{
    speed = 1000;
}

BulletEnemy::~BulletEnemy()
{
    //Destructor
}
