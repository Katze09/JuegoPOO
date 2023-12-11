#ifndef STATES_H
#define STATES_H

#include <iostream>
#include <windows.h>
#include <string>
#include "Player.h"
#include "Background.h"

using namespace std;

class States 
{
public:
    States();
    void draw(HWND hwnd);
    void update(double deltaTime);
    void updateMove(WPARAM key);
    void stopMove();
private:
    Player player;
    Background background;
};

#endif /* STATES_H */

