#include "Loader.h"
#include "Obstacle.h"
#include "Enemies.h"
#include <sdl.h>
#include "AudioPlayer.h"


#ifndef LEVEL_H
#define LEVEL_H

class Level 
{
public:
    Level();
    Level(SDL_Renderer* renderer, AudioPlayer* audioPlayer);
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
    void setMaxNumParts(int numParts);
    void setEnemyBase(int cant, float y, int movetype, bool direction, int bulletSpeed);
    void setEnemyLaser(int cant, float y, int movetype, bool direction, float moveTo, int bulletSpeed);
    void setEnemyStar(float y, int movetype, bool direction, float moveTo, int bulletSpeed);
    void setEnemyKamikaze(int cant, float x, float y);
    void setEnemyKamikaze(int cant, float x, float y, float speed);
    void setEnemyMid(float x, float y, float moveTo, int bulletSpeed);
    void setEnemyMidGuide(float x, float y, float moveTo, int bulletSpeed);
    void setEnemyBoss(float x, float y, float moveTo, int bulletSpeed);
    void setObstacles(int prob);
    void setPowerUps(int prob);
    int getScore();
    void setScore(int score);
private:
    void bulletsEnemysEvents(std::vector<BulletPlayer*>& bulletsPlayer, Player* player[], int numPlayers, float deltaTime);
    void obstaclesEvents(std::vector<BulletPlayer*>& bulletsPlayer, Player* player[], int numPlayers, float deltaTime);
    void powerUpsEvents(float deltaTime);
    void createAsteroid(Player* player[], int numPlayers);
    void createPowerUp();
    void deleteFromArrays();
    void EnemyLaserEvent(EnemyLaser* laser, int i);
    void EnemyBossEvent(EnemyBoss* boss, int i, Player* player);
    void EnemyStarEvent(EnemyStar* star, int i);
    void EnemyMidEvent(int i);
    void EnemyMidGuideEvent(int i, Player* player);
    void EnemyBaseEvent(int i);
    std::vector<SDL_Texture*> texturesEnemyBase;
    std::vector<SDL_Texture*> texturesEnemyLaser;
    std::vector<SDL_Texture*> texturesEnemyStar;
    std::vector<SDL_Texture*> texturesEnemyMid;
    std::vector<SDL_Texture*> texturesEnemyMidGuide;
    std::vector<SDL_Texture*> texturesAsteroid;
    std::vector<SDL_Texture*> texturesEnemyBoss;
    std::vector<SDL_Texture*> texturesEnemyKamikaze;
    std::vector<SDL_Texture*> texturesPowerUp[4];
    std::vector<int> bulletsPlayerToRemove;
    std::vector<int> asteroidsToRemove;
    std::vector<int> enemiesToRemove;
    SDL_Texture* textureBullet[10];
    AudioPlayer* audioPlayer;
    int score;
    int numEnemies;
    int probSpawn[10];
    int probSpawnPowerUp[10];
};

#endif /* LEVEL_H */

