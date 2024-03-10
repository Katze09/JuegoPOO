/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   AudioPlayer.h
 * Author: Katze
 *
 * Created on 17 de enero de 2024, 16:41
 */

#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <sdl.h>
#include <vector>
#include <string.h>
#include <iostream>
#include <SDL_mixer.h>

class AudioPlayer {
public:
    AudioPlayer();
    virtual ~AudioPlayer();
    void Play(int index, int volume);

private:
    Mix_Music* backgroundMusic;
    std::vector<Mix_Chunk*> audioData;
    int deviceId;
};

#endif /* AUDIOPLAYER_H */

