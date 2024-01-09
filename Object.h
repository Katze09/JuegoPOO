#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <sdl.h>

using namespace std;

class Object 
{
public:
    Object(SDL_Texture* texture, float X1, float Y1);
    virtual ~Object();

    SDL_Texture* getTexture();
    float getX1();
    float getX2();
    float getY1();
    float getY2();
    float getX1HitBox();
    float getX2HitBox();
    float getY1HitBox();
    float getY2HitBox(); 
    int getWIDTH();
    int getHEIGHT();
    int getSpeed();

    void setSprite(SDL_Texture* texture);
    void setX(float X);
    void setY(float Y);
    void setSpeed(int speed);
    
    void draw(SDL_Renderer* renderer);
    virtual void update(double deltaTime) = 0;

protected:
    SDL_Texture* texture;
    float X1;
    float X2;
    float Y1;
    float Y2;
    float X1HitBox;
    float X2HitBox;
    float Y1HitBox;
    float Y2HitBox; 
    int WIDTH;
    int HEIGHT;
    double deltaTime;
    int speed;
};

#endif /* OBJECT_H */
