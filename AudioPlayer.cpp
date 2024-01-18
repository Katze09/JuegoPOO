/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   AudioPlayer.cpp
 * Author: Katze
 * 
 * Created on 17 de enero de 2024, 16:41
 */

#include "AudioPlayer.h"
#include <sdl.h>

AudioPlayer::AudioPlayer()
{
    /*if (SDL_Init(SDL_INIT_AUDIO) < 0)
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    
    string audioName[] = {"Laser"};
    if (SDL_LoadWAV("example.wav", &wavSpec, &wavStart, &wavLength) == nullptr) {
        std::cerr << "SDL_LoadWAV Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(nullptr, 0, &wavSpec, nullptr, 0);
    if (deviceId == 0) {
        std::cerr << "SDL_OpenAudioDevice Error: " << SDL_GetError() << std::endl;
        SDL_FreeWAV(wavStart);
        SDL_Quit();
        return 1;
    }

    SDL_QueueAudio(deviceId, wavStart, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);*/
}

AudioPlayer::~AudioPlayer()
{
}

