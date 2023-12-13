#ifndef STATES_H
#define STATES_H

#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include "Player.h"
#include "Background.h"
#include "BulletPlayer.h"
#include "Enemy.h"

using namespace std;

class States 
{
public:
    States();
    void draw(HWND hwnd);
    void update(double deltaTime);
    void updateInput(WPARAM key);
    void inputUp(WPARAM key);
private:
    HBITMAP spriteBullet;
    double cooldownShot;
    bool PlayerShot;
    double deltaTime;
    void bulletsPlayerEvents();
    Player player;
    Background background;
    std::vector<BulletPlayer> bulletPlayer;
    Enemy enemy;
};

#endif /* STATES_H */

