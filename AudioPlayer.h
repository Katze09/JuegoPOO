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

constexpr int LASER_AUDIO = 0;
constexpr int LASER_EXPLOSION = 1;
constexpr int LASER_LASER_ENEMY = 2;
constexpr int LASER_LASER_ENEMY_LARGE = 3;

class AudioPlayer 
{
public:
    AudioPlayer();
    virtual ~AudioPlayer();
    void Play(int index, int volume);
    void increaseVolume();
    void decreaseVolume();
    void updateMusicVolume();
    float volume = 1.0f;
private:
    Mix_Music* backgroundMusic;
    std::vector<Mix_Chunk*> audioData;
    int deviceId;
};

#endif /* AUDIOPLAYER_H */

