#include "Background.h"

Background::Background(){}

Background::Background(HBITMAP sprite)
{
    this->sprite = sprite;
    X = 0;
    Y1 = 0;
    Y2 = -950;
    speed = 2;
}

Background::~Background()
{
}

void Background::update(double deltaTime)
{
    Y1 += speed; //* deltaTime;
    Y2 += speed; //* deltaTime;
    if(Y1 > 950)
        Y1 = -950;
    if(Y2 > 950)
        Y2 = -950;
}

void Background::draw(HWND hwnd)
{
    //Dibujar Fondo 1
    HDC hdc = GetDC(hwnd);
    HDC hdcMem = CreateCompatibleDC(hdc);
    SelectObject(hdcMem, sprite);
    // Obtener el tamaño del HBITMAP
    BITMAP bmp;
    GetObject(sprite, sizeof(BITMAP), &bmp);
    // Obtener las coordenadas donde se va a dibujar
    int x = static_cast<int>(X);
    int y = static_cast<int>(Y1);
    // Dibujar el HBITMAP en la ventana
    BitBlt(hdc, x, y, bmp.bmWidth, bmp.bmHeight, hdcMem, 0, 0, SRCCOPY);
    // Liberar recursos
    ReleaseDC(hwnd, hdc); //No eliminar, relentiza todo el pc al ejecutar si los haces
    DeleteDC(hdcMem); //No eliminar, relentiza todo el pc al ejecutar si los haces
    
    //Dibujar Fondo 2
    hdc = GetDC(hwnd);
    hdcMem = CreateCompatibleDC(hdc);
    SelectObject(hdcMem, sprite);
    // Obtener el tamaño del HBITMAP
    GetObject(sprite, sizeof(BITMAP), &bmp);
    // Obtener las coordenadas donde se va a dibujar
    x = static_cast<int>(X);
    y = static_cast<int>(Y2);
    // Dibujar el HBITMAP en la ventana
    BitBlt(hdc, x, y, bmp.bmWidth, bmp.bmHeight, hdcMem, 0, 0, SRCCOPY);
    // Liberar recursos
    ReleaseDC(hwnd, hdc); //No eliminar, relentiza todo el pc al ejecutar si los haces
    DeleteDC(hdcMem); //No eliminar, relentiza todo el pc al ejecutar si los haces
}