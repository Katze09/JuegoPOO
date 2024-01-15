// States.cpp
#include "States.h"
#include "Loader.h"

Loader loader;
//Asteroid aste;

States::States(SDL_Renderer* renderer)
{
    //spriteAsteroid = loader.LoadTexture("Asteroid", renderer);
    spriteBullet = loader.LoadTexture("Bullet", renderer);
    spriteBulletEnemy[0] = loader.LoadTexture("BulletEnemy", renderer);
    spriteBulletEnemy[1] = loader.LoadTexture("Laser1", renderer);
    spriteBulletEnemy[2] = loader.LoadTexture("Laser2", renderer);
    //vector<SDL_Texture*> textures;
    string nameFile[10];
    nameFile[0] = "Player";
    textures = loadTextures(nameFile, renderer, 1);
    player = Player(textures, 250, 250);
    textures.clear();
    background = Background(loader.LoadTexture("Background", renderer));
    cooldownShot = 0;
    PlayerShot = false;
    nameFile[0] = "EnemyMid";
    nameFile[1] = "EnemyMidHit";
    nameFile[2] = "Died";
    textures = loadTextures(nameFile, renderer, 3);
    enemies.push_back(new EnemyMid(textures, 300, -200));
    textures.clear();
    int enemyStartR = -60;
    int enemyStartL = 700;
    int enemyStartY = 100;
    nameFile[0] = "EnemyBase";
    nameFile[1] = "Died";
    textures = loadTextures(nameFile, renderer, 2);
    //enemies.push_back(new EnemyMid(textures, 300, -200));
    for (int i = 0; i < 3; i++)
    {
        enemies.push_back(new EnemyBase(textures, enemyStartL, enemyStartY, true, 1));
        enemies.push_back(new EnemyBase(textures, enemyStartR, enemyStartY, false, 1));
        enemies.push_back(new EnemyBase(textures, enemyStartL, 400, true, 0));
        enemies.push_back(new EnemyBase(textures, enemyStartR, 400, false, 0));
        enemyStartL += 60;
        enemyStartR -= 60;
        enemyStartY += 20;
    }
    textures.clear();
    nameFile[0] = "EnemyLaser";
    nameFile[1] = "Died";
    textures = loadTextures(nameFile, renderer, 2);
    enemies.push_back(new EnemyLaser(textures, -50, 200, true, 0));
    enemies.push_back(new EnemyLaser(textures, 750, 200, false, 0));
    textures.clear();
    //textures.push_back(loader.LoadTexture("Asteroid", renderer));
    nameFile[0] = "Died";
    textures = (loadTextures(nameFile, renderer, 1));
    textures.insert(textures.begin(), loader.LoadTexture("Asteroid", renderer));
    //aste = Asteroid(spriteAsteroid, 200, 200);
    //asteroids.push_back(new Asteroid(spriteAsteroid));
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
            } else if (dynamic_cast<EnemyMid*> (enemies[i]))
            {
                int posBulletX = 2;
                int posBulletY = 70;
                for (int j = 0; j < 5; j++)
                {
                    bulletsEnemy.push_back(new BulletEnemy(spriteBulletEnemy[0], enemies[i]->getX1() + posBulletX, enemies[i]->getY1() + posBulletY, false, 1000)); //Crear bala en el vector
                    posBulletX += 14;
                    posBulletY += 10;
                }
                posBulletX += 14;
                posBulletY -= 10;
                for (int j = 0; j < 5; j++)
                {
                    bulletsEnemy.push_back(new BulletEnemy(spriteBulletEnemy[0], enemies[i]->getX1() + posBulletX, enemies[i]->getY1() + posBulletY, false, 1000)); //Crear bala en el vector
                    posBulletX += 14;
                    posBulletY -= 10;
                }
                //bulletsEnemy.push_back(new BulletEnemy(spriteBulletEnemy[0], enemies[i]->getX1() + 3, enemies[i]->getY1() + 10, false, 1000)); //Crear bala en el vector
                //bulletsEnemy.push_back(new BulletEnemy(spriteBulletEnemy[0], enemies[i]->getX1() + 37, enemies[i]->getY1() + 10, false, 1000)); //Crear bala en el vector

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

void States::obstaclesEvents()
{
    for (int i = 0; i < asteroids.size(); i++)
    {
        int ind = asteroids[i]->isObstacleHit(bulletsPlayer);
        if (ind >= 0)
            bulletsPlayer.erase(bulletsPlayer.begin() + ind);
        asteroids[i]->update(deltaTime);
        if (asteroids[i]->isCollsionBorder())
            asteroids.erase(asteroids.begin() + i);
        //Borrar
        if (asteroids[i]->endDeadAnimation())
            asteroids.erase(asteroids.begin() + i);
    }
}

void States::createAsteroid()
{
    int ran = loader.randomNumber(1, 60);
    //textures.insert(textures.begin(), spriteAsteroid);
    if (ran == 5)
        asteroids.push_back(new Asteroid(textures));
}

void States::draw(SDL_Renderer* renderer)
{
    background.draw(renderer);
    for (int i = 0; i < asteroids.size(); i++)
        asteroids[i]->draw(renderer);
    player.draw(renderer);
    for (int i = 0; i < bulletsPlayer.size(); i++)
        bulletsPlayer[i]->draw(renderer);
    for (int i = 0; i < enemies.size(); i++)
        enemies[i]->draw(renderer);
    for (int i = bulletsEnemy.size() - 1; i >= 0; i--)
        bulletsEnemy[i]->draw(renderer);
    //aste.draw(renderer);
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
    obstaclesEvents();
    createAsteroid();
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
        contTexture = 1;
    }
    return textures;
}
