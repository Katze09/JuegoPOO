#include "Object.h"

Object::Object(SDL_Texture* texture, float X1, float Y1) : texture(texture), X1(X1), Y1(Y1)
{
    SDL_QueryTexture(texture, NULL, NULL, &WIDTH, &HEIGHT);
    X2 = X1 + WIDTH;
    Y2 = Y1 + HEIGHT;
    X1HitBox = X1 + (WIDTH * 0.1);
    X2HitBox = X2 - (WIDTH * 0.1);
    Y1HitBox = Y1 + (HEIGHT * 0.1);
    Y2HitBox = Y2 - (HEIGHT * 0.1);
}

Object::~Object()
{
    // Destructor
}

SDL_Texture* Object::getTexture()
{
    return texture;
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

void Object::setSprite(SDL_Texture* texture)
{
    this->texture = texture;
}

void Object::setX(float X)
{
    X1 = X;
    X2 = X1 + WIDTH;
    X1HitBox = X1 + (WIDTH * 0.1);
    X2HitBox = X2 - (WIDTH * 0.1);
}

void Object::setY(float Y)
{
    Y1 = Y;
    Y2 = Y1 + HEIGHT;
    Y1HitBox = Y1 + (HEIGHT * 0.1);
    Y2HitBox = Y2 - (HEIGHT * 0.1);
}

void Object::setSpeed(int speed)
{
    this->speed = speed;
}

void Object::draw(SDL_Renderer* renderer)
{
    SDL_Rect destRect = {static_cast<int> (X1), static_cast<int> (Y1), WIDTH, HEIGHT};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}