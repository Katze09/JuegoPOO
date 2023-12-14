#include <vector>

#include "Enemy.h"

Enemy::Enemy() : Object(nullptr, 0, 0)
{
}

Enemy::Enemy(HBITMAP sprite, float X1, float Y1) : Object(sprite, X1, Y1)
{
    life = 1;
    speed = 300;
}

Enemy::~Enemy()
{
}

int Enemy::isEnemyHit(vector<BulletPlayer> bulletPlayer)
{
    for(int i = 0;i < bulletPlayer.size();i++)
        if(bulletPlayer[i].getX1HitBox() >= X1HitBox && bulletPlayer[i].getX2HitBox() <= X2HitBox && bulletPlayer[i].getY1HitBox() >= Y1HitBox && bulletPlayer[i].getY2HitBox() <= Y2HitBox)
        {
            life--;
            return i;
        }
    return -1;
}

bool Enemy::isDead()
{
    return life <= 0;
}

void Enemy::collisionBorder()
{
    if(X1 <= -50)
        setX(710);
}

bool Enemy::animationDestroy()
{
    
}

void Enemy::update(double deltaTime)
{
    //if(isEnemyHit())
      //  life--;
    setX(X1 - (speed * deltaTime));
    collisionBorder();
}
