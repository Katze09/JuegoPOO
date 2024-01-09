// States.cpp
#include "States.h"
#include "Loader.h"

States::States(SDL_Renderer* renderer)
{
    Loader loader;
    spriteBullet = loader.LoadTexture("Bullet", renderer);
    spriteBulletEnemy = loader.LoadTexture("BulletEnemy", renderer);
    SDL_Texture* texture = loader.LoadTexture("Player", renderer);
    player = Player(texture, 250, 250);
    texture = loader.LoadTexture("Background", renderer);
    background = Background(texture);
    cooldownShot = 0;
    PlayerShot = false;
    texture = loader.LoadTexture("EnemyBase", renderer);
    int enemyStart = 700;
    for (int i = 0; i < 5; i++)
    {
        enemies.push_back(new EnemyBase(texture, enemyStart, 100, true));
        enemyStart += 60;
    }
    texture = loader.LoadTexture("EnemyLaser", renderer);
    enemies.push_back(new EnemyLaser(texture, -50, 200, true));
    enemies.push_back(new EnemyLaser(texture, 750, 200, false));
}

void States::bulletsPlayerEvents()
{
    if (PlayerShot && cooldownShot <= 0) //Crear bala si se presiona el espacio y cooldown se termino
    {
        bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player.getX1() + 3, player.getY1() + 10, true)); //Crear bala en el vector
        bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player.getX1() + 37, player.getY1() + 10, true)); //Crear bala en el vector
        cooldownShot = 2; //Ajusta el tiempo entre disparo
    }
    //Eliminar Bullets del vector cuando estas salgan de pantalla
    for (int i = 0; i < bulletsPlayer.size(); i++)
        if (bulletsPlayer[i]->getY1() <= -10)
            bulletsPlayer.erase(bulletsPlayer.begin() + i);
    //Update Bullets para el movimiento
    for (int i = 0; i < bulletsPlayer.size(); i++)
        bulletsPlayer[i]->update(deltaTime);
    if (cooldownShot > 0) //Contar para cooldown
        cooldownShot -= 15 * deltaTime;
}

void States::bulletsEnemysEvents()
{
    for (int i = 0; i < enemies.size(); i++)
    {
        if (enemies[i]->shot(deltaTime))
        {
            bulletsEnemy.push_back(new BulletEnemy(spriteBulletEnemy, enemies[i]->getX1() + 3, enemies[i]->getY1() + 10, false)); //Crear bala en el vector
            bulletsEnemy.push_back(new BulletEnemy(spriteBulletEnemy, enemies[i]->getX1() + 37, enemies[i]->getY1() + 10, false)); //Crear bala en el vector
        }
    }
    for (int i = 0; i < bulletsEnemy.size(); i++)
        bulletsEnemy[i]->update(deltaTime);
}

void States::draw(SDL_Renderer* renderer)
{
    background.draw(renderer);
    player.draw(renderer);
    for (int i = 0; i < bulletsPlayer.size(); i++)
        bulletsPlayer[i]->draw(renderer);
    for (int i = 0; i < bulletsEnemy.size(); i++)
        bulletsEnemy[i]->draw(renderer);
    for (int i = 0; i < enemies.size(); i++)
        enemies[i]->draw(renderer);
}

void States::update(double deltaTime)
{
    this->deltaTime = deltaTime;
    background.update(deltaTime);
    player.update(deltaTime);
    bulletsPlayerEvents();
    bulletsEnemysEvents();
    //Comparar bala con enemigo 
    for (int i = 0; i < enemies.size(); i++)
    {
        int ind = enemies[i]->isEnemyHit(bulletsPlayer);
        if (ind >= 0)
            bulletsPlayer.erase(bulletsPlayer.begin() + ind);
        enemies[i]->update(deltaTime);
    }

    //Borrar
    for (int i = 0; i < enemies.size(); i++)
        if (enemies[i]->isDead())
            enemies.erase(enemies.begin() + i);
}

void States::updateInput(SDL_Keycode key)
{
    player.move(key);
    if (key == SDLK_SPACE)
        PlayerShot = true;
}

void States::inputUp(SDL_Keycode key)
{
    if (key == SDLK_SPACE)
        PlayerShot = false;
    else
        player.stop(key);
}
