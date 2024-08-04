#pragma once

#include <iostream>
#include <string.h>
#include "Background.h"
#include "Texts.h"
#include "Loader.h"
#include <sdl.h>
#include <algorithm>

class Button 
{
public:
    Button();
    Button(std::string showText, float x, float y, int fontSize);
    virtual ~Button();
    bool isPresed(int x, int y);
    void isHover(int x, int y);
    void update(float deltaTime);
    void draw(SDL_Renderer* renderer);
    float getX() { return X1; }
    float getY() { return Y1; }
    void setText(std::string showText) { this->showText = showText; }
    void setTextColor(SDL_Color color) { textcolor = color; }
protected:
    bool hover;
    std::string showText;
    float X1;
    float X2;
    float Y1;
    float Y2;
    Texts texts;
    SDL_Color textcolor;
};

class Menu 
{
public:
    Menu(SDL_Renderer* renderer);
    virtual ~Menu();
    int click(int x, int y);
    void numPlayers();
    void hover(int x, int y);
    void update(float deltaTime);
    void draw(SDL_Renderer* renderer);
    void setAudioPlayer(AudioPlayer** audioPlayer) { this->audioPlayer = audioPlayer; }
    int WIDTH = 700;
    int HEIGHT = 800;
    bool changeResolution = false;
    bool changeTempResolution = false;
    int startResolution = 2;
    const int widthRes[10] = {300,500,700,900,1100,1300,1500,1700,1900,2100};
    const int heightRes[10] = {400,600,800,1000,1200,1400,1600,1800,2000,2200};
    void setStartResolution(int startResolution) { this->startResolution = startResolution; }
private:
    bool selectPlayer;
    bool instruc;
    bool nextBool;
    bool opti;
    Button play;
    Button instructions;
    Button player1;
    Button player2;
    Button online;
    Button local;
    Button back;
    Button backIns;
    Button backOpti;
    Button options;
    Button next;
    Button increaseSound;
    Button decreaseSound;
    Button increaseResolution;
    Button decreaseResolution;
    Background background;
    Texts textsTile;
    Texts textsMid;
    Texts textsLittle;
    Texts textsExtra;
    AudioPlayer** audioPlayer;
    const std::string resolutionOptions[10] = {"300x400","500x600","700x800","900x1000","1100x1200","1300x1400","1500x1600","1700x1800","1900x2000","2100x2200"};
};

class Item
{
public:
    Item();
    Item(SDL_Texture* texture, int type, int cost, float X, float Y, int WIDTH, int HEIGHT);
    void update(float deltaTime);
    void draw(SDL_Renderer* renderer);
    float getX() { return X; }
    float getY() { return Y; }
    int getCost() { return cost; }
    int getType() { return type; }
    bool sold = false;
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
    int getRemainingScore() { return score; }
    void startShopping(int score, Player* player[], int numPlayers);
    void endShopping();
private:
    SDL_Texture* itemTextures[5];
    int itemCost[5] = {300, 600, 600, 800, 1200};
    Item items[3];
    Button itemsButton[3];
    Player** player;
    int numPlayers = 1;
    Button finishShop;
    Background background;
    Texts textsTile;
    Texts textsMid;
    Texts textsExtra;
    int score = 0;
};

class Leaderboard
{
public:
    Leaderboard();
    Leaderboard(SDL_Renderer* renderer);
    virtual ~Leaderboard();
    int click(int x, int y);
    void hover(int x, int y);
    void update(float deltaTime);
    void draw(SDL_Renderer* renderer);
    void setScore(int score) { this->score = score; }
    void setDeaths(int deaths) { this->deaths = deaths; }
    void loadLeaderboard(int numPlayers);
    void updateInput(std::string text) { if(namePlayer.length() < 10) namePlayer += text; }
    void deleteCharacter() { if (namePlayer.length() > 0) namePlayer = namePlayer.substr(0, namePlayer.length() - 1); }
private:
    int score = 0;
    int deaths = 0;
    int numPlayers = 1;
    std::string leaderNames[5];
    int leaderScores[5];
    int indexLeader[5];
    int leaderDeaths[5];
    int sizeLeaderboard = 0;
    std::string namePlayer = "";
    Button accept;
    Texts textsTile;
    Texts textsMid;
    Texts textsExtra;
    Background background;
    bool end = false;
};
