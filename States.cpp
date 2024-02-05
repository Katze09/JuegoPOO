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

    player[0] = new Player(textures, 310, 460);
    textures.clear(); // Limpiar texturas después de su uso

    background = Background(loader.LoadTexture("Background", renderer));

    cooldownShot[0] = cooldownShot[1] = 0;
    passingLevel = PlayerShot[0] = PlayerShot[1] = false;
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
    //level = 3;
    //gameLevels[level]->numParts = 2;
    pastPart = false;
    continueLevel = false;
    win = false;
}
 
States::~States()
{
    delete audioPlayer; // Liberar memoria para el reproductor de audio
    for (int i = 0; i < 2; ++i)
        delete player[i];
    for (int i = 0; i < bulletsPlayer.size(); ++i)
        delete bulletsPlayer[i];
    for (int i = 0; i < 2; ++i)
        delete gameLevels[i];
}

void States::setPlayer2(SDL_Renderer* renderer)
{
    string nameFile[10];
    nameFile[0] = "Player2";
    nameFile[1] = "Shield";
    nameFile[2] = "Died";
    numPlayers++;
    player[1] = new Player2(loader.loadTextures(nameFile, renderer, 3), 400, 460);
}

// Manejar eventos relacionados con las balas del jugador

void States::bulletsPlayerEvents(float deltaTime)
{
    for (int p = 0; p < numPlayers; p++)
    {
        if (PlayerShot[p] && cooldownShot[p] <= 0 && !player[p]->isDead())
        {
            // Crear balas si se presiona el espacio y el cooldown ha terminado
            if (player[p]->havefloatShot())
            {
                bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player[p]->getX1() + 10, player[p]->getY1() + 10, true, player[p]->getBulletSpeed()));
                bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player[p]->getX1() + 30, player[p]->getY1() + 10, true, player[p]->getBulletSpeed()));
                bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player[p]->getX1() + 40, player[p]->getY1() + 10, true, player[p]->getBulletSpeed()));
                bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player[p]->getX1() + 60, player[p]->getY1() + 10, true, player[p]->getBulletSpeed()));
                audioPlayer->Play(0, 100);
                audioPlayer->Play(0, 100);
            }
            else
            {
                bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player[p]->getX1() + 12, player[p]->getY1() + 10, true, player[p]->getBulletSpeed()));
                bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player[p]->getX1() + 47, player[p]->getY1() + 10, true, player[p]->getBulletSpeed()));
                audioPlayer->Play(0, 100);
            }
            // Establecer cooldown y reproducir sonido de disparo
            cooldownShot[p] = player[p]->getCoolDownShot();
        }

        if (player[p]->haveSpecialAttackShot() && !player[p]->isDead())
        {
            int numShot = 50;
            for (int i = 0; i < numShot; ++i)
            {
                float radius = 100;
                float angle = (2 * M_PI / numShot) * i;  // Ángulo equidistante
                float x = (player[p]->getX1() + 30) + (radius * cos(angle)/2);
                float y = (player[p]->getY1() + 25) + (radius * sin(angle)/2);
                float targetX = player[p]->getX1() + 2 * radius * cos(angle);
                float targetY = player[p]->getY1() + 2 * radius * sin(angle);
                bulletsPlayer.push_back(new BulletPlayerSpecial(spriteBullet, x, y, targetX, targetY, player[p]->getBulletSpeed() / 1.5));
                audioPlayer->Play(0, 100);
            }
            player[p]->setSpecialAttackShot(false);
        }
        // Contar cooldown
        if (cooldownShot[p] > 0)
            cooldownShot[p] -= 15 * deltaTime;
    }
    // Eliminar balas del vector cuando salen de la pantalla
    for (int i = bulletsPlayer.size() - 1; i >= 0; --i)
        if (bulletsPlayer[i]->getY1() <= -10)
            bulletsPlayer.erase(bulletsPlayer.begin() + i);

    // Actualizar movimiento de balas
    for (int i = 0; i < bulletsPlayer.size(); i++)
        bulletsPlayer[i]->update(deltaTime);
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
    for (int p = 0; p < numPlayers; p++)
    {
        if (!player[p]->endDeadAnimation())
            player[p]->draw(renderer);
        if (win)
        {
            winEvent(renderer);
        }
        int x = 30;
        if (p == 1)
            x = 500;
        for (int i = 0; i < player[p]->getNumSpecialAttack(); i++)
        {
            SDL_Rect destRect = { x, 730, 50, 50 };
            SDL_RenderCopy(renderer, specialAttackTexture, NULL, &destRect);
            x += 60;
        }
    }
    if (numPlayers > 1)
    {
        if (player[0]->isDead() && player[1]->isDead())
            deadEvent(renderer);
    }else if(player[0]->isDead())
        deadEvent(renderer);
    texts.drawText("Score " + to_string(gameLevels[level]->getScore()), 10, 10, renderer);
    texts.drawText("Level " + to_string(level + 1), 535, 10, renderer);
    texts.drawText("Deaths " + to_string(deaths), 265, 10, renderer);
}

// Actualizar elementos del juego

