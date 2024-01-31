#include "Loader.h"
#include "Obstacle.h"
#include "Enemies.h"
#include <sdl.h>
#include "AudioPlayer.h"

#ifndef LEVEL_H
#define LEVEL_H

using namespace std;

class Level {
public:
    Level();
    Level(SDL_Renderer* renderer, AudioPlayer* audioPlayer);
    virtual ~Level();
    void update(vector<BulletPlayer*>& bulletsPlayer, Player* player, double deltaTime);
    void draw(SDL_Renderer* renderer);
    int numParts;
    int maxnumParts;
    vector<std::vector<EnemyBase*>> enemies;
    vector<BulletEnemy*> bulletsEnemy;
    vector<Obstacle*> asteroids;
    vector<PowerUp*> powerUps;
    void setMaxNumParts(int numParts);
    void setEnemyBase(int cant, double y, int movetype, bool direction, int bulletSpeed);
    void setEnemyLaser(int cant, double y, int movetype, bool direction, double moveTo, int bulletSpeed);
    void setEnemyMid(int cant, double x, double y, double moveTo, int bulletSpeed);
    void setEnemyBoss(double x, double y, double moveTo, int bulletSpeed);
    void setObstacles(int prob);
    void setPowerUps(int prob);
    int getScore();
    void setScore(int score);
private:
    void bulletsEnemysEvents(vector<BulletPlayer*> bulletsPlayer, Player* player, double deltaTime);
    void obstaclesEvents(vector<BulletPlayer*> bulletsPlayer, Player* player, double deltaTime);
    void powerUpsEvents(double deltaTime);
    void createAsteroid();
    void createPowerUp();
    void deleteFromArrays();
    vector<SDL_Texture*> texturesEnemyBase;
    vector<SDL_Texture*> texturesEnemyLaser;
    vector<SDL_Texture*> texturesEnemyMid;
    vector<SDL_Texture*> texturesAsteroid;
    vector<SDL_Texture*> texturesEnemyBoss;
    vector<SDL_Texture*> texturesPowerUp[3];
    vector<int> bulletsToRemove;
    vector<int> bulletsPlayerToRemove;
    vector<int> asteroidsToRemove;
    vector<int> enemiesToRemove;
    SDL_Texture* textureBullet[10];
    AudioPlayer* audioPlayer;
    int score;
    int numEnemies;
    int probSpawn[10];
    int probSpawnPowerUp[10];
};

#endif /* LEVEL_H */

