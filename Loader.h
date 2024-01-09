#ifndef LOADER_H
#define LOADER_H

#include <iostream>
#include <string>
#include <tchar.h>
#include <sdl.h>

using namespace std;

class Loader {
public:
    //HBITMAP LoadSprite(const std::string& name);
    SDL_Texture* LoadTexture(const std::string& filePat, SDL_Renderer* renderer);
};
#endif /* LOADER_H */

