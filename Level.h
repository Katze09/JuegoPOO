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
    void update(vector<BulletPlayer*> bulletsPlayer, double deltaTime);
    void draw(SDL_Renderer* renderer);
    int numParts;
    int maxnumParts;
    vector<std::vector<EnemyBase*>> enemies;
    vector<BulletEnemy*> bulletsEnemy;
    vector<Obstacle*> asteroids;
    void setMaxNumParts(int numParts);
    void setEnemyBase(int cant, double y, int movetype, bool direction);
    void setEnemyLaser(int cant, double y, int movetype, bool direction, double moveTo);
    void setEnemyMid(int cant, double x, double y, double moveTo);
    void setObstacles(int prob);
    int getScore();
private:
    void bulletsEnemysEvents(vector<BulletPlayer*> bulletsPlayer, double deltaTime);
    void obstaclesEvents(vector<BulletPlayer*> bulletsPlayer, double deltaTime);
    void createAsteroid();
    vector<SDL_Texture*> texturesEnemyBase;
    vector<SDL_Texture*> texturesEnemyLaser;
    vector<SDL_Texture*> texturesEnemyMid;
    vector<SDL_Texture*> texturesAsteroid;
    SDL_Texture* textureBullet[10];
    AudioPlayer* audioPlayer;
    int score;
    int numEnemies;
    int probSpawn[10];
};

#endif /* LEVEL_H */

