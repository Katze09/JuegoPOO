#ifndef STATES_H
#define STATES_H

#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include "Player.h"
#include "Background.h"
#include "BulletPlayer.h"

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
    bool shot;
    Player player;
    Background background;
    std::vector<BulletPlayer> bulletPlayer;
};

#endif /* STATES_H */

