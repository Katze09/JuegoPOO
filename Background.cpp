#include "Background.h"

Background::Background()
{
}

Background::Background(SDL_Texture* texture)
{
    this->texture = texture;
    SDL_QueryTexture(texture, NULL, NULL, &WIDTH, &HEIGHT);
    X = 0;
    Y1 = 0;
    Y2 = -950;
    speed = 2;
}

Background::~Background()
{
}

void Background::update(double deltaTime)
{
    Y1 += speed; //* deltaTime;
    Y2 += speed; //* deltaTime;
    if (Y1 > 950)
        Y1 = -950;
    if (Y2 > 950)
        Y2 = -950;
}

void Background::draw(SDL_Renderer* renderer)
{
    SDL_Rect destRect = {static_cast<int> (X), static_cast<int> (Y1), WIDTH, HEIGHT};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    destRect = {static_cast<int> (X), static_cast<int> (Y2), WIDTH, HEIGHT};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}