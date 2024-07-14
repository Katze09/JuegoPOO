#include <vector>

#include "Enemies.h"
#include "Loader.h"

using namespace std;

Loader loadEnemys;

EnemyBase::EnemyBase() : Object()
{
}

EnemyBase::EnemyBase(vector<SDL_Texture*> textures, float X1, float Y1, bool direction, int movimentType, int bulletSpeed) : Object(textures, X1, Y1)
{
    life = 1;
    speed = 300;
    this->bulletSpeed = bulletSpeed;
    this->direction = direction;
    coolDownShot = 3;
    this->movimentType = movimentType;
    angle = 0;
    //score = 5;
}

EnemyBase::~EnemyBase()
{
}

int EnemyBase::isEnemyHit(vector<BulletPlayer*> bulletPlayer)
{
    for (int i = 0; i < bulletPlayer.size(); i++)
        if (bulletPlayer[i]->getX1HitBox() < X2HitBox && bulletPlayer[i]->getX2HitBox() > X1HitBox &&
                bulletPlayer[i]->getY1HitBox() < Y2HitBox && bulletPlayer[i]->getY2HitBox() > Y1HitBox)
        {
            life--;
            isDead();
            return i;
        }
    return -1;
}

bool EnemyBase::isDead()
{
    if (life <= 0 && !dead)
    {
        dead = true;
        speedAnimations = 0;
    }
    return dead;
}

void EnemyBase::collisionBorder()
{
    if (direction)
    {
        if (X1 <= -50)
        {
            setX(710);
        }
    } else
    {
        if (X1 >= 750)
        {
            setX(-60);
        }
    }
}

void EnemyBase::update(float deltaTime)
{
    switch (movimentType)
    {
        case 0:
            if (direction)
            {
                setX(X1 - (speed * deltaTime));
                collisionBorder();
            } else
            {
                setX(X1 + (speed * deltaTime));
                collisionBorder();
            }
            break;
        case 1:
            if (direction)
            {
                setY(Y1 + (4.5 * cos(angle)));
                setX(X1 + (4.5 * sin(angle)));
            } else
            {
                setY(Y1 + (4.5 * cos(angle)));
                setX(X1 - (4.5 * sin(angle)));
            }
            angle -= 0.025;
            if (angle >= 2 * M_PI)
                angle = 0.0;
            break;
    }
    animationDead(deltaTime);
}

bool EnemyBase::shot(float deltaTime)
{
    coolDownShot -= 3 * deltaTime;
    if (coolDownShot <= 0)
    {
        coolDownShot = 3;
        return true;
    }
    return false;
}

void EnemyBase::animationBase(float deltaTime)
{
    /*speedAnimations -= speedAnimations * deltaTime;
    if(speedAnimations <= 0)
    {
        indexTexture++;
        speedAnimations = 1;
    }
    if(indexTexture == 3)
        indexTexture = 0;*/
}

void EnemyBase::animationDead(float deltaTime)
{
    if (dead && !deadAnimationEnd)
    {
        speedAnimations -= 15 * deltaTime;
        if (indexTexture < textures.size() - 3)
            indexTexture = textures.size() - 3;
        if (indexTexture == textures.size() - 1 && speedAnimations <= 0)
            deadAnimationEnd = true;
        if (speedAnimations <= 0)
        {
            indexTexture++;
            speedAnimations = 1;
        }
    }
}

int EnemyBase::getBulletSpeed()
{
    return bulletSpeed;
}

int EnemyBase::getScore()
{
    return score;
}

//
// Class enemyLaser
//

EnemyLaser::EnemyLaser() : EnemyBase()
{
}

EnemyLaser::EnemyLaser(vector<SDL_Texture*> textures, float X1, float Y1, bool direction, int movimentType, float moveTo, int bulletSpeed) : EnemyBase(textures, X1, Y1, direction, movimentType, bulletSpeed)
{
    this->moveTo = moveTo;
    firstShot = true;
    laserSize = 0;
}

EnemyLaser::~EnemyLaser()
{
}

bool EnemyLaser::shot(float deltaTime)
{
    if (laserSize >= 150)
    {
        laserSize = 0;
        coolDownShot = 8;
        firstShot = true;
    }
    coolDownShot -= 3 * deltaTime;
    if (coolDownShot <= 0)
    {
        coolDownShot = 0;
        laserSize++;
        return true;
    }
    return false;
}

