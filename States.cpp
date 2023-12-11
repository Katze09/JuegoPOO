// States.cpp
#include "States.h"
#include "Loader.h"

States::States() 
{
    Loader loader;
    spriteBullet = loader.LoadSprite(_T("Bullet"));
    HBITMAP sprite = loader.LoadSprite(_T("Player"));
    player = Player(sprite, 250, 250);
    sprite = loader.LoadSprite(_T("Background"));
    background = Background(sprite);
    numBulletP = 0;
    cooldownShot = 0;
}

void States::draw(HWND hwnd)
{
    background.draw(hwnd);
    player.draw(hwnd);
    for(int i = 0;i < numBulletP;i++)
        bulletPlayer[i].draw(hwnd);
    if(cooldownShot > 0)
        cooldownShot--;
}

void States::update(double deltaTime)
{
    background.update(deltaTime);
    player.update(deltaTime);
    for(int i = 0;i < numBulletP;i++)
        bulletPlayer[i].update(deltaTime);
}

void States::updateInput(WPARAM key)
{
    player.move(key);
    if(key == VK_SPACE && cooldownShot == 0)
    {
        bulletPlayer[numBulletP] = BulletPlayer(spriteBullet, player.getX1() + 25, player.getY1());
        numBulletP++;
        if(numBulletP >= 15)
            numBulletP = 0;
        cooldownShot = 5;
    }
}

void States::stopMove()
{
    player.stop();
    
}
