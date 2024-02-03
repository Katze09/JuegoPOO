#include "Level.h"

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

    // Arreglos de nombres de archivos y texturas para diferentes tipos de enemigos
    nameFile[0] = "EnemyBase";
    nameFile[1] = "Died";
    texturesEnemyBase = load.loadTextures(nameFile, renderer, 2);

    texturesEnemyKamikaze = load.loadTextures(nameFile, renderer, 2);

    nameFile[0] = "EnemyLaser";
    texturesEnemyLaser = load.loadTextures(nameFile, renderer, 2);

    nameFile[0] = "EnemyMid";
    nameFile[1] = "EnemyMidHit";
    nameFile[2] = "Died";
    texturesEnemyMid = load.loadTextures(nameFile, renderer, 3);

    nameFile[0] = "EnemyBoss";
    nameFile[1] = "EnemyBossHit";
    nameFile[2] = "Died";
    texturesEnemyBoss = load.loadTextures(nameFile, renderer, 3);

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
    //enemies[numParts].push_back(new EnemyBoss(texturesEnemyBoss, 200, -300, 50, 550));
    //enemies[numParts].push_back(new EnemyKamikaze(texturesEnemyKamikaze, 0, 0));

    this->audioPlayer = audioPlayer;
    score = 0;
}

// Destructor de Level

Level::~Level()
{
    for (auto& part : enemies)
        for (auto& enemy : part)
            delete enemy;
    for (auto& bullet : bulletsEnemy)
        delete bullet;
    for (auto& asteroid : asteroids)
        delete asteroid;
    for (auto& powerUp : powerUps)
        delete powerUp;

}

void Level::setMaxNumParts(int numParts)
{
    this->maxnumParts = numParts;
}

// Establecer enemigos de la base

void Level::setEnemyBase(int cant, double y, int movetype, bool direction, int bulletSpeed)
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

void Level::setEnemyLaser(int cant, double y, int movetype, bool direction, double moveTo, int bulletSpeed)
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

void Level::setEnemyKamikaze(int cant, double x, double y)
{
    for (int i = 0; i < cant; i++)
    {
        enemies[numParts].push_back(new EnemyKamikaze(texturesEnemyKamikaze, x, y));
        x -= 60;
    }
}

void Level::setEnemyKamikaze(int cant, double x, double y, double speed)
{
    for (int i = 0; i < cant; i++)
    {
        enemies[numParts].push_back(new EnemyKamikaze(texturesEnemyKamikaze, x, y, speed));
        x -= 60;
    }
}

// Establecer enemigos medianos

void Level::setEnemyMid(int cant, double x, double y, double moveTo, int bulletSpeed)
{
    // Crear enemigos medianos y agregarlos al vector
    for (int i = 0; i < cant; i++)
        enemies[numParts].push_back(new EnemyMid(texturesEnemyMid, x, y, moveTo, bulletSpeed));
}

void Level::setEnemyBoss(double x, double y, double moveTo, int bulletSpeed)
{
    enemies[numParts].push_back(new EnemyBoss(texturesEnemyBoss, x, y, moveTo, bulletSpeed));
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

void Level::bulletsEnemysEvents(vector<BulletPlayer*>& bulletsPlayer, Player* player, double deltaTime)
{
    for (int i = 0; i < enemies[numParts].size(); i++)
    {
        // Verificar si el enemigo disparó y manejar el tipo de bala
        if (enemies[numParts][i]->shot(deltaTime))
        {
            // Verificar si el enemigo es un láser
            if (EnemyLaser* laser = dynamic_cast<EnemyLaser*> (enemies[numParts][i]))
                EnemyLaserEvent(laser, i);
            else if (EnemyBoss* boss = dynamic_cast<EnemyBoss*> (enemies[numParts][i]))
                EnemyBossEvent(boss, i , player);
            else if (dynamic_cast<EnemyMid*> (enemies[numParts][i]))
                EnemyMidEvent(i);
            else if (dynamic_cast<EnemyKamikaze*> (enemies[numParts][i])) {}
            else if (dynamic_cast<EnemyBase*> (enemies[numParts][i]))
                EnemyBaseEvent(i);
        }

        // Verificar colisión de balas de jugador con enemigos
        int ind = -1;
        if (!enemies[numParts][i]->isDead())
            ind = enemies[numParts][i]->isEnemyHit(bulletsPlayer);
        if (ind >= 0)
            bulletsPlayerToRemove.push_back(ind);
        if(EnemyKamikaze* kamikaze = dynamic_cast<EnemyKamikaze*> (enemies[numParts][i]))
            kamikaze->update(deltaTime, player->getX1(), player->getY1());
        else
            enemies[numParts][i]->update(deltaTime);

        // Borrar enemigos después de la animación de muerte
        if (enemies[numParts][i]->endDeadAnimation())
        {
            score += (player->haveDoublePoints()) ? enemies[numParts][i]->getScore() * 2 : enemies[numParts][i]->getScore();
            enemiesToRemove.push_back(i);
        }
    }
}

// Manejar eventos de obstáculos (asteroides)

void Level::obstaclesEvents(vector<BulletPlayer*>& bulletsPlayer, Player* player, double deltaTime)
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
            score += (player->haveDoublePoints()) ? asteroids[i]->getScore() * 2 : asteroids[i]->getScore();
            asteroidsToRemove.push_back(i);
        }
    }
}

