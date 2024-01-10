#ifndef STATES_H
#define STATES_H

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "Background.h"
#include "Bullets.h"
#include "Enemies.h"

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
    SDL_Texture* spriteBulletEnemy;
    double cooldownShot;
    bool PlayerShot;
    double deltaTime;
    void bulletsPlayerEvents();
    void bulletsEnemysEvents();
    vector<SDL_Texture*> loadTextures(string nameFile[], SDL_Renderer* renderer, int sizeNames);
    Player player;
    Background background;
    std::vector<BulletPlayer*> bulletsPlayer;
    std::vector<BulletEnemy*> bulletsEnemy;
    std::vector<EnemyBase*> enemies;
};

#endif /* STATES_H */

