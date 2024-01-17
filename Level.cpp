#include "Level.h"

Loader load;

Level::Level()
{
}

Level::Level(SDL_Renderer* renderer)
{
    string nameFile[2];
    textureBullet[0] = load.LoadTexture("BulletEnemy", renderer);
    textureBullet[1] = load.LoadTexture("Laser1", renderer);
    textureBullet[2] = load.LoadTexture("Laser2", renderer);
    nameFile[0] = "EnemyBase";
    nameFile[1] = "Died";
    texturesEnemyBase = load.loadTextures(nameFile, renderer, 2);
    nameFile[0] = "EnemyLaser";
    texturesEnemyLaser = load.loadTextures(nameFile, renderer, 2);
    nameFile[0] = "EnemyMid";
    texturesEnemyMid = load.loadTextures(nameFile, renderer, 2);
    nameFile[0] = "Asteroid";
    texturesAsteroid = load.loadTextures(nameFile, renderer, 2);
    numParts = 0;
    numEnemies = 0;
    enemies.push_back(std::vector<EnemyBase*>());
}

Level::~Level()
{
}

void Level::setMaxNumParts(int numParts)
{
    this->maxnumParts = numParts;
}

void Level::setEnemyBase(int cant, double y, int movetype, bool direction)
{
    int x;
    int aumento;
    if (direction)
    {
        x = 700;
        aumento = 60;
    } else
    {
        x = -60;
        aumento = -60;
    }
    for (int i = 0; i < cant; i++)
    {
        enemies[numParts].push_back(new EnemyBase(texturesEnemyBase, x, y, direction, movetype));
        x += aumento;
        if (movetype == 1)
            y += 20;
    }
}

void Level::setEnemyLaser(int cant, double y, bool direction)
{
    int x;
    int aumento;
    if (direction)
    {
        x = 700;
        aumento = -60;
    } else
    {
        x = -60;
        aumento = 60;
    }
    for (int i = 0; i < cant; i++)
    {
        enemies[numParts].push_back(new EnemyBase(texturesEnemyLaser, x, y, direction, 1));
        x += aumento;
    }
}

void Level::setEnemyMid(int cant, double y)
{

}

void Level::setObstacles(int prob)
{
    probSpawn[numParts] = prob;
}

void Level::bulletsEnemysEvents(vector<BulletPlayer*> bulletsPlayer, double deltaTime)
{
    for (int i = 0; i < enemies[numParts].size(); i++)
    {
        if (enemies[numParts][i]->shot(deltaTime))
        {
            if (EnemyLaser * enemy = dynamic_cast<EnemyLaser*> (enemies[numParts][i]))
            {
                if (enemy->isFirstShot())
                {
                    bulletsEnemy.push_back(new BulletEnemy(textureBullet[1], enemies[numParts][i]->getX1(), enemies[numParts][i]->getY1() + 22, false, 500)); //Crear bala en el vector
                    enemy->setFirstShot();
                } else
                    bulletsEnemy.push_back(new BulletEnemy(textureBullet[2], enemies[numParts][i]->getX1(), enemies[numParts][i]->getY1() + 22, false, 500)); //Crear bala en el vector
            } else if (dynamic_cast<EnemyMid*> (enemies[numParts][i]))
            {
                int posBulletX = 2;
                int posBulletY = 70;
                for (int j = 0; j < 5; j++)
                {
                    bulletsEnemy.push_back(new BulletEnemy(textureBullet[0], enemies[numParts][i]->getX1() + posBulletX, enemies[numParts][i]->getY1() + posBulletY, false, 1000)); //Crear bala en el vector
                    posBulletX += 14;
                    posBulletY += 10;
                }
                posBulletX += 14;
                posBulletY -= 10;
                for (int j = 0; j < 5; j++)
                {
                    bulletsEnemy.push_back(new BulletEnemy(textureBullet[0], enemies[numParts][i]->getX1() + posBulletX, enemies[numParts][i]->getY1() + posBulletY, false, 1000)); //Crear bala en el vector
                    posBulletX += 14;
                    posBulletY -= 10;
                }

            } else if (dynamic_cast<EnemyBase*> (enemies[numParts][i]))
            {
                bulletsEnemy.push_back(new BulletEnemy(textureBullet[0], enemies[numParts][i]->getX1() + 3, enemies[numParts][i]->getY1() + 10, false, 1000)); //Crear bala en el vector
                bulletsEnemy.push_back(new BulletEnemy(textureBullet[0], enemies[numParts][i]->getX1() + 37, enemies[numParts][i]->getY1() + 10, false, 1000)); //Crear bala en el vector
            }
        }

        //Comparar bala con enemigo 
        int ind = enemies[numParts][i]->isEnemyHit(bulletsPlayer);
        if (ind >= 0)
            bulletsPlayer.erase(bulletsPlayer.begin() + ind);
        enemies[numParts][i]->update(deltaTime);
        //Borrar
        if (enemies[numParts][i]->endDeadAnimation())
        {
            enemies[numParts].erase(enemies[numParts].begin() + i);
        }
    }
}

void Level::obstaclesEvents(vector<BulletPlayer*> bulletsPlayer, double deltaTime)
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
        {
            asteroids.erase(asteroids.begin() + i);
        }
    }
}

void Level::createAsteroid()
{
    int ran = load.randomNumber(1, probSpawn[numParts]);
    //textures.insert(textures.begin(), spriteAsteroid);
    if (ran == 5)
        asteroids.push_back(new Asteroid(texturesAsteroid));
}

void Level::update(vector<BulletPlayer*> bulletsPlayer, double deltaTime)
{
    bulletsEnemysEvents(bulletsPlayer, deltaTime);
    obstaclesEvents(bulletsPlayer, deltaTime);
    for (int i = 0; i < bulletsEnemy.size(); i++)
    {
        bulletsEnemy[i]->update(deltaTime);
        if (bulletsEnemy[i]->getY1() > 820)
            bulletsEnemy.erase(bulletsEnemy.begin() + i);
    }
    createAsteroid();
}

void Level::draw(SDL_Renderer* renderer)
{
    for (int i = 0; i < asteroids.size(); i++)
        asteroids[i]->draw(renderer);
    for (int i = 0; i < enemies[numParts].size(); i++)
        enemies[numParts][i]->draw(renderer);
    for (int i = bulletsEnemy.size() - 1; i >= 0; i--)
        bulletsEnemy[i]->draw(renderer);
}