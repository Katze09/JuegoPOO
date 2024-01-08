#include "Bullets.h"

BulletPlayer::BulletPlayer() : Object(nullptr, 0, 0)
{
}

BulletPlayer::BulletPlayer(HBITMAP sprite, float X1, float Y1) : Object(sprite, X1, Y1)
{
    speed = 1000;
}

BulletPlayer::~BulletPlayer()
{
    //Destructor
}

void BulletPlayer::update(double deltaTime)
{
    BulletPlayer::setY(Y1 - (speed * deltaTime));
}

//
//Clase Bullet Enemy
//

BulletEnemy::BulletEnemy() : Object(nullptr, 0, 0)
{
}

BulletEnemy::BulletEnemy(HBITMAP sprite, float X1, float Y1) : Object(sprite, X1, Y1)
{
    speed = 1000;
}

BulletEnemy::~BulletEnemy()
{
    //Destructor
}

void BulletEnemy::update(double deltaTime)
{
    BulletEnemy::setY(Y1 - (speed * deltaTime));
}
