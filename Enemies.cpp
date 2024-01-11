#include <vector>

#include "Enemies.h"

EnemyBase::EnemyBase() : Object()
{
}

EnemyBase::EnemyBase(vector<SDL_Texture*> textures, float X1, float Y1, bool direction) : Object(textures, X1, Y1)
{
    life = 1;
    speed = 300;
    this->direction = direction;
    coolDownShot = 3;
}

EnemyBase::~EnemyBase()
{
}

int EnemyBase::isEnemyHit(vector<BulletPlayer*> bulletPlayer)
{
    for (int i = 0; i < bulletPlayer.size(); i++)
        if (bulletPlayer[i]->getX1HitBox() < X2HitBox && bulletPlayer[i]->getX2HitBox() > X1HitBox &&
                bulletPlayer[i]->getY1HitBox() < Y2HitBox && bulletPlayer[i]->getY2HitBox() > Y1HitBox)
        {
            life--;
            isDead();
            return i;
        }
    return -1;
}

bool EnemyBase::isDead()
{
    if (life <= 0 && !dead)
    {
        dead = true;
        speedAnimations = 0;
    }
    return dead;
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
    animationDead(deltaTime);
}

bool EnemyBase::shot(double deltaTime)
{
    coolDownShot -= 3 * deltaTime;
    if (coolDownShot <= 0)
    {
        coolDownShot = 3;
        return true;
    }
    return false;
}

void EnemyBase::animationBase(double deltaTime)
{
    /*speedAnimations -= speedAnimations * deltaTime;
    if(speedAnimations <= 0)
    {
        indexTexture++;
        speedAnimations = 1;
    }
    if(indexTexture == 3)
        indexTexture = 0;*/
}

void EnemyBase::animationDead(double deltaTime)
{
    if (dead && !deadAnimationEnd)
    {
        speedAnimations -= 15 * deltaTime;
        if (speedAnimations <= 0)
        {
            if(indexTexture < 1)
                indexTexture = 0;
            indexTexture++;
            speedAnimations = 1;
        }
        if (indexTexture == 3)
            deadAnimationEnd = true;
    }
}

//
// Class enemy2
//

EnemyLaser::EnemyLaser() : EnemyBase()
{
}

EnemyLaser::EnemyLaser(vector<SDL_Texture*> textures, float X1, float Y1, bool direction) : EnemyBase(textures, X1, Y1, direction)
{
    firstShot = true;
}

EnemyLaser::~EnemyLaser()
{
}

bool EnemyLaser::shot(double deltaTime)
{
    coolDownShot -= 3 * deltaTime;
    if (coolDownShot <= 0)
    {
        coolDownShot = 0;
        return true;
    }
    return false;
}

void EnemyLaser::update(double deltaTime)
{
    if (direction)
    {
        if (X1 >= 550)
            setX(X1 - (speed * deltaTime));
        collisionBorder();
    } else
    {
        if (X1 <= 150)
            setX(X1 + (speed * deltaTime));
        collisionBorder();
    }
    animationDead(deltaTime);
}

bool EnemyLaser::isFirstShot()
{
    return firstShot;
}

void EnemyLaser::setFirstShot()
{
    firstShot = false;
}