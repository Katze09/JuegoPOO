#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <iostream>
#include <sdl.h>

class Background 
{
public:
    Background();
    Background(SDL_Texture* texture);
    virtual ~Background();
    void update(float deltaTime);
    void draw(SDL_Renderer* renderer);
private:
    SDL_Texture* texture;
    int X;
    int Y1;
    int Y2;
    int WIDTH;
    int HEIGHT;
    int speed;
};

#endif /* BACKGROUND_H */

