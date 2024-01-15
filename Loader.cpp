#include "Loader.h"

SDL_Texture* Loader::LoadTexture(const std::string& filePath, SDL_Renderer* renderer)
{
    const std::string& path = "Textures/" + filePath + ".bmp";
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture)
        cerr << "Hubo un problema al cargar la textura " << filePath << ".bmp, verifica si el nombre esta correcto, o si el archivo existe." << endl;
    return texture;
}

bool comp = true;

int Loader::randomNumber(int i, int j)
{
    auto now = std::chrono::system_clock::now();
    auto seed = 0;
    if (comp)
        seed = static_cast<int> (std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count());
    else
        seed = static_cast<int> (std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count());
    comp = !comp;
    auto independentClock = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    seed += static_cast<int> (independentClock);
    std::random_device rd;
    seed += rd();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(i, j);
    return distribution(generator);
}
