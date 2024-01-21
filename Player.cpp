// Player.cpp
#include "Player.h"

Player::Player() : Object()
{
}

Player::Player(vector<SDL_Texture*> textures, float X1, float Y1)
: Object(textures, X1, Y1)
{
    speed = 500;
    X1HitBox = X1 + (WIDTH * 0.3);
    X2HitBox = X2 - (WIDTH * 0.3);
    Y1HitBox = Y1 + (HEIGHT * 0.3);
    Y2HitBox = Y2 - (HEIGHT * 0.3);
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

int Player::isPlayerHitObstacle(vector<Obstacle*> asteroids)
{
    for(int i = 0; i < asteroids.size();i++)
    if (asteroids[i]->getX1HitBox() < X2HitBox && asteroids[i]->getX2HitBox() > X1HitBox &&
                asteroids[i]->getY1HitBox() < Y2HitBox && asteroids[i]->getY2HitBox() > Y1HitBox)
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
        Player::setX(650);
    if (Y1 < 0)
        Player::setY(0);
    if (Y2 >= 800)
        Player::setY(750);
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
    if(!dead)
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

void Player::update(double deltaTime)
{
    this->deltaTime = deltaTime;
    if (right)
        setX(X1 + (speed * deltaTime));
    if (left)
        setX(X1 - (speed * deltaTime));
    if (up)
        setY(Y1 - (speed * deltaTime));
    if (down)
        setY(Y1 + (speed * deltaTime));
    collisionBorder();
    animationBase(deltaTime);
    animationDead(deltaTime);
}

bool Player::isDead()
{
    return dead;
}
