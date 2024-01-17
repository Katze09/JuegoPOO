// States.cpp
#include "States.h"
#include "Loader.h"

Loader loader;
//Asteroid aste;

States::States(SDL_Renderer* renderer)
{
    texts = Texts("8-bit ArcadeIn", 40);
    score = 0;
    spriteBullet = loader.LoadTexture("Bullet", renderer);
    //vector<SDL_Texture*> textures;
    string nameFile[10];
    nameFile[0] = "Player";
    textures = loader.loadTextures(nameFile, renderer, 1);
    player = Player(textures, 250, 250);
    textures.clear();
    background = Background(loader.LoadTexture("Background", renderer));
    cooldownShot = 0;
    PlayerShot = false;
    level = 0;
    gameLevels[level] = loader.LoadLevel(1, renderer);
}

void States::bulletsPlayerEvents(double deltaTime)
{
    if (PlayerShot && cooldownShot <= 0) //Crear bala si se presiona el espacio y cooldown se termino
    {
        bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player.getX1() + 3, player.getY1() + 10, true)); //Crear bala en el vector
        bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player.getX1() + 37, player.getY1() + 10, true)); //Crear bala en el vector
        cooldownShot = 2; //Ajusta el tiempo entre disparo
    }
    //Eliminar Bullets del vector cuando estas salgan de pantalla
    for (int i = 0; i < bulletsPlayer.size(); i++)
        if (bulletsPlayer[i]->getY1() <= -10)
            bulletsPlayer.erase(bulletsPlayer.begin() + i);
    //Update Bullets para el movimiento
    for (int i = 0; i < bulletsPlayer.size(); i++)
        bulletsPlayer[i]->update(deltaTime);
    if (cooldownShot > 0) //Contar para cooldown
        cooldownShot -= 15 * deltaTime;
}

void States::draw(SDL_Renderer* renderer)
{
    background.draw(renderer);
    player.draw(renderer);
    for (int i = 0; i < bulletsPlayer.size(); i++)
        bulletsPlayer[i]->draw(renderer);
    gameLevels[level]->draw(renderer);
    texts.drawText("Score " + to_string(score), 10, 10, renderer);
}

void States::update(double deltaTime)
{
    background.update(deltaTime);
    player.update(deltaTime);
    bulletsPlayerEvents(deltaTime);
    gameLevels[level]->update(bulletsPlayer, deltaTime);
    checkPartFinish();
}

void States::checkPartFinish()
{
    if(gameLevels[level]->enemies[gameLevels[level]->numParts].size() <= 0)
        gameLevels[level]->numParts++;
}

void States::updateInput(SDL_Keycode key)
{
    player.move(key);
    if (key == SDLK_SPACE)
        PlayerShot = true;
}

void States::inputUp(SDL_Keycode key)
{
    if (key == SDLK_SPACE)
        PlayerShot = false;
    else
        player.stop(key);
}
