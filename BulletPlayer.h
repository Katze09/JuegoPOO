#ifndef BULLETPLAYER_H
#define BULLETPLAYER_H

#include "Object.h"

class BulletPlayer : public Object
{
public:
    BulletPlayer();
    BulletPlayer(HBITMAP sprite, float X1, float Y1);
    virtual ~BulletPlayer();
    void update(double deltaTime);
private:
    int speed;
};

#endif /* BULLETPLAYER_H */