void States::update(float deltaTime)
{
    // Actualizar fondo y jugador
    background.update(deltaTime);
    for (int p = 0; p < numPlayers; p++)
    {
        if (!player[p]->endDeadAnimation())
        {
            player[p]->update(deltaTime);

            // Verificar colisiones del jugador con balas enemigas y obstáculos
            if (!player[p]->isDead() && !player[p]->isInmortal())
            {
                int ind = player[p]->isPlayerHit(gameLevels[level]->bulletsEnemy);
                if (ind > -1)
                {
                    gameLevels[level]->bulletsToRemove.push_back(ind);
                    audioPlayer->Play(1, 128);
                    deaths++;
                }
                ind = player[p]->isPlayerHitObstacle(gameLevels[level]->asteroids);
                if (ind > -1)
                {
                    gameLevels[level]->asteroids[ind]->reduceLife();
                    audioPlayer->Play(1, 128);
                    deaths++;
                }
                ind = player[p]->isPlayerHitEnemy(gameLevels[level]->enemies[gameLevels[level]->numParts]);
                if (ind > -1)
                {
                    gameLevels[level]->enemies[gameLevels[level]->numParts][ind]->reduceLife();
                    audioPlayer->Play(1, 128);
                    deaths++;
                }
            }
            for (int i = 0; i < gameLevels[level]->powerUps.size(); i++)
                if (gameLevels[level]->powerUps[i]->isCollisionPlayer(player[p]))
                {
                    gameLevels[level]->powerUps[i]->setPowerEffect(player[p]);
                    gameLevels[level]->powerUpsToRemove.push_back(i);
                }
        }
    }
    bulletsPlayerEvents(deltaTime);
    if (numPlayers > 1 && !player[0]->isDead())
    {
        if (player[0]->getX1HitBox() < player[1]->getX2HitBox() && player[0]->getX2HitBox() > player[1]->getX1HitBox() &&
            player[0]->getY1HitBox() < player[1]->getY2HitBox() && player[0]->getY2HitBox() > player[1]->getY1HitBox())
        {
            player[0]->kill();
            player[1]->kill();
            audioPlayer->Play(1, 128); audioPlayer->Play(1, 128);
        }
    }
    if (startCoolDown <= 0)
        if (!passingLevel)
        {
            gameLevels[level]->update(bulletsPlayer, player, numPlayers, deltaTime);
            checkPartFinish();
        }
    if (delayPart > 0)
        delayPart -= deltaTime * 15;
    if (delayLevel > 0)
        delayLevel -= deltaTime * 15;
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
            for (int p = 0; p < numPlayers; p++)
            {
                if (player[p]->getNumSpecialAttack() < 3 && !player[p]->isDead())
                    player[p]->increaseNumSpecialAttack();
                if (player[p]->isDead())
                {
                    if (p == 0)
                    {
                        Player* newPlay = new Player(player[0]->getTextures(), 310, 460);
                        newPlay->setNumSpecialAttack(player[0]->getNumSpecialAttack());
                        player[p] = newPlay;
                    }
                    else
                    {
                        Player* newPlay = new Player2(player[1]->getTextures(), 400, 460);
                        newPlay->setNumSpecialAttack(player[1]->getNumSpecialAttack());
                        player[p] = newPlay;
                    }
                }
            }
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
            gameLevels[level]->setScore(gameLevels[level - 1]->getScore());
            totalScore = gameLevels[level]->getScore();
        }
    }
}

void States::deadEvent(SDL_Renderer* renderer)
{
    if (continueLevel)
    {
        Player* newPlay = new Player(player[0]->getTextures(), 310, 460);
        newPlay->setNumSpecialAttack(player[0]->getNumSpecialAttack());
        player[0] = newPlay;
        if (numPlayers > 1)
        {
            Player* newPlay2 = new Player2(player[1]->getTextures(), 400, 460);
            newPlay2->setNumSpecialAttack(player[1]->getNumSpecialAttack());
            player[1] = newPlay2;
        }
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

void States::updateInput(SDL_Keycode key)
{
    player[0]->move(key);
    switch (key)
    {
        case SDLK_SPACE:
            PlayerShot[0] = true;
            if (player[0]->endDeadAnimation())
                continueLevel = true;
            break;
        case SDLK_e:
            if (player[0]->getNumSpecialAttack() > 0)
            {
                player[0]->setSpecialAttackShot(true);
                player[0]->reduceNumSpecialAttack();
            }
            break;
    }
    if (numPlayers > 1)
    {
        player[1]->move(key);
        switch (key)
        {
        case SDLK_RSHIFT:
            PlayerShot[1] = true;
            break;
        case SDLK_i:
                if (player[1]->getNumSpecialAttack() > 0)
                {
                    player[1]->setSpecialAttackShot(true);
                    player[1]->reduceNumSpecialAttack();
                }
            break;
        }
    }
}

// Manejar liberación de teclas

void States::inputUp(SDL_Keycode key)
{
    // Desactivar disparo al soltar la tecla de espacio
    if (key == SDLK_SPACE)
        PlayerShot[0] = false;
    else
        player[0]->stop(key);
    if(numPlayers > 1)
        if (key == SDLK_RSHIFT)
            PlayerShot[1] = false;
        else
            player[1]->stop(key);

}
