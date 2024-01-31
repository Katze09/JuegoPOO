// Player.cpp
#include "Player.h"

Player::Player() : Object()
{
}

Player::Player(vector<SDL_Texture*> textures, float X1, float Y1, bool player1)
: Object(textures, X1, Y1)
{
    speed = 500;
    hitBoxMultiplication = 0.2;
    cout << "X1: " << X1 << " X2: "<< X2 << " Y1: " << Y1 << " Y2: " << Y2 << endl;
    cout << "X1Hit: " << X1HitBox << " X2Hit: "<< X2HitBox << " Y1Hit: " << Y1HitBox << " Y2Hit: " << Y2HitBox << endl;
    bulletSpeed = 1000;
    coolDownShot = 2;
    normalSpeedCool = 2;
    this->player1 = player1;
    doubleShot = inmortal = false;
    activePowerUps[0] = false;
    activePowerUps[1] = false;
    timeLeftPowerUp[0] = 3;
    timeLeftPowerUp[1] = 3;
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
            //isDead();
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
            //isDead();
            return i;
        }
    return -1;
}

void Player::move(SDL_Keycode key)
{
    if(player1)
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
    else
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

void Player::animationBase(double deltaTime)
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

void Player::animationDead(double deltaTime)
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

void Player::timeLetfPowerUps(double deltaTime)
{
    for (int i = 0; i < 3; i++)
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
                        doubleShot = false;
                        break;
                }
            }
        }
}

void Player::update(double deltaTime)
{
    this->deltaTime = deltaTime;
    double speedScale = 1.0;
    if (normalSpeedCool >= 0)
    {
        // Utilizar una función cuadrática para suavizar la transición
        speedScale = 1.0 - (normalSpeedCool / (2.0));
        normalSpeedCool -= deltaTime * 15;
    }
    double speed = this->speed * speedScale;
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
    timeLetfPowerUps(deltaTime);
    collisionBorder();
    animationBase(deltaTime);
    animationDead(deltaTime);
}

bool Player::isDead()
{
    return dead;
}

bool Player::isInmortal()
{
    return inmortal;
}

void Player::setInmortal(bool inmortal)
{
    this->inmortal = inmortal;
}

bool Player::haveDoubleShot()
{
    return doubleShot;
}

void Player::setDoubleShot(bool doubleShot)
{
    this->doubleShot = doubleShot;
}

int Player::getBulletSpeed()
{
    return bulletSpeed;
}

void Player::setBulletSpeed(int bulletSpeed)
{
    this->bulletSpeed = bulletSpeed;
}

int Player::getCoolDownShot()
{
    return coolDownShot;
}

void Player::setCoolDownShot(int coolDownShot)
{
    this->coolDownShot = coolDownShot;
}
