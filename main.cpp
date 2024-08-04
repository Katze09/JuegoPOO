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

static void resetWindow(SDL_Window*& window, SDL_Renderer*& renderer, int width, int height)
{
    if (renderer) 
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    window = SDL_CreateWindow("The Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (SDL_RenderSetLogicalSize(renderer, 700, 800) != 0)
        cerr << "Failed to set logical size! SDL_Error: " << SDL_GetError() << endl;

    States* tempStates = states;
    Menu* tempMenu = menu;

    menu = new Menu(renderer);
    states = new States(renderer);
    states->setAudioPlayer(tempStates->audioPlayer);
    states->audioPlayer->updateMusicVolume();
    menu->setAudioPlayer(&states->audioPlayer);
    menu->setStartResolution(tempMenu->startResolution);

}

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("The Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 700, 800, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (SDL_RenderSetLogicalSize(renderer, 700, 800) != 0)
        cerr << "Failed to set logical size! SDL_Error: " << SDL_GetError() << endl;

    const int targetFPS = 60; // Reducido a 60 FPS para hacerlo más estándar
    const int frameDelay = 1000 / targetFPS;

    menu = new Menu(renderer);
    states = new States(renderer);
    menu->setAudioPlayer(&states->audioPlayer);

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
                    states->mouseClick(event.button.x, event.button.y);
                    if (!startGame)
                    {
                        int click = menu->click(event.button.x, event.button.y);
                        switch (click)
                        {
                        case 1:
                            startGame = true;
                            states->start = SDL_GetTicks();
                            break;
                        case 2:
                            startGame = true;
                            states->setPlayer2(renderer);
                            states->start = SDL_GetTicks();
                            break;
                        }
                    }
                }
                break;
            case SDL_MOUSEMOTION:
                if(!startGame)
                    menu->hover(event.motion.x, event.motion.y);
                states->mouseMove(event.motion.x, event.motion.y);
                break;
            case SDL_TEXTINPUT:
                states->leaderboard.updateInput(std::string(event.text.text));
                break;
            }
        }
        // Lógica del juego
        if (startGame)
        {
            states->update(deltaTime);
            states->draw(renderer);
        }
        else
        {
            menu->update(deltaTime);
            menu->draw(renderer);
        }

        if (menu->changeResolution)
        {
            resetWindow(window, renderer, menu->widthRes[menu->startResolution], menu->heightRes[menu->startResolution]);
            menu->changeResolution = false;
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