void Level::powerUpsEvents(double deltaTime)
{
    for (int i = 0; i < powerUps.size(); i++)
    {
        if (powerUps[i]->isCollsionBorder())
            powerUpsToRemove.push_back(i);
        powerUps[i]->update(deltaTime);
    }
}

// Crear asteroides con una cierta probabilidad

void Level::createAsteroid()
{
    int ran = load.randomNumber(1, probSpawn[numParts]);
    if (ran == 5)
        asteroids.push_back(new Asteroid(texturesAsteroid));
}

void Level::createPowerUp()
{
    int ran = load.randomNumber(1, probSpawnPowerUp[numParts]);
    int type = load.randomNumber(0, 4);
    if (ran == 5)
        powerUps.push_back(new PowerUp(texturesPowerUp[type], type));
}

// Actualizar el nivel

void Level::update(vector<BulletPlayer*>& bulletsPlayer, Player* player, double deltaTime)
{
    bulletsEnemysEvents(bulletsPlayer, player, deltaTime);
    for (int i = 0; i < bulletsPlayerToRemove.size(); i++)
    {
        if (bulletsPlayerToRemove[i] <= (bulletsPlayer.size() - 1))
            bulletsPlayer.erase(bulletsPlayer.begin() + bulletsPlayerToRemove[i]);
        bulletsPlayerToRemove.erase(bulletsPlayerToRemove.begin() + i);
    }
    obstaclesEvents(bulletsPlayer, player, deltaTime);
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
    createAsteroid();
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

void Level::EnemyBossEvent(EnemyBoss* boss, int i, Player* player)
{
    if (!boss->isSecondPart())
    {
        if (!boss->isSecondPartP2())
        {
            bulletsEnemy.push_back(new BulletEnemyDiagonal(textureBullet[0], enemies[numParts][i]->getX1() + 110, enemies[numParts][i]->getY1() + 200, false, enemies[numParts][i]->getBulletSpeed(), player->getX1() - 20, player->getY2()));
            bulletsEnemy.push_back(new BulletEnemyDiagonal(textureBullet[0], enemies[numParts][i]->getX1() + 150, enemies[numParts][i]->getY1() + 200, false, enemies[numParts][i]->getBulletSpeed(), player->getX1() + 20, player->getY2()));
        }
        else
        {
            bulletsEnemy.push_back(new BulletEnemyDiagonal(textureBullet[0], enemies[numParts][i]->getX1() + 110, enemies[numParts][i]->getY1() + 200, false, enemies[numParts][i]->getBulletSpeed() * 1.5, player->getX1() - 20, player->getY2()));
            bulletsEnemy.push_back(new BulletEnemyDiagonal(textureBullet[0], enemies[numParts][i]->getX1() + 150, enemies[numParts][i]->getY1() + 200, false, enemies[numParts][i]->getBulletSpeed() * 1.5, player->getX1() + 20, player->getY2()));
        }

        audioPlayer->Play(2, 20);

        if (boss->isThirdPart())
        {
            bulletsEnemy.push_back(new BulletEnemyDiagonal(textureBullet[0], enemies[numParts][i]->getX1() + 70, enemies[numParts][i]->getY1() + 200, false, enemies[numParts][i]->getBulletSpeed(), player->getX1() - 40, player->getY2()));
            bulletsEnemy.push_back(new BulletEnemyDiagonal(textureBullet[0], enemies[numParts][i]->getX1() + 190, enemies[numParts][i]->getY1() + 200, false, enemies[numParts][i]->getBulletSpeed(), player->getX1() + 40, player->getY2()));
            audioPlayer->Play(2, 20);
        }
    }
    else
    {
        audioPlayer->Play(2, 20);
        if (player->getY1() < 320)
        {
            bulletsEnemy.push_back(new BulletEnemyDiagonal(textureBullet[0], enemies[numParts][i]->getX1() + 110, enemies[numParts][i]->getY1() + 200, false, enemies[numParts][i]->getBulletSpeed(), player->getX1() - 20, player->getY2()));
            bulletsEnemy.push_back(new BulletEnemyDiagonal(textureBullet[0], enemies[numParts][i]->getX1() + 150, enemies[numParts][i]->getY1() + 200, false, enemies[numParts][i]->getBulletSpeed(), player->getX1() + 20, player->getY2()));
        }
        bulletsEnemy.push_back(new BulletEnemy(textureBullet[0], enemies[numParts][i]->getX1() + 110, enemies[numParts][i]->getY1() + 200, false, enemies[numParts][i]->getBulletSpeed()));
        bulletsEnemy.push_back(new BulletEnemy(textureBullet[0], enemies[numParts][i]->getX1() + 150, enemies[numParts][i]->getY1() + 200, false, enemies[numParts][i]->getBulletSpeed()));
        bulletsEnemy.push_back(new BulletEnemy(textureBullet[0], enemies[numParts][i]->getX1() + 70, enemies[numParts][i]->getY1() + 200, false, enemies[numParts][i]->getBulletSpeed()));
        bulletsEnemy.push_back(new BulletEnemy(textureBullet[0], enemies[numParts][i]->getX1() + 190, enemies[numParts][i]->getY1() + 200, false, enemies[numParts][i]->getBulletSpeed()));
    }
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