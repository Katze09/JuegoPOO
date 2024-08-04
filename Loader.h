#pragma once 

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <random>
#include "Level.h"
#include <chrono>
#include "tinyxml2.h"
#include <cstring>
#include "AudioPlayer.h"
#include <SDL_image.h>
#include <cstdlib>

namespace Loader
{
	SDL_Texture* loadTexture(const std::string& filePat, SDL_Renderer* renderer);
	int randomNumber(int i, int j);
	std::vector<SDL_Texture*> loadTextures(std::string nameFile[], SDL_Renderer* renderer, int sizeNames);
	std::vector<std::string> loadLeaderBoard(int numPlayers);
	void updateLeaderBoard(std::string name, int score, int deaths, std::string nameTodelete, int numPlayers);
	class Level* loadLevel(int level, SDL_Renderer* renderer, AudioPlayer** audioPlayer);
	std::string base64_encode(const std::string& in);
	std::string base64_decode(const std::string& in);
	Uint32 getElapsedTime(Uint32 start);
};