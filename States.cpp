// States.cpp
#include "States.h"
#include "Loader.h"

States::States(SDL_Renderer* renderer)
{
    Loader loader;
    spriteBullet = loader.LoadTexture("Bullet", renderer);
    spriteBulletEnemy[0] = loader.LoadTexture("BulletEnemy", renderer);
    spriteBulletEnemy[1] = loader.LoadTexture("Laser1", renderer);
    spriteBulletEnemy[2] = loader.LoadTexture("Laser2", renderer);
    vector<SDL_Texture*> textures;
    string nameFile[10];
    nameFile[0] = "Player";
    textures = loadTextures(nameFile, renderer, 1);
    player = Player(textures, 250, 250);
    textures.clear();
    background = Background(loader.LoadTexture("Background", renderer));
    cooldownShot = 0;
    PlayerShot = false;
    nameFile[0] = "EnemyBase";
    nameFile[1] = "Died";
    textures = loadTextures(nameFile, renderer, 2);
    int enemyStart = 700;
    for (int i = 0; i < 5; i++)
    {
        enemies.push_back(new EnemyBase(textures, enemyStart, 100, true));
        enemyStart += 60;
    }
    textures.clear();
    nameFile[0] = "EnemyLaser";
    nameFile[1] = "Died";
    textures = loadTextures(nameFile, renderer, 2);
    enemies.push_back(new EnemyLaser(textures, -50, 200, true));
    enemies.push_back(new EnemyLaser(textures, 750, 200, false));
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
            if (EnemyLaser * enemy = dynamic_cast<EnemyLaser*> (enemies[i]))
            {
                if (enemy->isFirstShot())
                {
                    bulletsEnemy.push_back(new BulletEnemy(spriteBulletEnemy[1], enemies[i]->getX1(), enemies[i]->getY1() + 22, false, 500)); //Crear bala en el vector
                    enemy->setFirstShot();
                } else
                    bulletsEnemy.push_back(new BulletEnemy(spriteBulletEnemy[2], enemies[i]->getX1(), enemies[i]->getY1() + 22, false, 500)); //Crear bala en el vector
            } else if (dynamic_cast<EnemyBase*> (enemies[i]))
            {
                bulletsEnemy.push_back(new BulletEnemy(spriteBulletEnemy[0], enemies[i]->getX1() + 3, enemies[i]->getY1() + 10, false, 1000)); //Crear bala en el vector
                bulletsEnemy.push_back(new BulletEnemy(spriteBulletEnemy[0], enemies[i]->getX1() + 37, enemies[i]->getY1() + 10, false, 1000)); //Crear bala en el vector
            }
        }

        //Comparar bala con enemigo 
        int ind = enemies[i]->isEnemyHit(bulletsPlayer);
        if (ind >= 0)
            bulletsPlayer.erase(bulletsPlayer.begin() + ind);
        enemies[i]->update(deltaTime);
        //Borrar
        if (enemies[i]->endDeadAnimation())
            enemies.erase(enemies.begin() + i);
    }
}

void States::draw(SDL_Renderer* renderer)
{
    background.draw(renderer);
    player.draw(renderer);
    for (int i = 0; i < bulletsPlayer.size(); i++)
        bulletsPlayer[i]->draw(renderer);
    for (int i = 0; i < enemies.size(); i++)
        enemies[i]->draw(renderer);
    for (int i = bulletsEnemy.size() - 1; i >= 0; i--)
        bulletsEnemy[i]->draw(renderer);
}

void States::update(double deltaTime)
{
    this->deltaTime = deltaTime;
    background.update(deltaTime);
    player.update(deltaTime);
    bulletsPlayerEvents();
    bulletsEnemysEvents();
    for (int i = 0; i < bulletsEnemy.size(); i++)
    {
        bulletsEnemy[i]->update(deltaTime);
        if (bulletsEnemy[i]->getY1() > 820)
            bulletsEnemy.erase(bulletsEnemy.begin() + i);
    }
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

vector<SDL_Texture*> States::loadTextures(string nameFile[], SDL_Renderer* renderer, int sizeNames)
{
    Loader loader;
    SDL_Texture* texture;
    vector<SDL_Texture*> textures;
    int contTexture = 1;
    for (int i = 0; i < sizeNames; i++)
    {
        texture = loader.LoadTexture(nameFile[i] + to_string(contTexture), renderer);
        while (texture)
        {
            textures.push_back(texture);
            contTexture++;
            texture = loader.LoadTexture(nameFile[i] + to_string(contTexture), renderer);
        }
    }
    return textures;
}
