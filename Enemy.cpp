#include <vector>

#include "Enemy.h"

Enemy::Enemy() : Object(nullptr, 0, 0)
{
}

Enemy::Enemy(HBITMAP sprite, float X1, float Y1) : Object(sprite, X1, Y1)
{
}

Enemy::~Enemy()
{
}

bool Enemy::isEnemyHit()
{
    for(int i = 0;i < bulletPlayer.size();i++)
        if(X1HitBox > bulletPlayer[i].getX1HitBox() && X2HitBox < bulletPlayer[i].getX2HitBox() && Y1HitBox > bulletPlayer[i].getY1HitBox() && Y2HitBox < bulletPlayer[i].getY2HitBox())
            return true;
    return false;
}

bool Enemy::animationDestroy()
{
    
}

void Enemy::update(double deltaTime, vector<BulletPlayer> bulletPlayer)
{
    this->bulletPlayer = bulletPlayer;
    if(isEnemyHit())
        cout << "Impacto" << endl;
}

void Enemy::update(double deltaTime){}
