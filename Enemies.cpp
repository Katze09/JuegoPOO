#include <vector>

#include "Enemies.h"

EnemyBase::EnemyBase() : Object(nullptr, 0, 0)
{
}

EnemyBase::EnemyBase(HBITMAP sprite, float X1, float Y1, bool direction) : Object(sprite, X1, Y1)
{
    life = 1;
    speed = 300;
    this->direction = direction;
}

EnemyBase::~EnemyBase()
{
}

int EnemyBase::isEnemyHit(vector<BulletPlayer> bulletPlayer)
{
    for (int i = 0; i < bulletPlayer.size(); i++)
        if (bulletPlayer[i].getX1HitBox() < X2HitBox && bulletPlayer[i].getX2HitBox() > X1HitBox &&
                bulletPlayer[i].getY1HitBox() < Y2HitBox && bulletPlayer[i].getY2HitBox() > Y1HitBox)
        {
            life--;
            return i;
        }
    return -1;
}

bool EnemyBase::isDead()
{
    return life <= 0;
}

void EnemyBase::collisionBorder()
{
    if (direction)
    {
        if (X1 <= -50)
        {
            setX(710);
        }
    } else
    {
        if (X1 >= 750)
        {
            setX(-50);
        }
    }
}

bool EnemyBase::animationDestroy()
{

}

void EnemyBase::update(double deltaTime)
{
    //if(isEnemyHit())
    //  life--;
    if (direction)
    {
        setX(X1 - (speed * deltaTime));
        collisionBorder();
    } else
    {
        setX(X1 + (speed * deltaTime));
        collisionBorder();
    }
}

//
// Class enemy2
//

EnemyLaser::EnemyLaser() : EnemyBase(nullptr, 0, 0, false)
{
}

EnemyLaser::EnemyLaser(HBITMAP sprite, float X1, float Y1, bool direction) : EnemyBase(sprite, X1, Y1, direction)
{
}

EnemyLaser::~EnemyLaser()
{
}

void EnemyLaser::update(double deltaTime)
{

}