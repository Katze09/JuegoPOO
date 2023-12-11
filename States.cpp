// States.cpp
#include "States.h"
#include "Loader.h"

States::States() 
{
    Loader loader;
    HBITMAP sprite = loader.LoadSprite(_T("Player"));
    player = Player(sprite, 250, 250);
    sprite = loader.LoadSprite(_T("Background"));
    background = Background(sprite);
}

void States::draw(HWND hwnd)
{
    background.draw(hwnd);
    player.draw(hwnd);
}

void States::update(double deltaTime)
{
    background.update(deltaTime);
    player.update(deltaTime);
}

void States::updateMove(WPARAM key)
{
    player.move(key);
}

void States::stopMove()
{
    player.stop();
}
