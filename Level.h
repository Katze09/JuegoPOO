#include "Loader.h"
#include "Obstacle.h"
#include "Enemies.h"
#include <sdl.h>

#ifndef LEVEL_H
#define LEVEL_H

using namespace std;

class Level {
public:
    Level();
    Level(SDL_Renderer* renderer);
    virtual ~Level();
    void update(vector<BulletPlayer*> bulletsPlayer, double deltaTime);
    void draw(SDL_Renderer* renderer);
    int numParts;
    vector<std::vector<EnemyBase*>> enemies;
    void setMaxNumParts(int numParts);
    void setEnemyBase(int cant, double y, int movetype, bool direction);
    void setEnemyLaser(int cant, double y, bool direction);
    void setEnemyMid(int cant, double y);
    void setObstacles(int prob);
private:
    void bulletsEnemysEvents(vector<BulletPlayer*> bulletsPlayer, double deltaTime);
    void obstaclesEvents(vector<BulletPlayer*> bulletsPlayer, double deltaTime);
    void createAsteroid();
    vector<SDL_Texture*> texturesEnemyBase;
    vector<SDL_Texture*> texturesEnemyLaser;
    vector<SDL_Texture*> texturesEnemyMid;
    vector<SDL_Texture*> texturesAsteroid;
    vector<Obstacle*> asteroids;
    std::vector<BulletEnemy*> bulletsEnemy;
    SDL_Texture* textureBullet[10];
    int maxnumParts;
    int numEnemies;
    int probSpawn[10];
};

#endif /* LEVEL_H */

