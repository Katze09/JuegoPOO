#include "Object.h"

Object::Object(HBITMAP sprite, float X1, float Y1) :sprite(sprite), X1(X1), Y1(Y1)
{
    BITMAP bmp;
    GetObject(sprite, sizeof(BITMAP), &bmp);
    WIDTH = bmp.bmWidth;
    HEIGHT = bmp.bmHeight;
    X2 = X1 + WIDTH;
    Y2 = Y1 + HEIGHT;
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

void Object::setSprite(HBITMAP newSprite)
{
    sprite = newSprite;
}

void Object::setX(float X)
{
    X1 = X;
    X2 = X1 + WIDTH;
}

void Object::setY(float Y)
{
    Y1 = Y;
    Y2 = Y1 + HEIGHT;
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