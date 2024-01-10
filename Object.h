#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <tchar.h>
#include <cstdlib>
#include <vector>
#include <sdl.h>

using namespace std;

class Object 
{
public:
    Object();
    Object(vector<SDL_Texture*> textures, float X1, float Y1);
    virtual ~Object();

    SDL_Texture* getTexture(int index);
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
    double getSpeedAnimations();
    bool isDead();
    bool endDeadAnimation();

    void setSprite(vector<SDL_Texture*> textures);
    void setSprite(SDL_Texture* texture, int index);
    void setX(float X);
    void setY(float Y);
    void setSpeed(int speed);
    void setSpeedAnimations(double speedAnimations);
    void setDead();
    
    
    virtual void animationBase(double deltaTime) = 0;
    virtual void animationDead(double deltaTime) = 0;
    void draw(SDL_Renderer* renderer);
    virtual void update(double deltaTime) = 0;

protected:
    std::vector<SDL_Texture*> textures;
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
    double speedAnimations;
    int indexTexture;
    bool dead;
    bool deadAnimationEnd;
};

#endif /* OBJECT_H */