void EnemyLaser::update(float deltaTime)
{
    if (direction)
    {
        if (X1 >= moveTo)
            setX(X1 - (speed * deltaTime));
        collisionBorder();
    } else
    {
        if (X1 <= moveTo)
            setX(X1 + (speed * deltaTime));
        collisionBorder();
    }
    animationDead(deltaTime);
}

bool EnemyLaser::isFirstShot()
{
    return firstShot;
}

void EnemyLaser::setFirstShot()
{
    firstShot = false;
}

//
// Class enemyStar
//

EnemyStar::EnemyStar() : EnemyLaser()
{
}

EnemyStar::EnemyStar(vector<SDL_Texture*> textures, float X1, float Y1, bool direction, int movimentType, float moveTo, int bulletSpeed)
    : EnemyLaser(textures, X1, Y1, direction, movimentType, moveTo, bulletSpeed)
{
    life = 3;
    coolDownShot = 4;
}

EnemyStar::~EnemyStar()
{
}

bool EnemyStar::shot(float deltaTime)
{
    coolDownShot -= 3 * deltaTime;
    if (coolDownShot <= 0)
    {
        coolDownShot = 6;
        return true;
    }
    return false;
}

void EnemyStar::update(float deltaTime)
{
    if (direction)
    {
        if (X1 >= moveTo)
            setX(X1 - (speed * deltaTime));
        collisionBorder();
    }
    else
    {
        if (X1 <= moveTo)
            setX(X1 + (speed * deltaTime));
        collisionBorder();
    }
    if (indexTexture == 1 && hitTex <= 0)
        indexTexture = 0;
    if (hitTex > 0)
        hitTex -= 15 * deltaTime;
    animationDead(deltaTime);
}

int EnemyStar::isEnemyHit(vector<BulletPlayer*> bulletPlayer)
{
    for (int i = 0; i < bulletPlayer.size(); i++)
        if (bulletPlayer[i]->getX1HitBox() < X2HitBox && bulletPlayer[i]->getX2HitBox() > X1HitBox &&
            bulletPlayer[i]->getY1HitBox() < Y2HitBox && bulletPlayer[i]->getY2HitBox() > Y1HitBox)
        {
            life--;
            indexTexture = 1;
            hitTex = 1;
            isDead();
            return i;
        }
    return -1;
}

//
// Class enemyKamikaze
//

EnemyKamikaze::EnemyKamikaze() : EnemyBase()
{
}

EnemyKamikaze::EnemyKamikaze(vector<SDL_Texture*> textures, float X1, float Y1) : EnemyBase(textures, X1, Y1, false, 0, 0)
{
    
}

EnemyKamikaze::EnemyKamikaze(vector<SDL_Texture*> textures, float X1, float Y1, float speed) : EnemyBase(textures, X1, Y1, false, 0, 0)
{
    this->speed = speed;
}

EnemyKamikaze::~EnemyKamikaze()
{
}

void EnemyKamikaze::update(float deltaTime, float targetX, float targetY)
{
    float dx = targetX - X1;
    float dy = targetY - Y1;
    // Calcular la distancia total al objetivo
    float distance = sqrt(dx * dx + dy * dy);
    if (distance > 0)
    {
        dx /= distance;
        dy /= distance;
    }
    // Calcular el desplazamiento en cada eje
    float deltaX = dx * speed * deltaTime;
    float deltaY = dy * speed * deltaTime;
    float angleInRadians = atan2(deltaY, deltaX);
    angleRotation = (angleInRadians * (180.0 / M_PI) - 90);
    // Asignar las nuevas coordenadas
    setX(X1 + deltaX);
    setY(Y1 + deltaY);
    animationDead(deltaTime);
}


void EnemyKamikaze::draw(SDL_Renderer* renderer)
{
    SDL_Rect destinationRect = { static_cast<int> (X1), static_cast<int> (Y1), WIDTH, HEIGHT };
    SDL_RenderCopyEx(renderer, textures[indexTexture], NULL, &destinationRect, angleRotation, NULL, SDL_FLIP_NONE);
}

//
// Class EnemyMidGuide
//

EnemyMidGuide::EnemyMidGuide() : EnemyMid()
{
}

EnemyMidGuide::EnemyMidGuide(vector<SDL_Texture*> textures, float X1, float Y1, float moveTo, int bulletSpeed)
    : EnemyMid(textures, X1, Y1, moveTo, bulletSpeed)
{
    life = 20;
    move = false;
}

