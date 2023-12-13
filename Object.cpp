#include "Object.h"

Object::Object(HBITMAP sprite, float X1, float Y1) :sprite(sprite), X1(X1), Y1(Y1)
{
    BITMAP bmp;
    GetObject(sprite, sizeof(BITMAP), &bmp);
    WIDTH = bmp.bmWidth;
    HEIGHT = bmp.bmHeight;
    X2 = X1 + WIDTH;
    Y2 = Y1 + HEIGHT;
    X1HitBox = X1 + (WIDTH * 0.1);
    X2HitBox = X2 - (WIDTH * 0.1);
    Y1HitBox = Y1 + (HEIGHT * 0.1);
    Y2HitBox = Y2 - (HEIGHT * 0.1);
}

Object::~Object()
{
    // Destructor
}

HBITMAP Object::getSprite()
{
    return sprite;
}

float Object::getX1()
{
    return X1;
}

float Object::getX2()
{
    return X2;
}

float Object::getY1()
{
    return Y1;
}

float Object::getY2()
{
    return Y2;
}

float Object::getX1HitBox()
{
    return X1HitBox;
}

float Object::getX2HitBox()
{
    return X2HitBox;
}

float Object::getY1HitBox()
{
    return Y1HitBox;
}

float Object::getY2HitBox()
{
    return Y2HitBox;
}

int Object::getWIDTH()
{
    return WIDTH;
}

int Object::getHEIGHT()
{
    return HEIGHT;
}

int Object::getSpeed()
{
    return speed;
}

void Object::setSprite(HBITMAP newSprite)
{
    sprite = newSprite;
}

void Object::setX(float X)
{
    X1 = X;
    X2 = X1 + WIDTH;
    X1HitBox = X1 + (WIDTH * 0.1);
    X2HitBox = X2 - (WIDTH * 0.1);
}

void Object::setY(float Y)
{
    Y1 = Y;
    Y2 = Y1 + HEIGHT;
    Y1HitBox = Y1 + (HEIGHT * 0.1);
    Y2HitBox = Y2 - (HEIGHT * 0.1);
}

void Object::setSpeed(int speed)
{
    this->speed = speed;
}

void Object::draw(HWND hwnd)
{
    HDC hdc = GetDC(hwnd);
    HDC hdcMem = CreateCompatibleDC(hdc);
    SelectObject(hdcMem, sprite);
    // Obtener el tamaño del HBITMAP
    BITMAP bmp;
    GetObject(sprite, sizeof(BITMAP), &bmp);
    // Obtener las coordenadas donde se va a dibujar
    int x = static_cast<int>(X1);
    int y = static_cast<int>(Y1);
    // Dibujar el HBITMAP en la ventana
    BitBlt(hdc, x, y, WIDTH, HEIGHT, hdcMem, 0, 0, SRCCOPY);
    // Liberar recursos
    ReleaseDC(hwnd, hdc); //No eliminar, relentiza todo el pc al ejecutar si los haces
    DeleteDC(hdcMem); //No eliminar, relentiza todo el pc al ejecutar si los haces
}