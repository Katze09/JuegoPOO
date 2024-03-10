// States.cpp

#include "States.h"
#include "Loader.h"

using namespace std;

// Instance of the loader
Loader loader;

// Constructor of States that initializes various game components
States::States(SDL_Renderer* renderer)
{
    // Initialize the audio player
    audioPlayer = new AudioPlayer();

    // Initialize text objects with different font sizes (VerminVibes1989)
    texts = Texts("VerminVibes1989", 40);
    textsTitle = Texts("VerminVibes1989", 70);

    spriteBullet = loader.LoadTexture("Bullet", renderer);

    shop = Shop(renderer);

    // Load player textures and create player instances
    string nameFile[10];
    nameFile[0] = "Player";
    nameFile[1] = "Shield";
    nameFile[2] = "Died";
    textures = loader.loadTextures(nameFile, renderer, 3);

    specialAttackTexture = loader.LoadTexture("SpecialAttack", renderer);
    shieldItemTexture = loader.LoadTexture("Shield1", renderer);

    player[0] = new Player(textures, 310, 460);
    textures.clear(); // Clear textures after use

    // Load background texture
    background = Background(loader.LoadTexture("Background", renderer));

    cooldownShot[0] = cooldownShot[1] = 0;
    passingLevel = PlayerShot[0] = PlayerShot[1] = false;
    level = 0;
    startCoolDown = 80;
    deaths = totalScore = delayLevel = delayPart = 0;

    // Load game levels
    Level* levelLod;
    while ((levelLod = loader.LoadLevel(level + 1, renderer, audioPlayer)) != nullptr)
    {
        gameLevels[level] = levelLod;
        level++;
    }
    maxLevel = level - 1;
    level = 0;

    shopTime = false;
    pastPart = false;
    continueLevel = false;
    win = false;
    numJoySticks = SDL_NumJoysticks();
    cout << "Num Joys: " << numJoySticks << endl;
    //numJoySticks = 0;
    for (int i = 0; i < numJoySticks; i++)
        joys[i] = new JoyStick(SDL_JoystickOpen(i));
}

States::~States()
{
    // Destructor to release memory
    delete audioPlayer;
    for (int i = 0; i < 2; ++i)
        delete player[i];
    for (int i = 0; i < bulletsPlayer.size(); ++i)
        delete bulletsPlayer[i];
    for (int i = 0; i < 2; ++i)
        delete gameLevels[i];
    for (int i = 0; i < numJoySticks; i++)
        delete joys[i];
}

void States::setPlayer2(SDL_Renderer* renderer)
{
    // Set up Player 2 with textures
    string nameFile[10];
    nameFile[0] = "Player2";
    nameFile[1] = "Shield";
    nameFile[2] = "Died";
    numPlayers++;
    player[1] = new Player2(loader.loadTextures(nameFile, renderer, 3), 400, 460);
}

