#ifndef STATES_H
#define STATES_H

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "Background.h"
#include "Bullets.h"
#include "Obstacle.h"
#include "Texts.h"
#include "AudioPlayer.h"
#include "Level.h"

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
    Level* gameLevels[10];
    SDL_Texture* spriteBullet;
    Texts texts;
    double cooldownShot;
    bool PlayerShot;
    void bulletsPlayerEvents(double deltaTime);
    void checkPartFinish();
    int level;
    AudioPlayer* audioPlayer;
    Player* player;
    Background background;
    vector<SDL_Texture*> textures;
    double delayPart;
    bool pastPart;
    std::vector<BulletPlayer*> bulletsPlayer;
};

#endif /* STATES_H */

