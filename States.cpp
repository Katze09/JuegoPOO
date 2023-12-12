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
    cooldownShot = 0;
    shot = false;
}

void States::bulletsPlayerEvents()
{
    if(shot && cooldownShot <= 0) //Crear bala si se presiona el espacio y cooldown se termino
    {
        bulletPlayer.push_back(BulletPlayer(spriteBullet, player.getX1() + 3, player.getY1() + 10)); //Crear bala en el vector
        bulletPlayer.push_back(BulletPlayer(spriteBullet, player.getX1() + 37, player.getY1() + 10)); //Crear bala en el vector
        cooldownShot = 2; //Ajusta el tiempo entre disparo
    }
    //Eliminar Bullets del vector cuando estas salgan de pantalla
    for (int i = 0;i < bulletPlayer.size();i++) 
        if(bulletPlayer[i].getY1() <= -10)
            bulletPlayer.erase(bulletPlayer.begin() + i);
    //Update Bullets para el movimiento
    for (int i = 0;i < bulletPlayer.size();i++)
        bulletPlayer[i].update(deltaTime);
    if(cooldownShot > 0) //Contar para cooldown
        cooldownShot -= 15 * deltaTime;
}

void States::draw(HWND hwnd)
{
    background.draw(hwnd);
    player.draw(hwnd);
    for (int i = 0;i < bulletPlayer.size();i++) 
        bulletPlayer[i].draw(hwnd);
}

void States::update(double deltaTime)
{
    this->deltaTime = deltaTime;
    background.update(deltaTime);
    player.update(deltaTime);
    bulletsPlayerEvents();
}

void States::updateInput(WPARAM key)
{
    player.move(key);
    if(key == VK_SPACE)
        shot = true;
}

void States::inputUp(WPARAM key)
{
    if(key == VK_SPACE)
        shot = false;
    player.stop();
}
