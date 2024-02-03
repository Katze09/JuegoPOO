// States.cpp

#include "States.h"
#include "Loader.h"

Loader loader; // Instancia del cargador

// Constructor de States que inicializa varios componentes del juego

States::States(SDL_Renderer* renderer)
{
    // Inicializar el reproductor de audio
    audioPlayer = new AudioPlayer();

    // Inicializar objetos de texto con diferentes tamaños de fuente VerminVibes1989
    //texts = Texts("8-bit ArcadeIn", 50);
    //textsTitle = Texts("8-bit ArcadeIn", 80);
    texts = Texts("VerminVibes1989", 40);
    textsTitle = Texts("VerminVibes1989", 70);

    spriteBullet = loader.LoadTexture("Bullet", renderer);

    string nameFile[10];
    nameFile[0] = "Player";
    nameFile[1] = "Shield";
    nameFile[2] = "Died";
    textures = loader.loadTextures(nameFile, renderer, 3);

    specialAttackTexture = loader.LoadTexture("SpecialAttack", renderer);

    player = new Player(textures, 310, 460, true);
    textures.clear(); // Limpiar texturas después de su uso

    background = Background(loader.LoadTexture("Background", renderer));

    cooldownShot = 0;
    passingLevel = PlayerShot = false;
    level = 0;
    startCoolDown = 80;
    deaths = totalScore = delayLevel = delayPart = 0;

    // Cargar niveles de juego
    Level* levelLod;
    while ((levelLod = loader.LoadLevel(level + 1, renderer, audioPlayer)) != nullptr)
    {
        gameLevels[level] = levelLod;
        level++;
    }
    maxLevel = level - 1;
    level = 0;
    pastPart = false;
    continueLevel = false;
    win = false;
}

States::~States()
{
    delete audioPlayer; // Liberar memoria para el reproductor de audio
    delete player; // Liberar memoria para el jugador
    for (int i = 0; i < bulletsPlayer.size(); ++i)
        delete bulletsPlayer[i];
    for (int i = 0; i < 2; ++i)
        delete gameLevels[i];
}

// Manejar eventos relacionados con las balas del jugador

void States::bulletsPlayerEvents(double deltaTime)
{
    if (PlayerShot && cooldownShot <= 0 && !player->isDead())
    {
        // Crear balas si se presiona el espacio y el cooldown ha terminado
        if (player->haveDoubleShot())
        {
            bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player->getX1() + 10, player->getY1() + 10, true, player->getBulletSpeed()));
            bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player->getX1() + 30, player->getY1() + 10, true, player->getBulletSpeed()));
            bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player->getX1() + 40, player->getY1() + 10, true, player->getBulletSpeed()));
            bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player->getX1() + 60, player->getY1() + 10, true, player->getBulletSpeed()));
            audioPlayer->Play(0, 100);
            audioPlayer->Play(0, 100);
        } else
        {
            bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player->getX1() + 12, player->getY1() + 10, true, player->getBulletSpeed()));
            bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player->getX1() + 47, player->getY1() + 10, true, player->getBulletSpeed()));
            audioPlayer->Play(0, 100);
        }
        // Establecer cooldown y reproducir sonido de disparo
        cooldownShot = player->getCoolDownShot();
    }

    if (player->haveSpecialAttackShot() && !player->isDead())
    {
        int numShot = 50;
        for (int i = 0; i < numShot; ++i)
        {
            double radius = 100;
            double angle = (2 * M_PI / numShot) * i;  // Ángulo equidistante
            double x = player->getX1() + (radius * cos(angle) + 30);
            double y = player->getY1() + (radius * sin(angle) + 30);
            double targetX = player->getX1() + 2 * radius * cos(angle);
            double targetY = player->getY1() + 2 * radius * sin(angle);
            bulletsPlayer.push_back(new BulletPlayerSpecial(spriteBullet, x, y, targetX, targetY, player->getBulletSpeed()/1.5));
        }
        player->setSpecialAttackShot(false);
    }

    // Eliminar balas del vector cuando salen de la pantalla
    for (int i = bulletsPlayer.size() - 1; i >= 0; --i)
        if (bulletsPlayer[i]->getY1() <= -10)
            bulletsPlayer.erase(bulletsPlayer.begin() + i);

    // Actualizar movimiento de balas
    for (int i = 0; i < bulletsPlayer.size(); i++)
        bulletsPlayer[i]->update(deltaTime);

    // Contar cooldown
    if (cooldownShot > 0)
        cooldownShot -= 15 * deltaTime;
}

// Dibujar elementos del juego en el renderizador

void States::draw(SDL_Renderer* renderer)
{
    // Dibujar fondo, jugador, balas del jugador y nivel actual
    background.draw(renderer);
    for (int i = 0; i < bulletsPlayer.size(); i++)
        bulletsPlayer[i]->draw(renderer);
    // Mostrar información de puntuación en la pantalla
    if (startCoolDown <= 0)
    {
        gameLevels[level]->draw(renderer);
        if (passingLevel)
            passLevel(renderer);
    } else
    {
        if (startCoolDown > 40)
            textsTitle.drawText("Level " + to_string(level + 1), 200, 300, renderer);
        else if (startCoolDown < 30)
            textsTitle.drawText("Start", 250, 300, renderer);
    }
    if (!player->endDeadAnimation())
        player->draw(renderer);
    else
        deadEvent(renderer);
    if(win)
    {
        winEvent(renderer);
    }
    int x = 30;
    for (int i = 0; i < player->getNumSpecialAttack(); i++)
    {
        SDL_Rect destRect = { x, 730, 50, 50 };
        SDL_RenderCopy(renderer, specialAttackTexture, NULL, &destRect);
        x += 60;
    }
    texts.drawText("Score " + to_string(gameLevels[level]->getScore()), 10, 10, renderer);
    texts.drawText("Level " + to_string(level + 1), 535, 10, renderer);
    texts.drawText("Deaths " + to_string(deaths), 265, 10, renderer);
}

