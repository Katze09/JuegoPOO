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
#include "Menu.h"
#include "JoyStick.h"

class States 
{
public:
    States(SDL_Renderer* renderer);
    virtual ~States();
    void draw(SDL_Renderer* renderer);
    void update(float deltaTime);
    void setPlayer2(SDL_Renderer* renderer);
    void updateInput(SDL_Keycode key);
    void inputUp(SDL_Keycode key);
    void mouseClick(int x, int y);
    void mouseMove(int x, int y);
    Leaderboard leaderboard;
private:
    Level* gameLevels[10];
    SDL_Texture* spriteBullet;
    Texts texts;
    Texts textsTitle;
    JoyStick* joys[2];
    int numJoySticks = 0;
    float cooldownShot[2];
    bool PlayerShot[2];
    bool win;
    Shop shop;
    bool leaderboardTime;
    bool shopTime;
    void bulletsPlayerEvents(float deltaTime);
    void checkPartFinish();
    void passLevel(SDL_Renderer* renderer);
    void deadEvent(SDL_Renderer* renderer);
    void updateInputJoyStick();
    bool alreadyUse[4] = { false, false, false, false };
    bool passingLevel;
    int level;
    int maxLevel;
    bool continueLevel;
    AudioPlayer* audioPlayer;
    Player* player[2];
    int numPlayers = 1;
    Background background;
    std::vector<SDL_Texture*> textures;
    SDL_Texture* specialAttackTexture;
    SDL_Texture* shieldItemTexture;
    float delayPart;
    float delayLevel;
    bool pastPart;
    int totalScore;
    int deaths;
    float startCoolDown;
    std::vector<BulletPlayer*> bulletsPlayer;
};

#endif /* STATES_H */