// Handle events related to player bullets
void States::bulletsPlayerEvents(float deltaTime)
{
    for (int p = 0; p < numPlayers; p++)
    {
        if (PlayerShot[p] && cooldownShot[p] <= 0 && !player[p]->isDead())
        {
            // Create bullets when space is pressed and cooldown has ended
            if (player[p]->haveDoubleShot() || player[p]->haveItemDoubleShot())
            {
                // Create double bullets
                bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player[p]->getX1() + 10, player[p]->getY1() + 10, true, player[p]->getBulletSpeed()));
                bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player[p]->getX1() + 30, player[p]->getY1() + 10, true, player[p]->getBulletSpeed()));
                bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player[p]->getX1() + 40, player[p]->getY1() + 10, true, player[p]->getBulletSpeed()));
                bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player[p]->getX1() + 60, player[p]->getY1() + 10, true, player[p]->getBulletSpeed()));
                audioPlayer->Play(0, 100);
                audioPlayer->Play(0, 100);
            }
            else
            {
                // Create single bullets
                bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player[p]->getX1() + 12, player[p]->getY1() + 10, true, player[p]->getBulletSpeed()));
                bulletsPlayer.push_back(new BulletPlayer(spriteBullet, player[p]->getX1() + 47, player[p]->getY1() + 10, true, player[p]->getBulletSpeed()));
                audioPlayer->Play(0, 100);
            }
            cooldownShot[p] = player[p]->getCoolDownShot(); // Set cooldown
        }

        // Handle special attack shot
        if (player[p]->haveSpecialAttackShot() && !player[p]->isDead())
        {
            // Create special attack bullets
            int numShot = 50;
            for (int i = 0; i < numShot; ++i)
            {
                float radius = 100;
                float angle = (2 * M_PI / numShot) * i;  // Equidistant angle
                float x = (player[p]->getX1() + 30) + (radius * cos(angle) / 2);
                float y = (player[p]->getY1() + 25) + (radius * sin(angle) / 2);
                float targetX = player[p]->getX1() + 2 * radius * cos(angle);
                float targetY = player[p]->getY1() + 2 * radius * sin(angle);
                bulletsPlayer.push_back(new BulletPlayerSpecial(spriteBullet, x, y, targetX, targetY, player[p]->getBulletSpeed() / 1.5));
                audioPlayer->Play(0, 100);
            }
            player[p]->setSpecialAttackShot(false);
        }

        // Count cooldown
        if (cooldownShot[p] > 0)
            cooldownShot[p] -= 15 * deltaTime;
    }

    // Remove bullets that are off-screen
    for (int i = bulletsPlayer.size() - 1; i >= 0; --i)
        if (bulletsPlayer[i]->getY1() <= -10)
            bulletsPlayer.erase(bulletsPlayer.begin() + i);

    // Update bullet movements
    for (int i = 0; i < bulletsPlayer.size(); i++)
        bulletsPlayer[i]->update(deltaTime);
}

