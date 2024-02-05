#include "Object.h"

Object::Object()
{
}

Object::Object(vector<SDL_Texture*> textures)
{
    this->textures = textures;
    SDL_QueryTexture(textures[0], NULL, NULL, &WIDTH, &HEIGHT);
    indexTexture = 0;
    speedAnimations = 1;
    hitBoxMultiplication = 0.1;
    dead = false;
    deadAnimationEnd = false;
}

Object::Object(vector<SDL_Texture*> textures, float X1, float Y1) : X1(X1), Y1(Y1)
{
    this->textures = textures;
    SDL_QueryTexture(textures[0], NULL, NULL, &WIDTH, &HEIGHT);
    X2 = X1 + WIDTH;
    Y2 = Y1 + HEIGHT;
    hitBoxMultiplication = 0.1;
    X1HitBox = X1 + (WIDTH * hitBoxMultiplication);
    X2HitBox = X2 - (WIDTH * hitBoxMultiplication);
    Y1HitBox = Y1 + (HEIGHT * hitBoxMultiplication);
    Y2HitBox = Y2 - (HEIGHT * hitBoxMultiplication);
    indexTexture = 0;
    speedAnimations = 1;
    dead = false;
    deadAnimationEnd = false;
}

Object::~Object()
{
    for (auto& texture : textures)
        SDL_DestroyTexture(texture);
}

SDL_Texture* Object::getTexture(int index)
{
    return textures[index];
}

float Object::getX1()
{
    return X1;
}

float Object::getX2()
{
    return X2;
}

float Object::getY1()
{
    return Y1;
}

float Object::getY2()
{
    return Y2;
}

float Object::getX1HitBox()
{
    return X1HitBox;
}

float Object::getX2HitBox()
{
    return X2HitBox;
}

float Object::getY1HitBox()
{
    return Y1HitBox;
}

float Object::getY2HitBox()
{
    return Y2HitBox;
}

int Object::getWIDTH()
{
    return WIDTH;
}

int Object::getHEIGHT()
{
    return HEIGHT;
}

int Object::getSpeed()
{
    return speed;
}

float Object::getSpeedAnimations()
{
    return speedAnimations;
}

bool Object::isDead()
{
    return dead;
}

bool Object::endDeadAnimation()
{
    return deadAnimationEnd;
}

void Object::setSpeedAnimations(float speedAnimations)
{
    this->speedAnimations = speedAnimations;
}

void Object::setSprite(vector<SDL_Texture*> textures)
{
    this->textures = textures;
}

void Object::setSprite(SDL_Texture* texture, int index)
{
    this->textures[index] = texture;
}

void Object::setX(float X)
{
    X1 = X;
    X2 = X1 + WIDTH;
    X1HitBox = X1 + (WIDTH * hitBoxMultiplication);
    X2HitBox = X2 - (WIDTH * hitBoxMultiplication);
}

void Object::setY(float Y)
{
    Y1 = Y;
    Y2 = Y1 + HEIGHT;
    Y1HitBox = Y1 + (HEIGHT * hitBoxMultiplication);
    Y2HitBox = Y2 - (HEIGHT * hitBoxMultiplication);
}

void Object::setSpeed(float speed)
{
    this->speed = speed;
}

void Object::draw(SDL_Renderer* renderer)
{
    SDL_Rect destRect = {static_cast<int> (X1), static_cast<int> (Y1), WIDTH, HEIGHT};
    SDL_RenderCopy(renderer, textures[indexTexture], NULL, &destRect);
}