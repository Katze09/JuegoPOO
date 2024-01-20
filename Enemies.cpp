#include <vector>

#include "Enemies.h"

EnemyBase::EnemyBase() : Object()
{
}

EnemyBase::EnemyBase(vector<SDL_Texture*> textures, float X1, float Y1, bool direction, int movimentType, int bulletSpeed) : Object(textures, X1, Y1)
{
    life = 1;
    speed = 300;
    this->bulletSpeed = bulletSpeed;
    this->direction = direction;
    coolDownShot = 3;
    this->movimentType = movimentType;
    angle = 0;
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
            setX(-60);
        }
    }
}

void EnemyBase::update(double deltaTime)
{
    switch (movimentType)
    {
        case 0:
            if (direction)
            {
                setX(X1 - (speed * deltaTime));
                collisionBorder();
            } else
            {
                setX(X1 + (speed * deltaTime));
                collisionBorder();
            }
            break;
        case 1:
            if (direction)
            {
                setY(Y1 + (4.5 * cos(angle)));
                setX(X1 + (4.5 * sin(angle)));
            } else
            {
                setY(Y1 + (4.5 * cos(angle)));
                setX(X1 - (4.5 * sin(angle)));
            }
            angle -= 0.025;
            if (angle >= 2 * M_PI)
                angle = 0.0;
            break;
    }
    /*if (direction)
    {
        setX(X1 - (speed * deltaTime));
        collisionBorder();
    } else
    {
        setX(X1 + (speed * deltaTime));
        collisionBorder();
    }*/
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
        if (indexTexture < textures.size() - 3)
            indexTexture = textures.size() - 3;
        if (speedAnimations <= 0)
        {
            indexTexture++;
            speedAnimations = 1;
        }
        if (indexTexture == textures.size() - 1)
            deadAnimationEnd = true;
    }
}

int EnemyBase::getBulletSpeed()
{
    return bulletSpeed;
}

//
// Class enemy2
//

EnemyLaser::EnemyLaser() : EnemyBase()
{
}

EnemyLaser::EnemyLaser(vector<SDL_Texture*> textures, float X1, float Y1, bool direction, int movimentType, double moveTo, int bulletSpeed) : EnemyBase(textures, X1, Y1, direction, movimentType, bulletSpeed)
{
    this->moveTo = moveTo;
    firstShot = true;
    laserSize = 0;
}

EnemyLaser::~EnemyLaser()
{
}

bool EnemyLaser::shot(double deltaTime)
{
    if (laserSize >= 150)
    {
        laserSize = 0;
        coolDownShot = 8;
        firstShot = true;
    }
    coolDownShot -= 3 * deltaTime;
    if (coolDownShot <= 0)
    {
        coolDownShot = 0;
        laserSize++;
        return true;
    }
    return false;
}

void EnemyLaser::update(double deltaTime)
{
    if (direction)
    {
        if (X1 >= moveTo)
            setX(X1 - (speed * deltaTime));
        collisionBorder();
    } else
    {
        if (X1 <= moveTo)
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

EnemyMid::EnemyMid() : EnemyBase()
{
}

EnemyMid::EnemyMid(vector<SDL_Texture*> textures, float X1, float Y1, double moveTo, int bulletSpeed) : EnemyBase(textures, X1, Y1, false, 0, bulletSpeed)
{
    life = 20;
    hitTex = 0;
    this->moveTo = moveTo;
}

EnemyMid::~EnemyMid()
{
}

int EnemyMid::isEnemyHit(vector<BulletPlayer*> bulletPlayer)
{
    for (int i = 0; i < bulletPlayer.size(); i++)
        if (bulletPlayer[i]->getX1HitBox() < X2HitBox && bulletPlayer[i]->getX2HitBox() > X1HitBox &&
                bulletPlayer[i]->getY1HitBox() < Y2HitBox && bulletPlayer[i]->getY2HitBox() > Y1HitBox)
        {
            life--;
            indexTexture = 1;
            hitTex = 1;
            isDead();
            return i;
        }
    return -1;
}

void EnemyMid::update(double deltaTime)
{
    if (Y1 <= moveTo)
        setY(Y1 + (speed * deltaTime));
    else
    {
        if (direction)
        {
            setX(X1 + (speed * deltaTime));
            if (X1 >= 550)
                direction = false;
        } else
        {
            setX(X1 - (speed * deltaTime));
            if (X1 <= 0)
                direction = true;
        }
    }
    if (indexTexture == 1 && hitTex <= 0)
        indexTexture = 0;
    if (hitTex > 0)
        hitTex -= 15 * deltaTime;
    animationDead(deltaTime);
}
