#include "Bullets.h"

BulletPlayer::BulletPlayer() : Object()
{
}

BulletPlayer::BulletPlayer(SDL_Texture* texture, float X1, float Y1, bool direction, int speed) : Object(vector<SDL_Texture*>{texture}, X1, Y1)
{
    this->speed = speed;
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

BulletPlayerSpecial::BulletPlayerSpecial() : BulletPlayer()
{
}

BulletPlayerSpecial::BulletPlayerSpecial(SDL_Texture* texture, float X1, float Y1, float targetX, float targetY, int speed) : BulletPlayer(texture, X1, Y1, false, speed)
{
    dx = targetX - X1;
    dy = targetY - Y1;
    // Calcular la distancia total al objetivo
    double distance = sqrt(dx * dx + dy * dy);
    if (distance > 0)
    {
        dx /= distance;
        dy /= distance;
    }
    // Calcular el desplazamiento en cada eje
    deltaX = dx * speed * deltaTime;
    deltaY = dy * speed * deltaTime;
    double angleInRadians = atan2(deltaY, deltaX);
    angleRotation = (angleInRadians * (180.0 / M_PI));
    // Asignar las nuevas coordenadas
}

BulletPlayerSpecial::~BulletPlayerSpecial()
{
}

void BulletPlayerSpecial::update(double deltaTime)
{
    deltaX = dx * speed * deltaTime;
    deltaY = dy * speed * deltaTime;
    double angleInRadians = atan2(deltaY, deltaX);
    angleRotation = (angleInRadians * (180.0 / M_PI) - -90);
    setX(X1 + deltaX);
    setY(Y1 + deltaY);
}

void BulletPlayerSpecial::draw(SDL_Renderer* renderer)
{
    SDL_Rect destinationRect = { static_cast<int> (X1), static_cast<int> (Y1), WIDTH, HEIGHT };
    SDL_RenderCopyEx(renderer, textures[indexTexture], NULL, &destinationRect, angleRotation, NULL, SDL_FLIP_NONE);
}

//
//Clase Bullet Enemy
//

BulletEnemy::BulletEnemy() : BulletPlayer()
{
}

BulletEnemy::BulletEnemy(SDL_Texture* texture, float X1, float Y1, bool direction, int speed) : BulletPlayer(texture, X1, Y1, direction, speed)
{

}

BulletEnemy::~BulletEnemy()
{
    //Destructor
}

BulletEnemyDiagonal::BulletEnemyDiagonal() : BulletEnemy()
{
}

BulletEnemyDiagonal::BulletEnemyDiagonal(SDL_Texture* texture, float X1, float Y1, bool direction, int speed, double targetX, double targetY) : BulletEnemy(texture, X1, Y1, direction, speed)
{
    slope = static_cast<double> (targetX - X1) / (targetY - Y1);
    if (targetY < Y1)
        up = true;
    intercept = X1 - slope * Y1;
    angleRotation = 0;
    angleRotation = atan(slope);
    angleRotation = -1 * (angleRotation * 180 / M_PI);
}

BulletEnemyDiagonal::~BulletEnemyDiagonal()
{

}

void BulletEnemyDiagonal::update(double deltaTime)
{
    if (up)
    {
        setY(Y1 - (speed * deltaTime));
        setX((slope * Y1 + intercept));
    } else
    {
        setY(Y1 + (speed * deltaTime));
        setX((slope * Y1 + intercept));
    }
}

void BulletEnemyDiagonal::draw(SDL_Renderer * renderer)
{
    SDL_Rect destinationRect = {static_cast<int> (X1), static_cast<int> (Y1), WIDTH, HEIGHT};
    SDL_RenderCopyEx(renderer, textures[indexTexture], NULL, &destinationRect, angleRotation, NULL, SDL_FLIP_NONE);
}