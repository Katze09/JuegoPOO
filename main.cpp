#include <sdl.h>
#include <iostream>
#include <chrono>
#include "States.h"

using namespace std;


States* states;

// Variables globales
double deltaTime;

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Juego", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 700, 800, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    const int targetFPS = 60; // Reducido a 60 FPS para hacerlo más estándar
    const int frameDelay = 1000 / targetFPS;

    states = new States(renderer);

    auto lastFrameTime = chrono::high_resolution_clock::now();
    bool quit = false;
    while (!quit)
    {
        auto frameStart = chrono::high_resolution_clock::now();
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    // Manejar el evento de tecla presionada
                    states->updateInput(event.key.keysym.sym);
                    break;
                case SDL_KEYUP:
                    // Manejar el evento de tecla liberada
                    states->inputUp(event.key.keysym.sym);
                    break;
            }
        }
        // Lógica del juego
        states->update(deltaTime);
        // Renderizar
        states->draw(renderer);

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

        auto frameEnd = chrono::high_resolution_clock::now();
        deltaTime = chrono::duration<double>(frameEnd - lastFrameTime).count();
        lastFrameTime = frameEnd;

        // Dormir el hilo para alcanzar el objetivo de 60 FPS
        auto frameTime = chrono::duration_cast<chrono::milliseconds>(frameEnd - frameStart).count();
        if (frameTime < frameDelay)
            SDL_Delay(static_cast<Uint32> (frameDelay - frameTime));
    }

    delete states;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}