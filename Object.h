#pragma once

#include <iostream>
#include <tchar.h>
#include <cstdlib>
#include <vector>
#include <sdl.h>
#include <sstream>
#include <string>

using namespace std;

class Object 
{
public:
    Object();
    Object(std::vector<SDL_Texture*> textures);
    Object(std::vector<SDL_Texture*> textures, float X1, float Y1);
    virtual ~Object();

    std::vector<SDL_Texture*> getTextures() { return textures; }
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
    float getSpeedAnimations();
    virtual bool isDead();
    bool endDeadAnimation();

    void setSprite(std::vector<SDL_Texture*> textures);
    void setSprite(SDL_Texture* texture, int index);
    void setX(float X);
    void setY(float Y);
    void setSpeed(float speed);
    void setSpeedAnimations(float speedAnimations);
    
    
    virtual void animationBase(float deltaTime) = 0;
    virtual void animationDead(float deltaTime) = 0;
    virtual void draw(SDL_Renderer* renderer);
    virtual void update(float deltaTime) = 0;

    virtual std::string serialize();
    virtual void deserialize(std::string& data);

protected:
    std::vector<SDL_Texture*> textures;
    float X1;
    float X2;
    float Y1;
    float Y2;
    float hitBoxMultiplication;
    float X1HitBox;
    float X2HitBox;
    float Y1HitBox;
    float Y2HitBox; 
    int WIDTH;
    int HEIGHT;
    float speed;
    float speedAnimations;
    int indexTexture;
    bool dead;
    bool deadAnimationEnd;
};
