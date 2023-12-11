#include <Windows.h>
#include <iostream>
#include <thread>
#include "States.h"

using namespace std;


// Declaración de funciones
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


void draw(HWND hwnd);
void update();
States* states;

// Variables globales
HWND hwnd;
double deltaTime;

int main()
{
    states = new States();
    // Crear la ventana
    WNDCLASSW wc = {}; // Cambiado a WNDCLASSW para usar cadenas de caracteres amplios
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(0);
    wc.lpszClassName = L"GameWindowClass"; // L indica una cadena de caracteres amplios
    RegisterClassW(&wc); // Cambiado a RegisterClassW para usar cadenas de caracteres amplios

    hwnd = CreateWindowExW(
            0, // Estilo de ventana extendida
            L"GameWindowClass", // Nombre de la clase (cadena de caracteres amplios)
            L"Mi Juego", // Título de la ventana (cadena de caracteres amplios)
            WS_OVERLAPPEDWINDOW, // Estilo de ventana
            CW_USEDEFAULT, CW_USEDEFAULT, // Posición de la ventana
            700, 900, // Tamaño de la ventana
            0, // Asa de instancia
            0, // Asa de menú
            GetModuleHandle(0), // Asa de instancia
            0 // Parametros adicionales
            );

    if (hwnd == NULL)
    {
        return 1;
    }

    // Mostrar y actualizar la ventana
    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    // Bucle principal
    MSG msg = {};
    const int targetFPS = 60;
    const int frameDelay = 1000 / targetFPS;

    auto lastFrameTime = std::chrono::high_resolution_clock::now();

    while (msg.message != WM_QUIT)
    {
        auto frameStart = std::chrono::high_resolution_clock::now();
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // Lógica del juego
            update();
            // Renderizar
            draw(hwnd);
            // Calcular el delta time
            auto frameEnd = std::chrono::high_resolution_clock::now();
            deltaTime = std::chrono::duration<double>(frameEnd - lastFrameTime).count();;
            lastFrameTime = frameEnd;
            // Dormir el hilo para alcanzar el objetivo de 60 FPS
            auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart).count();
            if (frameTime < frameDelay)
                Sleep(static_cast<DWORD>(frameDelay - frameTime));
        }
    }

    delete states;
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_KEYDOWN:
            states->updateInput(wParam);
            break;
        case WM_KEYUP:
            states->stopMove();
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

// Función de actualización del juego

void update()
{
    states->update(deltaTime);
}

// Función de dibujo del juego

void draw(HWND hwnd)
{
    states->draw(hwnd);
}
