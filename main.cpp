#include <iostream>
#include <chrono>
#include "States.h"
#include "Menu.h"
#include <SDL.h>

using namespace std;

States* states;   
Menu* menu;

// Variables globales
float deltaTime;
bool startGame = false;

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("The Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 700, 800, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    const int targetFPS = 60; // Reducido a 60 FPS para hacerlo más estándar
    const int frameDelay = 1000 / targetFPS;

    menu = new Menu(renderer);
    states = new States(renderer);

    auto lastFrameTime = chrono::high_resolution_clock::now();
    bool run = true;
    while (run)
    {
        auto frameStart = chrono::high_resolution_clock::now();
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                run = false;
                break;
            case SDL_KEYDOWN:
                // Manejar el evento de tecla presionada
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    run = false;
                else
                    states->updateInput(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                // Manejar el evento de tecla liberada
                states->inputUp(event.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    int click = menu->click(event.button.x, event.button.y);
                    switch (click)
                    {
                    case 1:
                        startGame = true;
                        break;
                    case 2:
                        startGame = true;
                        states->setPlayer2(renderer);
                    }
                }
                break;
            case SDL_MOUSEMOTION:
                menu->hover(event.motion.x, event.motion.y);
                break;
            }
        }
        // Lógica del juego
        if (startGame)
        {
            states->update(deltaTime);
            // Renderizar
            states->draw(renderer);
        }
        else
        {
            menu->update(deltaTime);
            menu->draw(renderer);
        }

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

        auto frameEnd = chrono::high_resolution_clock::now();
        deltaTime = chrono::duration<float>(frameEnd - lastFrameTime).count();
        lastFrameTime = frameEnd;

        // Dormir el hilo para alcanzar el objetivo de 60 FPS
        auto frameTime = chrono::duration_cast<chrono::milliseconds>(frameEnd - frameStart).count();
        if (frameTime < frameDelay)
            SDL_Delay(static_cast<Uint32>(frameDelay - frameTime));
    }

    delete states;
    delete menu;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}