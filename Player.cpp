// Player.cpp
#include "Player.h"

Player::Player() : Object()
{
}

Player::Player(vector<SDL_Texture*> textures, float X1, float Y1) : Object(textures, X1, Y1)
{
    speed = 500;
    hitBoxMultiplication = 0.2;
    bulletSpeed = 1000;
    coolDownShot = 2;
    normalSpeedCool = 2;
    floatShot = inmortal = false;
    up = false;
    down = false;
    right = false;
    left = false;
    dead = false;
}

Player::~Player()
{
    // Destructor de Player
}

int Player::isPlayerHit(vector<BulletEnemy*> bulletsEnemy)
{
    for (int i = 0; i < bulletsEnemy.size(); i++)
        if (bulletsEnemy[i]->getX1HitBox() < X2HitBox && bulletsEnemy[i]->getX2HitBox() > X1HitBox &&
                bulletsEnemy[i]->getY1HitBox() < Y2HitBox && bulletsEnemy[i]->getY2HitBox() > Y1HitBox)
        {
            dead = true;
            speedAnimations = 1;
            return i;
        }
    return -1;
}

int Player::isPlayerHitObstacle(vector<Obstacle*> obstacle)
{
    for (int i = 0; i < obstacle.size(); i++)
        if (obstacle[i]->getX1HitBox() < X2HitBox && obstacle[i]->getX2HitBox() > X1HitBox &&
                obstacle[i]->getY1HitBox() < Y2HitBox && obstacle[i]->getY2HitBox() > Y1HitBox)
        {
            dead = true;
            speedAnimations = 1;
            return i;
        }
    return -1;
}

int Player::isPlayerHitEnemy(vector<EnemyBase*> enemy)
{
    for (int i = 0; i < enemy.size(); i++)
        if (enemy[i]->getX1HitBox() < X2HitBox && enemy[i]->getX2HitBox() > X1HitBox &&
            enemy[i]->getY1HitBox() < Y2HitBox && enemy[i]->getY2HitBox() > Y1HitBox)
        {
            dead = true;
            speedAnimations = 1;
            return i;
        }
    return -1;
}

void Player::move(SDL_Keycode key)
{
    switch (key)
    {
    case SDLK_d:
        right = true;
        break;
    case SDLK_a:
        left = true;
        break;
    case SDLK_w:
        up = true;
        break;
    case SDLK_s:
        down = true;
        break;
    } 
}

void Player::collisionBorder()
{
    if (X1 <= 0)
        Player::setX(0);
    if (X2 >= 700)
        Player::setX(630);
    if (Y1 < 0)
        Player::setY(0);
    if (Y2 >= 800)
        Player::setY(730);
}

void Player::stop(SDL_Keycode key)
{
    switch (key)
    {
        case SDLK_d:
            right = false;
            break;
        case SDLK_a:
            left = false;
            break;
        case SDLK_w:
            up = false;
            break;
        case SDLK_s:
            down = false;
            break;
    }
}

void Player::animationBase(float deltaTime)
{
    if (!dead)
    {
        speedAnimations -= 5 * deltaTime;
        if (speedAnimations <= 0)
        {
            indexTexture++;
            speedAnimations = 1;
        }
        if (indexTexture == 3)
            indexTexture = 0;
    }
}

void Player::animationDead(float deltaTime)
{
    if (dead && !deadAnimationEnd)
    {
        speedAnimations -= 15 * deltaTime;
        if (indexTexture < textures.size() - 3)
            indexTexture = textures.size() - 3;
        if (speedAnimations <= 0)
        {
            indexTexture++;
            speedAnimations = 1;
        }
        if (indexTexture == textures.size() - 1)
            deadAnimationEnd = true;
    }
}

void Player::timeLetfPowerUps(float deltaTime)
{
    for (int i = 0; i < 4; i++)
        if (activePowerUps[i])
        {
            timeLeftPowerUp[i] -= 15 * deltaTime;
            if (timeLeftPowerUp[i] <= 0)
            {
                activePowerUps[i] = false;
                switch (i)
                {
                    case 0:
                        coolDownShot = 2;
                        break;
                    case 1:
                        inmortal = false;
                        break;
                    case 2:
                        floatShot = false;
                        break;
                    case 3:
                        floatPoints = false;
                        break;
                }
            }
        }
}

void Player::update(float deltaTime)
{
    this->deltaTime = deltaTime;
    float speedScale = 1.0;
    if (normalSpeedCool >= 0)
    {
        // Utilizar una función cuadrática para suavizar la transición
        speedScale = 1.0 - (normalSpeedCool / (2.0));
        normalSpeedCool -= deltaTime * 15;
    }
    float speed = this->speed * speedScale;
    if (right)
        setX(X1 + (speed * deltaTime));
    if (left)
        setX(X1 - (speed * deltaTime));
    if (up)
        setY(Y1 - (speed * deltaTime));
    if (down)
        setY(Y1 + (speed * deltaTime));
    if (!right && !left && !up && !down)
        normalSpeedCool = 2;
    if (flashingDelay > 0)
        flashingDelay -= deltaTime * 15;
    if (timeLeftPowerUp[1] < 15 && inmortal && flashingDelay <= 0)
    {
        flashingDelay = 2.5;
        flashingShield = !flashingShield;
    }
    timeLetfPowerUps(deltaTime);
    collisionBorder();
    animationBase(deltaTime);
    animationDead(deltaTime);
}

void Player::draw(SDL_Renderer* renderer)
{
    SDL_Rect destRect = {static_cast<int> (X1), static_cast<int> (Y1), WIDTH, HEIGHT};
    SDL_RenderCopy(renderer, textures[indexTexture], NULL, &destRect);
    if (inmortal && flashingShield)
    {
        destRect = {static_cast<int> (X1 - 10), static_cast<int> (Y1 - 10), 90, 90};
        SDL_RenderCopy(renderer, textures[3], NULL, &destRect);
    }
}

Player2::Player2() : Player()
{
}

Player2::Player2(vector<SDL_Texture*> textures, float X1, float Y1) : Player(textures, X1, Y1)
{
    
}

Player2::~Player2()
{
    // Destructor de Player
}

void Player2::move(SDL_Keycode key)
{
    switch (key)
    {
        case SDLK_k:
            right = true;
            break;
        case SDLK_h:
            left = true;
            break;
        case SDLK_u:
            up = true;
            break;
        case SDLK_j:
            down = true;
            break;
    }
}

void Player2::stop(SDL_Keycode key)
{
    switch (key)
    {
        case SDLK_k:
            right = false;
            break;
        case SDLK_h:
            left = false;
            break;
        case SDLK_u:
            up = false;
            break;
        case SDLK_j:
            down = false;
            break;
    }
}
