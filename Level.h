#pragma once

#include "Obstacle.h"
#include "Enemies.h"
#include <sdl.h>
#include "AudioPlayer.h"

class Level 
{
public:
    Level();
    Level(SDL_Renderer* renderer, AudioPlayer** audioPlayer);
    virtual ~Level();
    void update(std::vector<BulletPlayer*>& bulletsPlayer, Player* player[], int numPlayers, float deltaTime);
    void draw(SDL_Renderer* renderer);
    int numParts;
    int maxnumParts;
    std::vector<std::vector<EnemyBase*>> enemies;
    std::vector<BulletEnemy*> bulletsEnemy;
    std::vector<Obstacle*> asteroids;
    std::vector<PowerUp*> powerUps;
    std::vector<int> bulletsToRemove;
    std::vector<int> powerUpsToRemove;
    void setMaxNumParts(int numParts) { this->maxnumParts = numParts; }
    void setEnemyBase(int cant, float y, int movetype, bool direction, int bulletSpeed)
    {
        int x;
        int aumento;

        if (direction)
        {
            x = 700;
            aumento = 60;
        }
        else
        {
            x = -60;
            aumento = -60;
        }

        // Crear enemigos de la base y agregarlos al vector
        for (int i = 0; i < cant; i++)
        {
            enemies[numParts].push_back(new EnemyBase(texturesEnemyBase, x, y, direction, movetype, bulletSpeed));
            x += aumento;
            if (movetype == 1)
                y += 20;
        }
    }
    void setEnemyLaser(int cant, float y, int movetype, bool direction, float moveTo, int bulletSpeed)
    {
        int x;
        int aumento;

        // Determinar posición inicial y aumento según la dirección
        if (direction)
        {
            x = 700;
            aumento = 60;
        }
        else
        {
            x = -60;
            aumento = -60;
        }

        // Crear enemigos láser y agregarlos al vector
        for (int i = 0; i < cant; i++)
        {
            enemies[numParts].push_back(new EnemyLaser(texturesEnemyLaser, x, y, direction, movetype, moveTo, bulletSpeed));
            x += aumento;
            moveTo += aumento;
        }
    }
    void setEnemyStar(float y, int movetype, bool direction, float moveTo, int bulletSpeed)
    {
        float x;
        if (direction)
            x = 720;
        else
            x = -80;
        enemies[numParts].push_back(new EnemyStar(texturesEnemyStar, x, y, direction, movetype, moveTo, bulletSpeed));
    }
    void setEnemyKamikaze(int cant, float x, float y)
    {
        for (int i = 0; i < cant; i++)
        {
            enemies[numParts].push_back(new EnemyKamikaze(texturesEnemyKamikaze, x, y));
            x -= 60;
        }
    }
    void setEnemyKamikaze(int cant, float x, float y, float speed)
    {
        for (int i = 0; i < cant; i++)
        {
            enemies[numParts].push_back(new EnemyKamikaze(texturesEnemyKamikaze, x, y, speed));
            x -= 60;
        }
    }
    void setEnemyAngry(int cant, float y, bool direction, int bulletSpeed)
    {
        float x;
        if (direction)
            x = 720;
        else
            x = -80;
        for (int i = 0; i < cant; i++)
            enemies[numParts].push_back(new EnemyAngry(texturesEnemyBase, x, y, direction, bulletSpeed));
    }
    void setEnemyMid(float x, float y, float moveTo, int bulletSpeed){ enemies[numParts].push_back(new EnemyMid(texturesEnemyMid, x, y, moveTo, bulletSpeed)); }
    void setEnemyMidGuide(float x, float y, float moveTo, int bulletSpeed){ enemies[numParts].push_back(new EnemyMidGuide(texturesEnemyMidGuide, x, y, moveTo, bulletSpeed)); }
    void setEnemyBoss(float x, float y, float moveTo, int bulletSpeed, int boss)
    {
        switch (boss)
        {
        case 0:enemies[numParts].push_back(new EnemyBoss(texturesEnemyBoss, x, y, moveTo, bulletSpeed)); break;
        case 1:enemies[numParts].push_back(new EnemySecondBoss(texturesEnemySecondBoss, x, y, moveTo, bulletSpeed)); break;
        }
    }
    void setObstacles(int prob){ probSpawn[numParts] = prob; }
    void setPowerUps(int prob){ probSpawnPowerUp[numParts] = prob; }
    int getScore(){ return score; }
    void setScore(int score){ this->score = score; }
    int Totalscore = 0;
private:
    void bulletsEnemysEvents(std::vector<BulletPlayer*>& bulletsPlayer, Player* player[], int numPlayers, float deltaTime);
    void obstaclesEvents(std::vector<BulletPlayer*>& bulletsPlayer, Player* player[], int numPlayers, float deltaTime);
    void powerUpsEvents(float deltaTime);
    void createAsteroid(Player* player[], int numPlayers);
    void createPowerUp();
    void deleteFromArrays();
    void EnemyLaserEvent(EnemyLaser* laser, int i);
    void EnemyAngryEvent(EnemyAngry* angry, int i);
    void EnemyBossEvent(EnemyBoss* boss, int i, Player* player);
    void EnemySecondBossEvent(EnemySecondBoss* secondboss, int i);
    void EnemyStarEvent(EnemyStar* star, int i);
    void EnemyMidEvent(int i);
    void EnemyMidGuideEvent(int i, Player* player);
    void EnemyBaseEvent(int i);
    std::vector<SDL_Texture*> texturesEnemyBase;
    std::vector<SDL_Texture*> texturesEnemyLaser;
    std::vector<SDL_Texture*> texturesEnemyStar;
    std::vector<SDL_Texture*> texturesEnemyAngry;
    std::vector<SDL_Texture*> texturesEnemyMid;
    std::vector<SDL_Texture*> texturesEnemyMidGuide;
    std::vector<SDL_Texture*> texturesAsteroid;
    std::vector<SDL_Texture*> texturesEnemyBoss;
    std::vector<SDL_Texture*> texturesEnemySecondBoss;
    std::vector<SDL_Texture*> texturesEnemyKamikaze;
    std::vector<SDL_Texture*> texturesPowerUp[4];
    std::vector<int> bulletsPlayerToRemove;
    std::vector<int> asteroidsToRemove;
    std::vector<int> enemiesToRemove;
    SDL_Texture* textureBullet[10];
    AudioPlayer** audioPlayer;
    int score;
    int numEnemies;
    int probSpawn[10];
    int probSpawnPowerUp[10];
};
