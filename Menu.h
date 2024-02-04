#ifndef MENU_H
#define MENU_H

#include <iostream>
//#include "States.h"
#include <string.h>
#include "Background.h"
#include "Texts.h"
#include "Loader.h"
#include <sdl.h>

using namespace std;

class Button {
public:
    Button();
    Button(string showText, float x, float y);
    virtual ~Button();
    bool isPresed(int x, int y);
    void isHover(int x, int y);
    void update(float deltaTime);
    void draw(SDL_Renderer* renderer);
protected:
    bool hover;
    string showText;
    float X1;
    float X2;
    float Y1;
    float Y2;
    Texts texts;
};

class Menu {
public:
    Menu(SDL_Renderer* renderer);
    virtual ~Menu();
    int click(int x, int y);
    void numPlayers();
    void hover(int x, int y);
    void update(float deltaTime);
    void draw(SDL_Renderer* renderer);
private:
    Button play;
    Button player1;
    Button player2;
    Button back;
    Background background;
    Texts textsTile;
    Texts textsExtra;
};

#endif /* MENU_H */

