// States.cpp

#include "States.h"
#include "Loader.h"

Loader loader; // Instancia del cargador

// Constructor de States que inicializa varios componentes del juego
States::States(SDL_Renderer* renderer)
{
    // Inicializar el reproductor de audio
    audioPlayer = new AudioPlayer();

    // Inicializar objetos de texto con diferentes tamaños de fuente
    texts = Texts("8-bit ArcadeIn", 40);
    textsTitle = Texts("8-bit ArcadeIn", 80);

    // Cargar textura para la bala del jugador
    spriteBullet = loader.LoadTexture("Bullet", renderer);

    // Cargar texturas para el jugador y su animación de muerte
    string nameFile[10];
    nameFile[0] = "Player";
    nameFile[1] = "Died";
    textures = loader.loadTextures(nameFile, renderer, 2);

    // Crear jugador en la posición inicial
    player = new Player(textures, 250, 250);
    textures.clear(); // Limpiar texturas después de su uso

    // Inicializar el fondo del juego
    background = Background(loader.LoadTexture("Background", renderer));

    // Inicializar variables de control del juego
    cooldownShot = 0;
    passingLevel = PlayerShot = false;
    level = 0;
    delayLevel = delayPart = 0;

    // Cargar niveles de juego
    for (level; level < 2; level++)
        gameLevels[level] = loader.LoadLevel((level + 1), renderer, audioPlayer);

    level = 0;
    pastPart = false;
}

// Manejar eventos relacionados con las balas del jugador
void States::bulletsPlayerEvents(double deltaTime)
{
    if (PlayerShot && cooldownShot <= 0 && !player->isDead())
    {
        // Crear balas si se presiona el espacio y el cooldown ha terminado
        bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player->getX1() + 3, player->getY1() + 10, true));
        bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player->getX1() + 37, player->getY1() + 10, true));

        // Establecer cooldown y reproducir sonido de disparo
        cooldownShot = 2;
        audioPlayer->Play(0, 100);
    }

    // Eliminar balas del vector cuando salen de la pantalla
    for (int i = 0; i < bulletsPlayer.size(); i++)
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
    player->draw(renderer);
    for (int i = 0; i < bulletsPlayer.size(); i++)
        bulletsPlayer[i]->draw(renderer);
    gameLevels[level]->draw(renderer);

    // Mostrar información de puntuación en la pantalla
    if (passingLevel)
    {
        passLevel(renderer);
    }
    texts.drawText("Score " + to_string(gameLevels[level]->getScore()), 10, 10, renderer);
}

// Actualizar elementos del juego
void States::update(double deltaTime)
{
    // Actualizar fondo y jugador
    background.update(deltaTime);
    player->update(deltaTime);

    // Verificar colisiones del jugador con balas enemigas y obstáculos
    if(player->isPlayerHit(gameLevels[level]->bulletsEnemy) > -1)
        audioPlayer->Play(1,100);
    if(player->isPlayerHitObstacle(gameLevels[level]->asteroids) > -1)
        audioPlayer->Play(1,100);

    // Manejar eventos relacionados con las balas del jugador
    bulletsPlayerEvents(deltaTime);

    // Actualizar nivel actual si no se está pasando de nivel
    if (!passingLevel)
    {
        gameLevels[level]->update(bulletsPlayer, deltaTime);
        checkPartFinish();
    }

    // Contar tiempo de retardo entre partes del nivel y niveles
    if (delayPart > 0)
        delayPart -= deltaTime * 15;
    if (delayLevel > 0)
        delayLevel -= deltaTime * 15;
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
    if (delayLevel <= 0)
    {
        passingLevel = false;
        level++;
    }

    // Mostrar mensajes de nivel pasado y próximo nivel
    if(delayLevel > 30)
        textsTitle.drawText("Level " + to_string(level + 1) + " Passed", 100, 400, renderer);
    else if(delayLevel < 20)
        textsTitle.drawText("Level " + to_string(level + 2) + " Start", 100, 400, renderer);
}

// Actualizar entrada del jugador
void States::updateInput(SDL_Keycode key)
{
    // Mover jugador y activar disparo al presionar teclas
    player->move(key);
    if (key == SDLK_SPACE)
        PlayerShot = true;
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
