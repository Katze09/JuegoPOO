#include "Level.h"

using namespace std;

// Crear una instancia del cargador
Loader load;

// Constructor predeterminado de Level

Level::Level()
{
}

Level::Level(SDL_Renderer* renderer, AudioPlayer* audioPlayer)
{
    // Arreglos de nombres de archivos y texturas para las balas
    string nameFile[5];
    textureBullet[0] = load.LoadTexture("BulletEnemy", renderer);
    textureBullet[1] = load.LoadTexture("Laser1", renderer);
    textureBullet[2] = load.LoadTexture("Laser2", renderer);
    textureBullet[3] = load.LoadTexture("BulletEnemyBig", renderer);
    textureBullet[4] = load.LoadTexture("BulletEnemySecond", renderer);

    // Arreglos de nombres de archivos y texturas para diferentes tipos de enemigos
    nameFile[0] = "EnemyBase";
    nameFile[1] = "Died";
    texturesEnemyBase = load.loadTextures(nameFile, renderer, 2);

    nameFile[0] = "EnemyBaseKamikaze";
    texturesEnemyKamikaze = load.loadTextures(nameFile, renderer, 2);

    nameFile[0] = "EnemyLaser";
    texturesEnemyLaser = load.loadTextures(nameFile, renderer, 2);

    //nameFile[0] = "EnemyAngry";
    //texturesEnemyAngry = load.loadTextures(nameFile, renderer, 2);

    nameFile[0] = "EnemyStar";
    nameFile[1] = "EnemyStarHit";
    nameFile[2] = "Died";
    texturesEnemyStar = load.loadTextures(nameFile, renderer, 3);

    nameFile[0] = "EnemyMid";
    nameFile[1] = "EnemyMidHit";
    nameFile[2] = "Died";
    texturesEnemyMid = load.loadTextures(nameFile, renderer, 3);
    
    nameFile[0] = "EnemyMidGuide";
    nameFile[1] = "EnemyMidGuideHit";
    nameFile[2] = "Died";
    texturesEnemyMidGuide = load.loadTextures(nameFile, renderer, 3);

    nameFile[0] = "EnemyBoss";
    nameFile[1] = "EnemyBossHit";
    nameFile[2] = "Died";
    texturesEnemyBoss = load.loadTextures(nameFile, renderer, 3);

    nameFile[0] = "EnemySecondBoss";
    nameFile[1] = "EnemySecondBossHit";
    nameFile[2] = "Died";
    texturesEnemySecondBoss = load.loadTextures(nameFile, renderer, 3);

    nameFile[0] = "Asteroid";
    nameFile[1] = "Died";
    texturesAsteroid = load.loadTextures(nameFile, renderer, 2);

    nameFile[0] = "PowerUpShot";
    texturesPowerUp[0] = load.loadTextures(nameFile, renderer, 1);

    nameFile[0] = "PowerUpInmortal";
    texturesPowerUp[1] = load.loadTextures(nameFile, renderer, 1);

    nameFile[0] = "PowerUpDouble";
    texturesPowerUp[2] = load.loadTextures(nameFile, renderer, 1);

    nameFile[0] = "PowerUpDoubleP";
    texturesPowerUp[3] = load.loadTextures(nameFile, renderer, 1);

    numParts = 0;
    numEnemies = 0;

    enemies.push_back(std::vector<EnemyBase*>());
    //setEnemyMidGuide(400, -100, 150, 700);
    //enemies[numParts].push_back(new EnemyStar(texturesEnemyStar, 780, 400, true, 0, 400, 700));
    //enemies[numParts].push_back(new EnemyBoss(texturesEnemyBoss, 200, -300, 50, 550));

    this->audioPlayer = audioPlayer;
    score = 0;
}

// Destructor de Level

