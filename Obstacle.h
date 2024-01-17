/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Obstacle.h
 * Author: Katze
 *
 * Created on 11 de enero de 2024, 23:49
 */
#include "Object.h"
#include "Loader.h"
#include "Bullets.h"

#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle : public Object 
{
public:
    Obstacle();
    Obstacle(vector<SDL_Texture*> textures);
    Obstacle(vector<SDL_Texture*> textures, float X1, float Y1);
    virtual ~Obstacle();
    void update(double deltaTime);\
    void animationBase(double deltaTime);
    void animationDead(double deltaTime);
    int isObstacleHit(vector<BulletPlayer*> bulletPlayer);
    bool isCollsionBorder();
    bool isDead();
    virtual void draw(SDL_Renderer* renderer);
protected:
    int life;
    float targetY;
    bool direction;
    double slope;
    double intercept;
    int angleRotation;
};

class Asteroid : public Obstacle 
{
public:
    Asteroid();
    Asteroid(vector<SDL_Texture*> textures);
    Asteroid(vector<SDL_Texture*> textures, float X1, float Y1);
    virtual ~Asteroid();
protected:
};

#endif /* OBSTACLE_H */

