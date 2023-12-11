#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <iostream>
#include <windows.h>

using namespace std;

class Background 
{
public:
    Background();
    Background(HBITMAP sprite);
    virtual ~Background();
    void update(double deltaTime);
    void draw(HWND hwnd);
private:
    HBITMAP sprite;
    int X;
    int Y1;
    int Y2;
    int speed;
};

#endif /* BACKGROUND_H */