EnemyMidGuide::~EnemyMidGuide()
{
}

void EnemyMidGuide::setAngleRotation(float targetX, float targetY)
{
    float angleInRadians = atan2(targetY, targetX);
    if(X1 > 350)
        angleRotation = (angleInRadians * (180.0 / M_PI) - 50);
    else
        angleRotation = (angleInRadians * (180.0 / M_PI) - 80);
}


bool EnemyMidGuide::shot(float deltaTime)
{
    coolDownShot -= 3 * deltaTime;
    if (coolDownShot <= 0)
    {
        coolDownShot = 6;
        return true;
    }
    return false;
}

void EnemyMidGuide::draw(SDL_Renderer* renderer)
{
    SDL_Rect destinationRect = { static_cast<int> (X1), static_cast<int> (Y1), WIDTH, HEIGHT };
    SDL_RenderCopyEx(renderer, textures[indexTexture], NULL, &destinationRect, angleRotation, NULL, SDL_FLIP_NONE);
}

//
// Class EnemyMid
//

EnemyMid::EnemyMid() : EnemyBase()
{
}

EnemyMid::EnemyMid(vector<SDL_Texture*> textures, float X1, float Y1, float moveTo, int bulletSpeed) : EnemyBase(textures, X1, Y1, false, 0, bulletSpeed)
{
    life = 35;
    hitTex = 0;
    this->moveTo = moveTo;
    //score = 20;
}

EnemyMid::~EnemyMid()
{
}

int EnemyMid::isEnemyHit(vector<BulletPlayer*> bulletPlayer)
{
    for (int i = 0; i < bulletPlayer.size(); i++)
        if (bulletPlayer[i]->getX1HitBox() < X2HitBox && bulletPlayer[i]->getX2HitBox() > X1HitBox &&
                bulletPlayer[i]->getY1HitBox() < Y2HitBox && bulletPlayer[i]->getY2HitBox() > Y1HitBox)
        {
            life--;
            indexTexture = 1;
            hitTex = 1;
            isDead();
            return i;
        }
    return -1;
}

void EnemyMid::update(float deltaTime)
{
    if (Y1 <= moveTo)
        setY(Y1 + (speed * deltaTime));
    else
    {
        if(move)
            if (direction)
            {
                setX(X1 + (speed * deltaTime));
                if (X1 >= 520)
                    direction = false;
            } else
            {
                setX(X1 - (speed * deltaTime));
                if (X1 <= 0)
                    direction = true;
            }
    }
    if (indexTexture == 1 && hitTex <= 0)
        indexTexture = 0;
    if (hitTex > 0)
        hitTex -= 15 * deltaTime;
    animationDead(deltaTime);
}

//
// Class EnemyBoss
//

EnemyBoss::EnemyBoss() : EnemyMid()
{
}

EnemyBoss::EnemyBoss(vector<SDL_Texture*> textures, float X1, float Y1, float moveTo, int bulletSpeed) : EnemyMid(textures, X1, Y1, moveTo, bulletSpeed)
{
    life = 800;
    secondFase = false;
    thirdFase = false;
    secondFaseP2 = false;
    contSecondFaseShot = 1;
}

EnemyBoss::~EnemyBoss()
{
}

void EnemyBoss::update(float deltaTime)
{
    if (Y1 <= moveTo)
        setY(Y1 + (speed * deltaTime));
    if (indexTexture == 1 && hitTex <= 0)
        indexTexture = 0;
    if (hitTex > 0)
        hitTex -= 15 * deltaTime;
    if (secondFase || thirdFase)
    {
        if (direction)
        {
            setX(X1 + (speed * deltaTime));
            if (X1 >= 420)
                direction = false;
        } else
        {
            setX(X1 - (speed * deltaTime));
            if (X1 <= 0)
                direction = true;
        }
    }
    if ((life <= 650 && life >= 550) || (life <= 450 && life >= 350))
        secondFase = true;
    else
        secondFase = false;
    if (life < 550)
        secondFaseP2 = true;
    if (life <= 300 && !secondFase)
    {
        secondFaseP2 = false;
        thirdFase = true;
    }
    animationDead(deltaTime);
}

bool EnemyBoss::shot(float deltaTime)
{
    coolDownShot -= 3 * deltaTime;
    if (coolDownShot <= 0)
    {
        coolDownShot = 1.5;
        if (secondFase)
        {
            coolDownShot = 0.2;
        }
        if (thirdFase && contSecondFaseShot >= 0)
        {
            contSecondFaseShot -= 15 * deltaTime;
            coolDownShot = 0.4;
        } else if (contSecondFaseShot <= 0)
            contSecondFaseShot = 1.5;
        return true;
    }
    return false;
}

