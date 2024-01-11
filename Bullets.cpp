#include "Bullets.h"

BulletPlayer::BulletPlayer() : Object()
{
}

BulletPlayer::BulletPlayer(SDL_Texture* texture, float X1, float Y1, bool direction) : Object(vector<SDL_Texture*>{texture}, X1, Y1)
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
    if (direction)
        BulletPlayer::setY(Y1 - (speed * deltaTime));
    else
        BulletPlayer::setY(Y1 + (speed * deltaTime));
}

void BulletPlayer::animationBase(double deltaTime)
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

void BulletPlayer::animationDead(double deltaTime)
{
    
}

//
//Clase Bullet Enemy
//

BulletEnemy::BulletEnemy() : BulletPlayer()
{
}

BulletEnemy::BulletEnemy(SDL_Texture* texture, float X1, float Y1, bool direction, int speed) : BulletPlayer(texture, X1, Y1, direction)
{
    this->speed = speed;
}

BulletEnemy::~BulletEnemy()
{
    //Destructor
}
