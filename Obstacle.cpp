/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Obstacle.cpp
 * Author: Katze
 * 
 * Created on 11 de enero de 2024, 23:49
 */

#include "Obstacle.h"

Loader loaderAste;

Obstacle::Obstacle()
{
}

Obstacle::Obstacle(vector<SDL_Texture*> textures, float X1, float Y1) : Object(textures, X1, Y1)
{
    targetY = loaderAste.randomNumber(50, 700);
    while (Y1 >= targetY && Y1 <= targetY + 100)
        targetY = loaderAste.randomNumber(50, 700);
    slope = static_cast<double> (targetY - Y1) / (X1 - 100);
    intercept = Y1 - slope * X1;
    life = angleRotation = 0;
}

Obstacle::Obstacle(vector<SDL_Texture*> textures) : Object(textures)
{
    direction = loaderAste.randomNumber(0, 1);
    X1 = (direction) ? 800 : -100;
    Y1 = loaderAste.randomNumber(100, 700);
    if (Y1 < 450)
        targetY = loaderAste.randomNumber(Y1, 700);
    else
        targetY = loaderAste.randomNumber(0, Y1);
    X2 = X1 + WIDTH;
    Y2 = Y1 + HEIGHT;
    X1HitBox = X1 + (WIDTH * 0.1);
    X2HitBox = X2 - (WIDTH * 0.1);
    Y1HitBox = Y1 + (HEIGHT * 0.1);
    Y2HitBox = Y2 - (HEIGHT * 0.1);

    // Establecer la pendiente y la intersección
    int xObj = (direction) ? 0 : 700;
    slope = static_cast<double> (targetY - Y1) / (xObj - X1);
    intercept = Y1 - slope * X1;

    life = angleRotation = 0;
    score = 5;
}

Obstacle::~Obstacle()
{
}

void Obstacle::update(double deltaTime)
{
    // Actualizar la posición X e Y basada en la pendiente y velocidad
    setX(X1 + (speed * (15 * deltaTime)));
    setY((slope * X1 + intercept) + (15 * deltaTime));
    animationDead(deltaTime);
}

bool Obstacle::isCollsionBorder()
{
    bool border = false;
    if (direction)
    {
        if (X1 < -150)
        {
            border = true;
        }
    } else
    {
        if (X1 > 850)
        {
            border = true;
        }
    }
    return border;
}

bool Obstacle::isDead()
{
    if (life <= 0 && !dead)
    {
        dead = true;
        speedAnimations = 0;
    }
    return dead;
}

void Obstacle::reduceLife()
{
    life--;
    isDead();
}

int Obstacle::isObstacleHit(vector<BulletPlayer*> bulletPlayer)
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

void Obstacle::animationBase(double deltaTime)
{
    //SDL_Rect destinationRect = {100, 100, 200, 150}; // Posición y tamaño del rectángulo de destino
}

void Obstacle::animationDead(double deltaTime)
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

int Obstacle::getScore()
{
    return score;
}

void Obstacle::draw(SDL_Renderer * renderer)
{
    // Renderizar con rotación
    SDL_Rect destinationRect = {static_cast<int> (X1), static_cast<int> (Y1), WIDTH, HEIGHT};
    SDL_RenderCopyEx(renderer, textures[indexTexture], NULL, &destinationRect, angleRotation, NULL, SDL_FLIP_NONE);

    // Renderizar sin rotación
    //SDL_Rect destRect = {static_cast<int> (X1), static_cast<int> (Y1), WIDTH, HEIGHT};
    //SDL_RenderCopy(renderer, textures[indexTexture], NULL, &destRect);

    // Actualizar el ángulo de rotación
    if (angleRotation >= 360)
        angleRotation = 0;
    angleRotation += 3;
}

Asteroid::Asteroid() : Obstacle()
{
}

Asteroid::Asteroid(vector<SDL_Texture*> textures, float X1, float Y1) : Obstacle(textures, X1, Y1)
{
    this->speed = 20;
}

Asteroid::Asteroid(vector<SDL_Texture*> textures) : Obstacle(textures)
{
    this->speed = 20;
}

Asteroid::~Asteroid()
{
}

PowerUp::PowerUp() : Obstacle()
{
}

PowerUp::PowerUp(vector<SDL_Texture*> textures, int type) : Obstacle(textures)
{
    this->type = type;
    this->speed = 10;
}

PowerUp::PowerUp(vector<SDL_Texture*> textures, float X1, float Y1, int type) : Obstacle(textures, X1, Y1)
{
    this->type = type;
    X1HitBox = X1 - (WIDTH * 0.3);
    X2HitBox = X2 + (WIDTH * 0.3);
    Y1HitBox = Y1 - (HEIGHT * 0.3);
    Y2HitBox = Y2 + (HEIGHT * 0.3);
}

PowerUp::~PowerUp()
{
}

bool PowerUp::isCollisionPlayer(Player* player)
{
    return player->getX1HitBox() < X2HitBox && player->getX2HitBox() > X1HitBox &&
            player->getY1HitBox() < Y2HitBox && player->getY2HitBox() > Y1HitBox;
}

void PowerUp::setPowerEffect(Player* player)
{
    switch (type)
    {
        case 0:
            player->setCoolDownShot(0.6);
            player->activePowerUps[0] = true;
            player->timeLeftPowerUp[0] = 50;
            break;
        case 1:
            player->setInmortal(true);
            player->activePowerUps[1] = true;
            player->timeLeftPowerUp[1] = 50;
            break;
        case 2:
            player->setDoubleScore(true);
            player->activePowerUps[2] = true;
            player->timeLeftPowerUp[2] = 50;
            break;
    }
}