EnemySecondBoss::EnemySecondBoss() : EnemyBoss(){}

EnemySecondBoss::EnemySecondBoss(vector<SDL_Texture*> textures, float X1, float Y1, float moveTo, int bulletSpeed) : EnemyBoss(textures, X1, Y1, moveTo, bulletSpeed)
{
    life = 1200;
    secondFase = false;
    thirdFase = false;
    secondFaseP2 = false;
    coolDownShot = 5;
}

EnemySecondBoss::~EnemySecondBoss()
{
}

void EnemySecondBoss::update(float deltaTime)
{
    if (indexTexture == 1 && hitTex <= 0)
        indexTexture = 0;
    if (hitTex > 0)
        hitTex -= 15 * deltaTime;
    if (firstFase)
    {
        if (Y1 <= moveTo && !reachPosition)
            setY(Y1 + (speed * deltaTime));
        else if(!reachPosition)
            setY(Y1 - (speed * deltaTime));
        
        if ((Y1 > moveTo && Y1 < moveTo + 10) || (Y1 < moveTo && Y1 > moveTo - 10))
            reachPosition = true;
        coolDownSpawnEnemies -= 3 * deltaTime;
        if (coolDownSpawnEnemies <= 0)
        {
            coolDownSpawnEnemies = 30;
            spawnEnemies = true;
        }
    } else if (secondFase)
    {
        coolDownSpawnEnemies = (coolDownSpawnEnemies > 5) ? 5 : coolDownSpawnEnemies;
        numSpawnEnemies = 4;
        if (Y1 <= 900)
            setY(Y1 + ((speed * 2) * deltaTime));
        coolDownSpawnEnemies -= 3 * deltaTime;
        if (coolDownSpawnEnemies <= 0)
        {
            coolDownSpawnEnemies = 5;
            spawnEnemies = true;
        }
        timeSecondFase -= 3 * deltaTime;
        cout << timeSecondFase << endl;
        if (timeSecondFase <= 0)
        {
            thirdFase = true;
            reachPosition = true;
            coolDownShot = 15;
            secondFase = false;
            timeSecondFase = 70;
        }
    } else if (thirdFase)
    {
        if (reachPosition)
        {
            reachX = (direction) ? 700 : 0;
            reachY = loadEnemys.randomNumber(0, 800);
            reachPosition = false;
        } 

        coolDownSpawnEnemies -= 3 * deltaTime;
        if (coolDownSpawnEnemies <= 0)
        {
            coolDownSpawnEnemies = 15;
            spawnEnemies = true;
        }

        float dx = reachX - X1;
        float dy = reachY - Y1;

        float distance = sqrt(dx * dx + dy * dy);
        if (distance > 0)
        {
            dx /= distance;
            dy /= distance;
        }

        float deltaX = dx * (speed * 1.4) * deltaTime;
        float deltaY = dy * (speed * 1.4) * deltaTime;
        float angleInRadians = atan2(deltaY, deltaX);

        setX(X1 + deltaX);
        setY(Y1 + deltaY);

        if (!direction)
        {
            if (X1 > reachX - 10 && X1 < reachX + 10)
            {
                reachPosition = true;
                direction = !direction;
            }
        }
        else
        {
            if (X2 > reachX - 10 && X2 < reachX + 10)
            {
                reachPosition = true;
                direction = !direction;
            }
        }
    }
    if (life <= 850 && life >= 800 && firstFase && !secondFase)
    {
        secondFase = true;
        firstFase = false;
    }
    if (life <= 400 && life >= 350)
    {
        firstFase = true;
        thirdFase = false;
    }
    animationDead(deltaTime);
}

bool EnemySecondBoss::shot(float deltaTime)
{
    coolDownShot -= 3 * deltaTime;
    if (coolDownShot <= 0)
    {
        coolDownShot = 3;
        /*if (secondFase)
        {
            coolDownShot = 0.2;
        }
        if (thirdFase && contSecondFaseShot >= 0)
        {
            contSecondFaseShot -= 15 * deltaTime;
            coolDownShot = 0.4;
        }
        else if (contSecondFaseShot <= 0)
            contSecondFaseShot = 1.5;*/
        return true;
    }
    return false;
}