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
    Object(vector<SDL_Texture*> textures);
    Object(vector<SDL_Texture*> textures, float X1, float Y1);
    virtual ~Object();

    vector<SDL_Texture*> getTextures() { return textures; }
    SDL_Texture* getTexture(int index);
    double getX1();
    double getX2();
    double getY1();
    double getY2();
    double getX1HitBox();
    double getX2HitBox();
    double getY1HitBox();
    double getY2HitBox(); 
    int getWIDTH();
    int getHEIGHT();
    int getSpeed();
    double getSpeedAnimations();
    virtual bool isDead();
    bool endDeadAnimation();

    void setSprite(vector<SDL_Texture*> textures);
    void setSprite(SDL_Texture* texture, int index);
    void setX(double X);
    void setY(double Y);
    void setSpeed(double speed);
    void setSpeedAnimations(double speedAnimations);
    void setDead();
    
    
    virtual void animationBase(double deltaTime) = 0;
    virtual void animationDead(double deltaTime) = 0;
    virtual void draw(SDL_Renderer* renderer);
    virtual void update(double deltaTime) = 0;

protected:
    std::vector<SDL_Texture*> textures;
    double X1;
    double X2;
    double Y1;
    double Y2;
    double hitBoxMultiplication;
    double X1HitBox;
    double X2HitBox;
    double Y1HitBox;
    double Y2HitBox; 
    int WIDTH;
    int HEIGHT;
    double deltaTime;
    double speed;
    double speedAnimations;
    int indexTexture;
    bool dead;
    bool deadAnimationEnd;
};

#endif /* OBJECT_H */
