#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string.h>
#include "Background.h"
#include "Texts.h"
#include "Loader.h"
#include <sdl.h>

using namespace std;

class Button {
public:
    Button();
    Button(string showText, float x, float y, int fontSize);
    virtual ~Button();
    bool isPresed(int x, int y);
    void isHover(int x, int y);
    void update(float deltaTime);
    void draw(SDL_Renderer* renderer);
    float getX() { return X1; }
    float getY() { return Y1; }
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

class Item
{
public:
    Item();
    Item(SDL_Texture* texture, int type, int cost, float X, float Y, int WIDTH, int HEIGHT);
    void update(float deltaTime);
    void draw(SDL_Renderer* renderer);
    void setEffectPlayer();
    float getX() { return X; }
    float getY() { return Y; }
    int getCost() { return cost; }
private:
    SDL_Texture* texture;
    int WIDTH;
    int HEIGHT;
    int type;
    float X;
    float Y;
    int cost;
};

class Shop
{
public:
    Shop();
    Shop(SDL_Renderer* renderer);
    virtual ~Shop();
    int click(int x, int y);
    void hover(int x, int y);
    void update(float deltaTime);
    void draw(SDL_Renderer* renderer);
    bool endShop;
    int getRemainingPoints() { return totalPoints; }
    void startShopping(int points, Player* player[], int numPlayers);
    void endShopping();
private:
    SDL_Texture* itemTextures[5];
    Item items[3];
    Button itemsButton[3];
    Player** player;
    int numPlayers = 1;
    Button finishShop;
    Background background;
    Texts textsTile;
    Texts textsMid;
    Texts textsExtra;
    int totalPoints = 0;
};

#endif /* MENU_H */

