#ifndef STATES_H
#define STATES_H

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "Background.h"
#include "Bullets.h"
#include "Enemies.h"
#include "Obstacle.h"

using namespace std;

class States 
{
public:
    States(SDL_Renderer* renderer);
    void draw(SDL_Renderer* renderer);
    void update(double deltaTime);
    void updateInput(SDL_Keycode key);
    void inputUp(SDL_Keycode key);
private:
    SDL_Texture* spriteBullet;
    SDL_Texture* spriteAsteroid;
    SDL_Texture* spriteBulletEnemy[10];
    double cooldownShot;
    bool PlayerShot;
    double deltaTime;
    void bulletsPlayerEvents();
    void bulletsEnemysEvents();
    void obstaclesEvents();
    void createAsteroid();
    vector<SDL_Texture*> loadTextures(string nameFile[], SDL_Renderer* renderer, int sizeNames);
    Player player;
    Background background;
    vector<SDL_Texture*> textures;
    vector<Obstacle*> asteroids;
    std::vector<BulletPlayer*> bulletsPlayer;
    std::vector<BulletEnemy*> bulletsEnemy;
    std::vector<EnemyBase*> enemies;
};

#endif /* STATES_H */