Level::~Level() 
{
    for (auto& enemyList : enemies) 
        for (auto& enemy : enemyList) 
            delete enemy;
    enemies.clear();

    for (auto& bullet : bulletsEnemy) 
        delete bullet;
    bulletsEnemy.clear();

    for (auto& asteroid : asteroids) 
        delete asteroid;
    asteroids.clear();

    for (auto& powerUp : powerUps) 
        delete powerUp;
    powerUps.clear();

    for (auto& texture : texturesEnemyBase) 
        SDL_DestroyTexture(texture);
    texturesEnemyBase.clear();

    for (auto& texture : texturesEnemyLaser) 
        SDL_DestroyTexture(texture);
    texturesEnemyLaser.clear();

    for (auto& texture : texturesEnemyStar) 
        SDL_DestroyTexture(texture);
    texturesEnemyStar.clear();

    for (auto& texture : texturesEnemyAngry) 
        SDL_DestroyTexture(texture);
    texturesEnemyAngry.clear();

    for (auto& texture : texturesEnemyMid) 
        SDL_DestroyTexture(texture);
    texturesEnemyMid.clear();

    for (auto& texture : texturesEnemyMidGuide) 
        SDL_DestroyTexture(texture);
    texturesEnemyMidGuide.clear();

    for (auto& texture : texturesAsteroid) 
        SDL_DestroyTexture(texture);
    texturesAsteroid.clear();

    for (auto& texture : texturesEnemyBoss) 
        SDL_DestroyTexture(texture);
    texturesEnemyBoss.clear();

    for (auto& texture : texturesEnemySecondBoss) 
        SDL_DestroyTexture(texture);
    texturesEnemySecondBoss.clear();

    for (auto& texture : texturesEnemyKamikaze) 
        SDL_DestroyTexture(texture);
    texturesEnemyKamikaze.clear();

    for (auto& textures : texturesPowerUp) 
        for (auto& texture : textures) 
            SDL_DestroyTexture(texture);
    texturesPowerUp->clear();

    for (auto& texture : textureBullet) 
        SDL_DestroyTexture(texture);
}


void Level::setMaxNumParts(int numParts)
{
    this->maxnumParts = numParts;
}

// Establecer enemigos de la base

void Level::setEnemyBase(int cant, float y, int movetype, bool direction, int bulletSpeed)
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

    // Crear enemigos de la base y agregarlos al vector
    for (int i = 0; i < cant; i++)
    {
        enemies[numParts].push_back(new EnemyBase(texturesEnemyBase, x, y, direction, movetype, bulletSpeed));
        x += aumento;
        if (movetype == 1)
            y += 20;
    }
}

// Establecer enemigos láser