// Actualizar elementos del juego

void States::update(double deltaTime)
{
    // Actualizar fondo y jugador
    background.update(deltaTime);
    if (!player->endDeadAnimation())
    {
        player->update(deltaTime);

        // Verificar colisiones del jugador con balas enemigas y obstáculos
        if (!player->isDead() && !player->isInmortal())
        {
            int ind = player->isPlayerHit(gameLevels[level]->bulletsEnemy);
            if (ind > -1)
            {
                gameLevels[level]->bulletsToRemove.push_back(ind);
                audioPlayer->Play(1, 128);
                deaths++;
            }
            ind = player->isPlayerHitObstacle(gameLevels[level]->asteroids);
            if (ind > -1)
            {
                gameLevels[level]->asteroids[ind]->reduceLife();
                audioPlayer->Play(1, 128);
                deaths++;
            }
            ind = player->isPlayerHitEnemy(gameLevels[level]->enemies[gameLevels[level]->numParts]);
            if (ind > -1)
            {
                gameLevels[level]->enemies[gameLevels[level]->numParts][ind]->reduceLife();
                audioPlayer->Play(1, 128);
                deaths++;
            }
        }
        for (int i = 0; i < gameLevels[level]->powerUps.size(); i++)
            if (gameLevels[level]->powerUps[i]->isCollisionPlayer(player))
            {
                gameLevels[level]->powerUps[i]->setPowerEffect(player);
                gameLevels[level]->powerUpsToRemove.push_back(i);
            }
    }
    bulletsPlayerEvents(deltaTime);
    if (startCoolDown <= 0)
    {
        // Actualizar nivel actual si no se está pasando de nivel
        if (!passingLevel)
        {
            gameLevels[level]->update(bulletsPlayer, player, deltaTime);
            checkPartFinish();
        }
        // Contar tiempo de retardo entre partes del nivel y niveles
        if (delayPart > 0)
            delayPart -= deltaTime * 15;
        if (delayLevel > 0)
            delayLevel -= deltaTime * 15;
    }
    if (startCoolDown > 0)
        startCoolDown -= deltaTime * 25;
}

// Comprobar si se ha completado una parte del nivel

void States::checkPartFinish()
{
    if (gameLevels[level]->enemies[gameLevels[level]->numParts].size() <= 0 && delayPart == 0)
        delayPart = 15;
    if (delayPart < 0 && !pastPart)
        pastPart = true;
    if (pastPart)
    {
        delayPart = 0;
        gameLevels[level]->numParts++;
        // Comprobar si se ha completado el nivel actual
        if (gameLevels[level]->numParts == gameLevels[level]->maxnumParts)
        {
            passingLevel = true;
            delayLevel = 50;
        }
        pastPart = false;
    }
}

// Realizar transición al pasar de nivel

void States::passLevel(SDL_Renderer* renderer)
{
    // Mostrar mensajes de nivel pasado y próximo nivel
    if (delayLevel > 30)
        textsTitle.drawText("Level " + to_string(level + 1) + " Passed", 100, 300, renderer);
    else if (delayLevel < 20)
        textsTitle.drawText("Level " + to_string(level + 2) + " Start", 100, 300, renderer);
    if (delayLevel <= 0)
    {
        if (level == maxLevel)
        {
            win = true;
            passingLevel = false;
        } else
        {
            passingLevel = false;
            level++;
            if (player->getNumSpecialAttack() < 3)
                player->increaseNumSpecialAttack();
            gameLevels[level]->setScore(gameLevels[level - 1]->getScore());
            totalScore = gameLevels[level]->getScore();
        }
    }
}

void States::deadEvent(SDL_Renderer* renderer)
{
    if (continueLevel)
    {
        string nameFile[10];
        nameFile[0] = "Player";
        nameFile[1] = "Shield";
        nameFile[2] = "Died";
        textures = loader.loadTextures(nameFile, renderer, 3);

        // Crear jugador en la posición inicial
        Player* newPlay = new Player(textures, 310, 460, true);
        newPlay->setNumSpecialAttack(player->getNumSpecialAttack());
        player = newPlay;
        Level* lev = loader.LoadLevel((level + 1), renderer, audioPlayer);
        lev->setScore(totalScore);
        gameLevels[level] = lev;
        continueLevel = false;
        delayPart = 0;
    }
    
    textsTitle.drawText("You died", 200, 300, renderer);
    texts.drawText("Press space to try again", 80, 400, renderer);
}

void States::winEvent(SDL_Renderer* renderer)
{
    textsTitle.drawText("Congratulations", 70, 300, renderer);
    textsTitle.drawText("You Won!!", 190, 350, renderer);
    texts.drawText("Press space to continue", 100, 400, renderer);
}
// Actualizar entrada del jugador

void States::updateInput(SDL_Keycode key)
{
    // Mover jugador y activar disparo al presionar teclas
    player->move(key);
    switch (key)
    {
        case SDLK_SPACE:
            PlayerShot = true;
            if (player->endDeadAnimation())
                continueLevel = true;
            break;
        case SDLK_e:
            if (player->getNumSpecialAttack() > 0)
            {
                player->setSpecialAttackShot(true);
                player->reduceNumSpecialAttack();
            }
            break;
    }
}

// Manejar liberación de teclas

void States::inputUp(SDL_Keycode key)
{
    // Desactivar disparo al soltar la tecla de espacio
    if (key == SDLK_SPACE)
        PlayerShot = false;
    else
        player->stop(key);
}
