#include "Level.h"

// Crear una instancia del cargador
Loader load;

// Constructor predeterminado de Level

Level::Level()
{
}

// Constructor de Level con parámetros para el renderizador y el reproductor de audio

Level::Level(SDL_Renderer* renderer, AudioPlayer* audioPlayer)
{
    // Arreglos de nombres de archivos y texturas para las balas
    string nameFile[2];
    textureBullet[0] = load.LoadTexture("BulletEnemy", renderer);
    textureBullet[1] = load.LoadTexture("Laser1", renderer);
    textureBullet[2] = load.LoadTexture("Laser2", renderer);

    // Arreglos de nombres de archivos y texturas para diferentes tipos de enemigos
    nameFile[0] = "EnemyBase";
    nameFile[1] = "Died";
    texturesEnemyBase = load.loadTextures(nameFile, renderer, 2);

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

    numParts = 0;
    numEnemies = 0;

    // Crear el primer vector de enemigos
    enemies.push_back(std::vector<EnemyBase*>());
    //enemies[numParts].push_back(new EnemyBoss(texturesEnemyBoss, 200, -300, 50, 75));

    // Establecer el reproductor de audio
    this->audioPlayer = audioPlayer;
    // Inicializar la puntuación
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
}

// Establecer el número máximo de partes

void Level::setMaxNumParts(int numParts)
{
    this->maxnumParts = numParts;
}

// Establecer enemigos de la base