void Level::setEnemyLaser(int cant, float y, int movetype, bool direction, float moveTo, int bulletSpeed)
{
    int x;
    int aumento;

    // Determinar posición inicial y aumento según la dirección
    if (direction)
    {
        x = 700;
        aumento = 60;
    } else
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

void Level::setEnemyStar(float y, int movetype, bool direction, float moveTo, int bulletSpeed)
{
    float x;
    if (direction)
        x = 720;
    else
        x = -80;
    enemies[numParts].push_back(new EnemyStar(texturesEnemyStar, x,y, direction, movetype, moveTo, bulletSpeed));
}

void Level::setEnemyAngry(int cant, float y, bool direction, int bulletSpeed)
{
    float x;
    if (direction)
        x = 720;
    else
        x = -80;
    for (int i = 0; i < cant; i++)
        enemies[numParts].push_back(new EnemyAngry(texturesEnemyBase, x, y, direction, bulletSpeed));
}

void Level::setEnemyKamikaze(int cant, float x, float y)
{
    for (int i = 0; i < cant; i++)
    {
        enemies[numParts].push_back(new EnemyKamikaze(texturesEnemyKamikaze, x, y));
        x -= 60;
    }
}

void Level::setEnemyKamikaze(int cant, float x, float y, float speed)
{
    for (int i = 0; i < cant; i++)
    {
        enemies[numParts].push_back(new EnemyKamikaze(texturesEnemyKamikaze, x, y, speed));
        x -= 60;
    }
}

// Establecer enemigos medianos

void Level::setEnemyMid(float x, float y, float moveTo, int bulletSpeed)
{
    enemies[numParts].push_back(new EnemyMid(texturesEnemyMid, x, y, moveTo, bulletSpeed));
}

void Level::setEnemyMidGuide(float x, float y, float moveTo, int bulletSpeed)
{
    enemies[numParts].push_back(new EnemyMidGuide(texturesEnemyMidGuide, x, y, moveTo, bulletSpeed));
}

void Level::setEnemyBoss(float x, float y, float moveTo, int bulletSpeed, int boss)
{
    switch (boss)
    {
    case 0:enemies[numParts].push_back(new EnemyBoss(texturesEnemyBoss, x, y, moveTo, bulletSpeed)); break;
    case 1:enemies[numParts].push_back(new EnemySecondBoss(texturesEnemySecondBoss, x, y, moveTo, bulletSpeed)); break;
    }
}

// Establecer obstáculos con una probabilidad de aparición

void Level::setObstacles(int prob)
{
    probSpawn[numParts] = prob;
}

void Level::setPowerUps(int prob)
{
    probSpawnPowerUp[numParts] = prob;
}

// Manejar eventos de balas de enemigos

void Level::bulletsEnemysEvents(vector<BulletPlayer*>& bulletsPlayer, Player* player[], int numPlayers, float deltaTime)
{
    for (int i = 0; i < enemies[numParts].size(); i++)
    {
        if (EnemyMidGuide* midGuide = dynamic_cast<EnemyMidGuide*> (enemies[numParts][i]))
        {
            if (midGuide->playerIndex < 0)
                midGuide->playerIndex = load.randomNumber(0, numPlayers);
            if (player[midGuide->playerIndex]->isDead() && numPlayers > 1)
                if (midGuide->playerIndex == 1)
                    midGuide->playerIndex--;
                else if (midGuide->playerIndex == 0)
                    midGuide->playerIndex++;
            midGuide->setAngleRotation(player[midGuide->playerIndex]->getX1(), player[midGuide->playerIndex]->getY1());
        }
        // Verificar si el enemigo disparó y manejar el tipo de bala
        if (enemies[numParts][i]->shot(deltaTime))
        {
            if (EnemyStar* star = dynamic_cast<EnemyStar*> (enemies[numParts][i]))
                EnemyStarEvent(star, i);
            else if (EnemyLaser* laser = dynamic_cast<EnemyLaser*> (enemies[numParts][i]))
                EnemyLaserEvent(laser, i);
            else if (EnemySecondBoss* secondboss = dynamic_cast<EnemySecondBoss*> (enemies[numParts][i]))
                EnemySecondBossEvent(secondboss, i);
            else if (EnemyBoss* boss = dynamic_cast<EnemyBoss*> (enemies[numParts][i]))
            {
                if (numPlayers > 1)
                {
                    int iPlayer;
                    if (player[0]->isDead())
                        iPlayer = 1;
                    else if (player[1]->isDead())
                        iPlayer = 0;
                    else
                        iPlayer = load.randomNumber(0, 2);
                    EnemyBossEvent(boss, i, player[iPlayer]);
                } else
                    EnemyBossEvent(boss, i, player[0]);
            }
            else if(EnemyMidGuide* midGuide = dynamic_cast<EnemyMidGuide*> (enemies[numParts][i]))
                EnemyMidGuideEvent(i, player[midGuide->playerIndex]);
            else if (dynamic_cast<EnemyMid*> (enemies[numParts][i]))
                EnemyMidEvent(i);
            else if (dynamic_cast<EnemyBase*> (enemies[numParts][i]))
                EnemyBaseEvent(i);
        }

        // Verificar colisión de balas de jugador con enemigos
        int ind = -1;
        if (!enemies[numParts][i]->isDead())
            ind = enemies[numParts][i]->isEnemyHit(bulletsPlayer);
        if (ind >= 0)
            bulletsPlayerToRemove.push_back(ind);
        if (EnemyAngry* angry = dynamic_cast<EnemyAngry*> (enemies[numParts][i]))
        {
            if (angry->isOffLimits())
                enemiesToRemove.push_back(i);
            if (angry->isAngry())
            {
                if (angry->playerIndex < 0)
                    angry->playerIndex = load.randomNumber(0, numPlayers);
                if (player[angry->playerIndex]->isDead() && numPlayers > 1)
                    if (angry->playerIndex == 1)
                        angry->playerIndex--;
                    else if (angry->playerIndex == 0)
                        angry->playerIndex++;
            }
            angry->update(deltaTime, player[angry->playerIndex]->getX1(), player[angry->playerIndex]->getY1());
        }
        else if (EnemyKamikaze* kamikaze = dynamic_cast<EnemyKamikaze*> (enemies[numParts][i]))
        {
            if (kamikaze->playerIndex < 0)
                kamikaze->playerIndex = load.randomNumber(0, numPlayers);
            if (player[kamikaze->playerIndex]->isDead() && numPlayers > 1)
                if (kamikaze->playerIndex == 1)
                    kamikaze->playerIndex--;
                else if (kamikaze->playerIndex == 0)
                    kamikaze->playerIndex++;
            kamikaze->update(deltaTime, player[kamikaze->playerIndex]->getX1(), player[kamikaze->playerIndex]->getY1());
        }
        else
            enemies[numParts][i]->update(deltaTime);

        // Borrar enemigos después de la animación de muerte
        if (enemies[numParts][i]->endDeadAnimation())
        {
            for (int p = 0; p < numPlayers; p++)
            {
                score += (player[p]->haveDoublePoints() || player[p]->haveItemDoublePoints()) ? enemies[numParts][i]->getScore() * 2 : enemies[numParts][i]->getScore();
                Totalscore += (player[p]->haveDoublePoints() || player[p]->haveItemDoublePoints()) ? enemies[numParts][i]->getScore() * 2 : enemies[numParts][i]->getScore();
            }
            enemiesToRemove.push_back(i);
        }
    }
}

// Manejar eventos de obstáculos (asteroides)

void Level::obstaclesEvents(vector<BulletPlayer*>& bulletsPlayer, Player* player[], int numPlayers, float deltaTime)
{
    for (int i = 0; i < asteroids.size(); i++)
    {
        // Verificar colisión de balas de jugador con asteroides
        int ind = asteroids[i]->isObstacleHit(bulletsPlayer);
        if (ind >= 0 && ind <= (bulletsPlayer.size() - 1))
            bulletsPlayer.erase(bulletsPlayer.begin() + ind);

        // Actualizar posición y animación de asteroides
        asteroids[i]->update(deltaTime);

        if (asteroids[i]->isCollsionBorder())
            asteroidsToRemove.push_back(i);

        // Borrar asteroides después de la animación de muerte
        if (asteroids[i]->endDeadAnimation())
        {
            for (int p = 0; p < numPlayers; p++)
            {
                score += (player[p]->haveDoublePoints() || player[p]->haveItemDoublePoints()) ? asteroids[i]->getScore() * 2 : asteroids[i]->getScore();
                Totalscore += (player[p]->haveDoublePoints() || player[p]->haveItemDoublePoints()) ? asteroids[i]->getScore() * 2 : asteroids[i]->getScore();
            }
            asteroidsToRemove.push_back(i);
        }
    }
}

void Level::powerUpsEvents(float deltaTime)
{
    for (int i = 0; i < powerUps.size(); i++)
    {
        if (powerUps[i]->isCollsionBorder())
            powerUpsToRemove.push_back(i);
        powerUps[i]->update(deltaTime);
    }
}

// Crear asteroides con una cierta probabilidad

void Level::createAsteroid(Player* player[], int numPlayers)
{
    int x1 = 400;
    int x2 = 400;
    if (numPlayers > 1)
    {
        x1 = player[1]->getX1();
        x2 = player[1]->getX2();
    }
    if (player[0]->getX1() > 50 && player[0]->getX2() < 650 && x1 > 50 && x2 < 650)
    {
        int ran = load.randomNumber(1, probSpawn[numParts]);
        if (ran == 5)
            asteroids.push_back(new Asteroid(texturesAsteroid));
    }
}

void Level::createPowerUp()
{
    int ran = load.randomNumber(1, probSpawnPowerUp[numParts]);
    int type = load.randomNumber(0, 4);
    if (ran == 5)
        powerUps.push_back(new PowerUp(texturesPowerUp[type], type));
}

// Actualizar el nivel

void Level::update(vector<BulletPlayer*>& bulletsPlayer, Player* player[], int numPlayers, float deltaTime)
{
    bulletsEnemysEvents(bulletsPlayer, player, numPlayers, deltaTime);
    for (int i = 0; i < bulletsPlayerToRemove.size(); i++)
    {
        if (bulletsPlayerToRemove[i] < (bulletsPlayer.size() - 1))
            bulletsPlayer.erase(bulletsPlayer.begin() + bulletsPlayerToRemove[i]);
        bulletsPlayerToRemove.erase(bulletsPlayerToRemove.begin() + i);
    }
    obstaclesEvents(bulletsPlayer, player, numPlayers, deltaTime);
    powerUpsEvents(deltaTime);

    // Actualizar posición de balas de enemigos y borrarlas si salen de la pantalla
    for (int i = 0; i < bulletsEnemy.size(); i++)
    {
        bulletsEnemy[i]->update(deltaTime);
        if (bulletsEnemy[i]->getY1() > 820)
            bulletsToRemove.push_back(i);
    }
    deleteFromArrays();

    // Crear asteroides con cierta probabilidad
    createAsteroid(player, numPlayers);
    createPowerUp();
}

//Eliminar del Vector Objetos no necesarios
void Level::deleteFromArrays()
{
    for (int i = bulletsToRemove.size() - 1; i >= 0; --i)
    {
        if (bulletsToRemove[i] <= (bulletsEnemy.size() - 1))
            bulletsEnemy.erase(bulletsEnemy.begin() + bulletsToRemove[i]);
        bulletsToRemove.erase(bulletsToRemove.begin() + i);
    }
    for (int i = enemiesToRemove.size() - 1; i >= 0; --i)
    {
        if (enemiesToRemove[i] <= (enemies[numParts].size() - 1))
            enemies[numParts].erase(enemies[numParts].begin() + enemiesToRemove[i]);
        enemiesToRemove.erase(enemiesToRemove.begin() + i);
    }
    for (int i = asteroidsToRemove.size() - 1; i >= 0; --i)
    {
        if (asteroidsToRemove[i] <= (asteroids.size() - 1))
            asteroids.erase(asteroids.begin() + asteroidsToRemove[i]);
        asteroidsToRemove.erase(asteroidsToRemove.begin() + i);
    }
    for (int i = powerUpsToRemove.size() - 1; i >= 0; --i)
    {
        if (powerUpsToRemove[i] <= (powerUps.size() - 1))
            powerUps.erase(powerUps.begin() + powerUpsToRemove[i]);
        powerUpsToRemove.erase(powerUpsToRemove.begin() + i);
    }
}

void Level::EnemyLaserEvent(EnemyLaser* laser, int i)
{
    if (laser->isFirstShot())
    {
        bulletsEnemy.push_back(new BulletEnemy(textureBullet[1], enemies[numParts][i]->getX1(), enemies[numParts][i]->getY1() + 22, false, enemies[numParts][i]->getBulletSpeed()));
        laser->setFirstShot();
        audioPlayer->Play(3, 30);
    }
    else
        bulletsEnemy.push_back(new BulletEnemy(textureBullet[2], enemies[numParts][i]->getX1(), enemies[numParts][i]->getY1() + 22, false, enemies[numParts][i]->getBulletSpeed()));
}

void Level::EnemyAngryEvent(EnemyAngry* angry, int i)
{

}

void Level::EnemyStarEvent(EnemyStar* star, int i)
{
    int numShot = 20;
    for (int i = 0; i < numShot; ++i)
    {
        float radius = 100;
        float angle = (2 * M_PI / numShot) * i;  // Ángulo equidistante
        float x = (star->getX1() + 30) + (radius * cos(angle)/2);
        float y = (star->getY1() + 25) + (radius * sin(angle)/2);
        float targetX = star->getX1() + 2 * radius * cos(angle);
        float targetY = star->getY1() + 2 * radius * sin(angle);
        bulletsEnemy.push_back(new BulletEnemyDiagonal(textureBullet[0], x, y, targetX, targetY, star->getBulletSpeed() / 1.5));
        audioPlayer->Play(2, 20);
    }
}

void Level::EnemyBossEvent(EnemyBoss* boss, int i, Player* player)
{
    if (!boss->isSecondPart())
    {
        if (!boss->isSecondPartP2())
        {
            bulletsEnemy.push_back(new BulletEnemyDiagonal(textureBullet[0], enemies[numParts][i]->getX1() + 110, enemies[numParts][i]->getY1() + 200, player->getX1() - 20, player->getY2(), enemies[numParts][i]->getBulletSpeed()));
            bulletsEnemy.push_back(new BulletEnemyDiagonal(textureBullet[0], enemies[numParts][i]->getX1() + 150, enemies[numParts][i]->getY1() + 200, player->getX1() + 20, player->getY2(), enemies[numParts][i]->getBulletSpeed()));
        }
        else
        {
            bulletsEnemy.push_back(new BulletEnemyDiagonal(textureBullet[0], enemies[numParts][i]->getX1() + 110, enemies[numParts][i]->getY1() + 200, player->getX1() - 20, player->getY2(), enemies[numParts][i]->getBulletSpeed() * 1.5));
            bulletsEnemy.push_back(new BulletEnemyDiagonal(textureBullet[0], enemies[numParts][i]->getX1() + 150, enemies[numParts][i]->getY1() + 200, player->getX1() + 20, player->getY2(), enemies[numParts][i]->getBulletSpeed() * 1.5));
        }

        audioPlayer->Play(2, 20);

        if (boss->isThirdPart())
        {
            bulletsEnemy.push_back(new BulletEnemyDiagonal(textureBullet[0], enemies[numParts][i]->getX1() + 70, enemies[numParts][i]->getY1() + 200, player->getX1() - 40, player->getY2(), enemies[numParts][i]->getBulletSpeed()));
            bulletsEnemy.push_back(new BulletEnemyDiagonal(textureBullet[0], enemies[numParts][i]->getX1() + 190, enemies[numParts][i]->getY1() + 200, player->getX1() + 40, player->getY2(), enemies[numParts][i]->getBulletSpeed()));
            audioPlayer->Play(2, 20);
        }
    }
    else
    {
        audioPlayer->Play(2, 20);
        if (player->getY1() < 320)
        {
            bulletsEnemy.push_back(new BulletEnemyDiagonal(textureBullet[0], enemies[numParts][i]->getX1() + 110, enemies[numParts][i]->getY1() + 200, player->getX1() - 20, player->getY2(), enemies[numParts][i]->getBulletSpeed()));
            bulletsEnemy.push_back(new BulletEnemyDiagonal(textureBullet[0], enemies[numParts][i]->getX1() + 150, enemies[numParts][i]->getY1() + 200, player->getX1() + 20, player->getY2(), enemies[numParts][i]->getBulletSpeed()));
        }
        bulletsEnemy.push_back(new BulletEnemy(textureBullet[0], enemies[numParts][i]->getX1() + 110, enemies[numParts][i]->getY1() + 200, false, enemies[numParts][i]->getBulletSpeed()));
        bulletsEnemy.push_back(new BulletEnemy(textureBullet[0], enemies[numParts][i]->getX1() + 150, enemies[numParts][i]->getY1() + 200, false, enemies[numParts][i]->getBulletSpeed()));
        bulletsEnemy.push_back(new BulletEnemy(textureBullet[0], enemies[numParts][i]->getX1() + 70, enemies[numParts][i]->getY1() + 200, false, enemies[numParts][i]->getBulletSpeed()));
        bulletsEnemy.push_back(new BulletEnemy(textureBullet[0], enemies[numParts][i]->getX1() + 190, enemies[numParts][i]->getY1() + 200, false, enemies[numParts][i]->getBulletSpeed()));
    }
}

bool shotSec = true;
int circ = 2;

void Level::EnemySecondBossEvent(EnemySecondBoss* secondboss, int i)
{
    if (secondboss->canSpawnEnemies())
    {
        int y = load.randomNumber(-100, 150);
        setEnemyKamikaze(secondboss->numSpawnEnemies, -200, y);
        setEnemyKamikaze(secondboss->numSpawnEnemies, 950, y);
        secondboss->falseSpawnEnemies();
    }
    if (secondboss->isFirstPart())
    {
        int numShot = 30;
        for (int i = 0; i < numShot; ++i)
        {
            float radius = 100;
            float angle = (circ * M_PI / numShot) * i;  // Ángulo equidistante
            float xPosition = secondboss->getX1() + 67;
            float yPosition = secondboss->getY1() + 67;
            float x = xPosition + (radius * cos(angle) / 2);
            float y = yPosition + (radius * sin(angle) / 2);
            float targetX = xPosition + 2 * radius * cos(angle);
            float targetY = yPosition + 2 * radius * sin(angle);
            BulletEnemyDiagonal* bullet = new BulletEnemyDiagonal(textureBullet[4], x, y, targetX, targetY, secondboss->getBulletSpeed() / 1.5);
            bullet->activeRotation();
            bulletsEnemy.push_back(bullet);
            audioPlayer->Play(2, 20);
        }
        if (shotSec)
            circ++;
        else
            circ--;
        if (circ > 4)
            shotSec = false;
        if (circ < 3)
            shotSec = true;
    }
}

void Level::EnemyMidGuideEvent(int i, Player* player)
{
    audioPlayer->Play(2, 20); audioPlayer->Play(2, 20);
    audioPlayer->Play(2, 20); audioPlayer->Play(2, 20);
    BulletEnemyDiagonal* diagonal = new BulletEnemyDiagonal(textureBullet[3], enemies[numParts][i]->getX1() + 30, enemies[numParts][i]->getY1() + 80, player->getX1(), player->getY1(), enemies[numParts][i]->getBulletSpeed());
    diagonal->activeRotation();
    bulletsEnemy.push_back(diagonal);
}

void Level::EnemyMidEvent(int i) 
{
    // Manejar balas de enemigos medianos
    audioPlayer->Play(2, 20);
    int posBulletX = 2;
    int posBulletY = 70;

    // Crear balas para enemigos medianos
    for (int j = 0; j < 5; j++)
    {
        bulletsEnemy.push_back(new BulletEnemy(textureBullet[0], enemies[numParts][i]->getX1() + posBulletX, enemies[numParts][i]->getY1() + posBulletY, false, enemies[numParts][i]->getBulletSpeed()));
        posBulletX += 14;
        posBulletY += 10;
    }

    posBulletX += 14;
    posBulletY -= 10;

    // Crear más balas para enemigos medianos
    for (int j = 0; j < 5; j++)
    {
        bulletsEnemy.push_back(new BulletEnemy(textureBullet[0], enemies[numParts][i]->getX1() + posBulletX, enemies[numParts][i]->getY1() + posBulletY, false, enemies[numParts][i]->getBulletSpeed()));
        posBulletX += 14;
        posBulletY -= 10;
    }
}

void Level::EnemyBaseEvent(int i)
{
    audioPlayer->Play(2, 20);
    bulletsEnemy.push_back(new BulletEnemy(textureBullet[0], enemies[numParts][i]->getX1() + 3, enemies[numParts][i]->getY1() + 10, false, enemies[numParts][i]->getBulletSpeed()));
    bulletsEnemy.push_back(new BulletEnemy(textureBullet[0], enemies[numParts][i]->getX1() + 37, enemies[numParts][i]->getY1() + 10, false, enemies[numParts][i]->getBulletSpeed()));
}

void Level::draw(SDL_Renderer * renderer)
{
    // Dibujar asteroides
    for (int i = 0; i < asteroids.size(); i++)
        asteroids[i]->draw(renderer);

    for (int i = 0; i < powerUps.size(); i++)
        powerUps[i]->draw(renderer);

    // Dibujar enemigos
    for (int i = 0; i < enemies[numParts].size(); i++)
        enemies[numParts][i]->draw(renderer);

    // Dibujar balas de enemigos
    for (int i = bulletsEnemy.size() - 1; i >= 0; i--)
        bulletsEnemy[i]->draw(renderer);
}

// Obtener la puntuación actual

int Level::getScore()
{
    return score;
}

void Level::setScore(int score)
{
    this->score = score;
}