// Draw game elements on the renderer
void States::draw(SDL_Renderer* renderer)
{
    if (!shopTime)
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
        }
        else
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
            //Special attack draw
            int x = 30;
            if (p == 1)
                x = 500;
            for (int i = 0; i < player[p]->getNumSpecialAttack(); i++)
            {
                SDL_Rect destRect = { x, 730, 50, 50 };
                SDL_RenderCopy(renderer, specialAttackTexture, NULL, &destRect);
                x += 60;
            }
            //Item Shild draw
            x = 30;
            if (p == 1)
                x = 500;
            for (int i = 0; i < player[p]->getNumItemShield(); i++)
            {
                SDL_Rect destRect = { x, 660, 50, 50 };
                SDL_RenderCopy(renderer, shieldItemTexture, NULL, &destRect);
                x += 60;
            }
        }
        if (numPlayers > 1)
        {
            if (player[0]->isDead() && player[1]->isDead())
                deadEvent(renderer);
        }
        else if (player[0]->isDead())
            deadEvent(renderer);
        texts.drawText("Score " + to_string(gameLevels[level]->getScore()), 10, 10, renderer);
        texts.drawText("Level " + to_string(level + 1), 535, 10, renderer);
        texts.drawText("Deaths " + to_string(deaths), 265, 10, renderer);
    }
    else
        shop.draw(renderer);
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
                    audioPlayer->Play(1, 250);
                    deaths++;
                    if (player[p]->haveItemDoublePoints() || player[p]->haveItemDoubleShot() || player[p]->haveItemPowerShopItem())
                    {
                        player[p]->setItemDoublePoints(false);
                        player[p]->setItemDoubleShot(false);
                        player[p]->setItemPowerShopItem(false);
                    }
                }
                ind = player[p]->isPlayerHitObstacle(gameLevels[level]->asteroids);
                if (ind > -1)
                {
                    gameLevels[level]->asteroids[ind]->reduceLife();
                    audioPlayer->Play(1, 250);
                    deaths++;
                    if (player[p]->haveItemDoublePoints() || player[p]->haveItemDoubleShot() || player[p]->haveItemPowerShopItem())
                    {
                        player[p]->setItemDoublePoints(false);
                        player[p]->setItemDoubleShot(false);
                        player[p]->setItemPowerShopItem(false);
                    }
                }
                ind = player[p]->isPlayerHitEnemy(gameLevels[level]->enemies[gameLevels[level]->numParts]);
                if (ind > -1)
                {
                    gameLevels[level]->enemies[gameLevels[level]->numParts][ind]->reduceLife();
                    audioPlayer->Play(1, 250);
                    deaths++;
                    if (player[p]->haveItemDoublePoints() || player[p]->haveItemDoubleShot() || player[p]->haveItemPowerShopItem())
                    {
                        player[p]->setItemDoublePoints(false);
                        player[p]->setItemDoubleShot(false);
                        player[p]->setItemPowerShopItem(false);
                    }
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
        if (!player[1]->isDead())
            if (player[0]->getX1HitBox() < player[1]->getX2HitBox() && player[0]->getX2HitBox() > player[1]->getX1HitBox() &&
                player[0]->getY1HitBox() < player[1]->getY2HitBox() && player[0]->getY2HitBox() > player[1]->getY1HitBox())
            {
                player[0]->kill();
                player[1]->kill();
                audioPlayer->Play(1, 250); audioPlayer->Play(1, 128);
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
    if (delayLevel > 0 && !shopTime)
        delayLevel -= deltaTime * 15;
    else
    {
        shop.update(deltaTime);
        if (shop.endShop)
            shopTime = false;
    }
    if (startCoolDown > 0)
        startCoolDown -= deltaTime * 25;
    updateInputJoyStick();
}

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
        if (gameLevels[level]->numParts == gameLevels[level]->maxnumParts)
        {
            gameLevels[level]->asteroids.clear();
            gameLevels[level]->powerUpsToRemove.clear();
            gameLevels[level]->powerUps.clear();
            gameLevels[level]->bulletsEnemy.clear();
            gameLevels[level]->bulletsToRemove.clear();
            passingLevel = true;
            delayLevel = 80;
            shop.startShopping(gameLevels[level]->getScore(), player, numPlayers);
            for (int p = 0; p < numPlayers; p++)
            {
                if (player[p]->haveItemDoublePoints() || player[p]->haveItemDoubleShot() || player[p]->haveItemPowerShopItem())
                {
                    player[p]->setItemDoublePoints(false);
                    player[p]->setItemDoubleShot(false);
                    player[p]->setItemPowerShopItem(false);
                }
                if (player[p]->getNumSpecialAttack() < 3 && !player[p]->isDead())
                    player[p]->increaseNumSpecialAttack();
                if (player[p]->isDead())
                {
                    if (p == 0)
                    {
                        Player* newPlay = new Player(player[0]->getTextures(), 310, 460);
                        newPlay->setNumSpecialAttack(player[0]->getNumSpecialAttack());
                        newPlay->setNumItemShield(player[0]->getNumItemShield());
                        player[p] = newPlay;
                    }
                    else
                    {
                        Player* newPlay = new Player2(player[1]->getTextures(), 400, 460);
                        newPlay->setNumSpecialAttack(player[1]->getNumSpecialAttack());
                        newPlay->setNumItemShield(player[1]->getNumItemShield());
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
    if (delayLevel > 60)
        textsTitle.drawText("Level " + to_string(level + 1) + " Passed", 100, 300, renderer);
    else if (delayLevel > 30 && delayLevel < 50)
    {
        textsTitle.drawText("Shopping Time", 120, 300, renderer);
        //textsTitle.drawText("Level " + to_string(level + 2) + " Start", 100, 300, renderer);
    }else if (delayLevel < 30 && !shop.endShop)
    {
        shopTime = true;
    } else if (delayLevel < 20)
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
            //gameLevels[level]->setScore(gameLevels[level - 1]->getScore());
            gameLevels[level]->setScore(shop.getRemainingScore());
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
        newPlay->setNumItemShield(player[0]->getNumItemShield());
        player[0] = newPlay;
        if (numPlayers > 1)
        {
            Player* newPlay2 = new Player2(player[1]->getTextures(), 400, 460);
            newPlay2->setNumSpecialAttack(player[1]->getNumSpecialAttack());
            newPlay2->setNumItemShield(player[1]->getNumItemShield());
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

void States::updateInputJoyStick()
{
    if (numJoySticks == 2 && numPlayers == 2)
    {
        for (int i = 0; i < numPlayers; i++)
        {
            player[i]->setDirecionJoy(joys[i]->joyDirection());
            if (joys[i]->buttonAShot())
            {
                if (player[0]->endDeadAnimation() && !PlayerShot[i])
                    continueLevel = true;
                PlayerShot[i] = true;
            } else
                PlayerShot[i] = false;
            if (joys[i]->buttonBSpecial() && !alreadyUse[i])
            {
                if (player[i]->getNumSpecialAttack() > 0)
                {
                    player[i]->setSpecialAttackShot(true);
                    player[i]->reduceNumSpecialAttack();
                    alreadyUse[i] = true;
                }
            }else if(!joys[i]->buttonBSpecial())
                alreadyUse[i] = false;
            if (joys[i]->buttonXItemShield() && !alreadyUse[i + 1])
            {
                if (player[i]->getNumItemShield() > 0)
                {
                    player[i]->setInmortal(true);
                    player[i]->activePowerUps[1] = true;
                    player[i]->timeLeftPowerUp[1] = 50;
                    player[i]->flashingShield = true;
                    player[i]->reduceNumItemShield();
                    alreadyUse[i + 1] = true;
                }
            }else if(!joys[i]->buttonXItemShield())
                alreadyUse[i + 1] = false;
        }
    } else if (numJoySticks == 1)
    {
        player[0]->setDirecionJoy(joys[0]->joyDirection());
        if (joys[0]->buttonAShot())
        {
            if (player[0]->endDeadAnimation() && !PlayerShot[0])
                continueLevel = true;
            PlayerShot[0] = true;
        } else
            PlayerShot[0] = false;
        if (joys[0]->buttonBSpecial() && !alreadyUse[0])
        {
            if (player[0]->getNumSpecialAttack() > 0)
            {
                player[0]->setSpecialAttackShot(true);
                player[0]->reduceNumSpecialAttack();
                alreadyUse[0] = true;
            }
        }
        else if (!joys[0]->buttonBSpecial())
            alreadyUse[0] = false;
        if (joys[0]->buttonXItemShield() && !alreadyUse[1])
        {
            if (player[0]->getNumItemShield() > 0)
            {
                player[0]->setInmortal(true);
                player[0]->activePowerUps[1] = true;
                player[0]->timeLeftPowerUp[1] = 50;
                player[0]->flashingShield = true;
                player[0]->reduceNumItemShield();
                alreadyUse[0] = true;
            }
        }
        else if (!joys[0]->buttonXItemShield())
            alreadyUse[1] = false;
    }
}

void States::updateInput(SDL_Keycode key)
{
    if (numJoySticks == 0)
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
        case SDLK_q:
            if (player[0]->getNumItemShield() > 0)
            {
                player[0]->setInmortal(true);
                player[0]->activePowerUps[1] = true;
                player[0]->timeLeftPowerUp[1] = 50;
                player[0]->flashingShield = true;
                player[0]->reduceNumItemShield();
            }
            break;
        }
    }
    if (numPlayers > 1 && numJoySticks < 2)
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
        case SDLK_y:
            if (player[1]->getNumItemShield() > 0)
            {
                player[1]->setInmortal(true);
                player[1]->activePowerUps[1] = true;
                player[1]->timeLeftPowerUp[1] = 50;
                player[1]->flashingShield = true;
                player[1]->reduceNumItemShield();
            }
            break;
        }
    }
}

void States::inputUp(SDL_Keycode key)
{
    // Desactivar disparo al soltar la tecla de espacio
    if (numJoySticks == 0)
    {
        if (key == SDLK_SPACE)
            PlayerShot[0] = false;
        else
            player[0]->stop(key);
    }
    if(numPlayers > 1 && numJoySticks < 2)
        if (key == SDLK_RSHIFT)
            PlayerShot[1] = false;
        else
            player[1]->stop(key);

}

void States::mouseClick(int x, int y)
{
    if (shopTime)
        shop.click(x, y);
}

void States::mouseMove(int x, int y)
{
    if (shopTime)
        shop.hover(x, y);
}
