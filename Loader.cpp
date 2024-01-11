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
