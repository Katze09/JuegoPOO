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
    virtual ~States();
    void draw(SDL_Renderer* renderer);
    void update(double deltaTime);
    void updateInput(SDL_Keycode key);
    void inputUp(SDL_Keycode key);
private:
    Level* gameLevels[10];
    SDL_Texture* spriteBullet;
    Texts texts;
    Texts textsTitle;
    double cooldownShot;
    bool PlayerShot;
    bool win;
    void bulletsPlayerEvents(double deltaTime);
    void checkPartFinish();
    void passLevel(SDL_Renderer* renderer);
    void deadEvent(SDL_Renderer* renderer);
    void winEvent(SDL_Renderer* renderer);
    bool passingLevel;
    int level;
    int maxLevel;
    bool continueLevel;
    AudioPlayer* audioPlayer;
    Player* player;
    Player* player2;
    Background background;
    vector<SDL_Texture*> textures;
    SDL_Texture* specialAttackTexture;
    double delayPart;
    double delayLevel;
    bool pastPart;
    int totalScore;
    int deaths;
    double startCoolDown;
    std::vector<BulletPlayer*> bulletsPlayer;
};

#endif /* STATES_H */

