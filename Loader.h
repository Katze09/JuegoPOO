#ifndef LOADER_H
#define LOADER_H

#include <iostream>
#include <string>
#include <tchar.h>
#include <sdl.h>
#include "Level.h"
#include <chrono>
#include "Level.h"
#include "tinyxml2.h"
#include <cstring>
#include "AudioPlayer.h"
#include <sdl_image.h>
#include <cstdlib>

using namespace std;

class Loader 
{
public:
    //HBITMAP LoadSprite(const std::string& name);
    SDL_Texture* LoadTexture(const std::string& filePat, SDL_Renderer* renderer);
    int randomNumber(int i, int j);
    vector<SDL_Texture*> loadTextures(string nameFile[], SDL_Renderer* renderer, int sizeNames);
    Level* LoadLevel(int level, SDL_Renderer* renderer, AudioPlayer* audioPlayer);
    
};
#endif /* LOADER_H */