void Level::setEnemyBase(int cant, double y, int movetype, bool direction, int bulletSpeed)
{
    int x;
    int aumento;

    // Determinar posición inicial y aumento según la dirección
    if (direction)
    {
        x = 700;
        aumento = 80;
    } else
    {
        x = -60;
        aumento = -80;
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

// Establecer enemigos medianos

void Level::setEnemyMid(int cant, double x, double y, double moveTo, int bulletSpeed)
{
    // Crear enemigos medianos y agregarlos al vector
    for (int i = 0; i < cant; i++)
        enemies[numParts].push_back(new EnemyMid(texturesEnemyMid, x, y, moveTo, bulletSpeed));
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

void Level::bulletsEnemysEvents(vector<BulletPlayer*> bulletsPlayer, Player* player, double deltaTime)
{
    for (int i = 0; i < enemies[numParts].size(); i++)
    {
        // Verificar si el enemigo disparó y manejar el tipo de bala
        if (enemies[numParts][i]->shot(deltaTime))
        {
            // Verificar si el enemigo es un láser
            if (EnemyLaser * enemy = dynamic_cast<EnemyLaser*> (enemies[numParts][i]))
            {
                if (enemy->isFirstShot())
                {
                    // Crear bala láser inicial
                    bulletsEnemy.push_back(new BulletEnemy(textureBullet[1], enemies[numParts][i]->getX1(), enemies[numParts][i]->getY1() + 22, false, enemies[numParts][i]->getBulletSpeed()));
                    enemy->setFirstShot();
                    audioPlayer->Play(3, 30);
                } else
                    // Crear otras balas láser
                    bulletsEnemy.push_back(new BulletEnemy(textureBullet[2], enemies[numParts][i]->getX1(), enemies[numParts][i]->getY1() + 22, false, enemies[numParts][i]->getBulletSpeed()));
            } else if (dynamic_cast<EnemyBoss*> (enemies[numParts][i]))
            {
                bulletsEnemy.push_back(new BulletEnemyDiagonal(
                            textureBullet[0],
                            enemies[numParts][i]->getX1() + 150,
                            enemies[numParts][i]->getY1() + 200,
                            false,
                            enemies[numParts][i]->getBulletSpeed(),
                            player->getX1()
                            ));
                /*int posBulletX = 0;
                int posBulletY = 200;
                for (int j = 0; j < 10; j++)
                {
                    bulletsEnemy.push_back(new BulletEnemyDiagonal(
                            textureBullet[0],
                            enemies[numParts][i]->getX1() + posBulletX,
                            enemies[numParts][i]->getY1() + posBulletY,
                            false,
                            enemies[numParts][i]->getBulletSpeed(),
                            player->getX1()
                            ));
                    posBulletX += 20;
                    //posBulletY += 10;
                }*/
            } else if (dynamic_cast<EnemyMid*> (enemies[numParts][i]))
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
            } else if (dynamic_cast<EnemyBase*> (enemies[numParts][i]))
            {
                // Manejar balas de enemigos de la base
                audioPlayer->Play(2, 20);
                bulletsEnemy.push_back(new BulletEnemy(textureBullet[0], enemies[numParts][i]->getX1() + 3, enemies[numParts][i]->getY1() + 10, false, enemies[numParts][i]->getBulletSpeed()));
                bulletsEnemy.push_back(new BulletEnemy(textureBullet[0], enemies[numParts][i]->getX1() + 37, enemies[numParts][i]->getY1() + 10, false, enemies[numParts][i]->getBulletSpeed()));
            }
        }

        // Verificar colisión de balas de jugador con enemigos
        int ind = -1;
        if (!enemies[numParts][i]->isDead())
            ind = enemies[numParts][i]->isEnemyHit(bulletsPlayer);
        if (ind >= 0)
            bulletsPlayer.erase(bulletsPlayer.begin() + ind);

        // Actualizar posición y animación de enemigos
        enemies[numParts][i]->update(deltaTime);

        // Borrar enemigos después de la animación de muerte
        if (enemies[numParts][i]->endDeadAnimation())
        {
            score += (player->haveDoubleScore()) ? enemies[numParts][i]->getScore() * 2 : enemies[numParts][i]->getScore();
            enemies[numParts].erase(enemies[numParts].begin() + i);
        }
    }
}

// Manejar eventos de obstáculos (asteroides)

void Level::obstaclesEvents(vector<BulletPlayer*> bulletsPlayer, Player* player, double deltaTime)
{
    for (int i = 0; i < asteroids.size(); i++)
    {
        // Verificar colisión de balas de jugador con asteroides
        int ind = asteroids[i]->isObstacleHit(bulletsPlayer);
        if (ind >= 0)
            bulletsPlayer.erase(bulletsPlayer.begin() + ind);

        // Actualizar posición y animación de asteroides
        asteroids[i]->update(deltaTime);

        // Borrar asteroides que colisionan con el borde
        if (asteroids[i]->isCollsionBorder())
            asteroids.erase(asteroids.begin() + i);

        // Borrar asteroides después de la animación de muerte
        if (asteroids[i]->endDeadAnimation())
        {
            score += (player->haveDoubleScore()) ? asteroids[i]->getScore() * 2 : asteroids[i]->getScore();
            asteroids.erase(asteroids.begin() + i);
        }
    }
}

void Level::powerUpsEvents(double deltaTime)
{
    for (int i = 0; i < powerUps.size(); i++)
    {
        if (powerUps[i]->isCollsionBorder())
            powerUps.erase(powerUps.begin() + i);
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
    int type = load.randomNumber(0, 3);
    if (ran == 5)
        powerUps.push_back(new PowerUp(texturesPowerUp[type], type));
}

// Actualizar el nivel

void Level::update(vector<BulletPlayer*> bulletsPlayer, Player* player, double deltaTime)
{
    bulletsEnemysEvents(bulletsPlayer, player, deltaTime);
    obstaclesEvents(bulletsPlayer, player, deltaTime);
    powerUpsEvents(deltaTime);

    // Actualizar posición de balas de enemigos y borrarlas si salen de la pantalla
    for (int i = 0; i < bulletsEnemy.size(); i++)
    {
        bulletsEnemy[i]->update(deltaTime);
        if (bulletsEnemy[i]->getY1() > 820)
            bulletsEnemy.erase(bulletsEnemy.begin() + i);
    }

    // Crear asteroides con cierta probabilidad
    createAsteroid();
    createPowerUp();
}

// Dibujar el nivel en el renderizador

void Level::draw(SDL_Renderer* renderer)
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