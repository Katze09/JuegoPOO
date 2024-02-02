#include "AudioPlayer.h"

AudioPlayer::AudioPlayer() : deviceId(0)
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 4096) == -1)
        std::cerr << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
    std::vector<std::string> audioFiles = {"Audio/Laser.wav", "Audio/Explosion.wav", "Audio/LaserEnemy.mp3", "Audio/LaserEnemyLarge.mp3"};
    backgroundMusic = Mix_LoadMUS("Audio/AudioMusic.mp3");
    Mix_PlayMusic(backgroundMusic, -1);
    for (const auto& file : audioFiles)
    {
        Mix_Chunk* sound = Mix_LoadWAV(file.c_str());
        if (sound == nullptr)
            std::cerr << "Mix_LoadWAV Error: " << Mix_GetError() << std::endl;
        audioData.push_back(sound);
    }
    Mix_AllocateChannels(16); // Número máximo de canales simultáneos
}

AudioPlayer::~AudioPlayer()
{
    for (auto sound : audioData)
        Mix_FreeChunk(sound);
    Mix_FreeMusic(backgroundMusic);
    Mix_CloseAudio();
    SDL_Quit();
}

void AudioPlayer::Play(int index, int volume)
{
    if (index < 0 || index >= static_cast<int> (audioData.size()))
        std::cerr << "Invalid audio index." << std::endl;
    volume = std::max(0, std::min(MIX_MAX_VOLUME, volume));

    // Establecer el volumen del canal de mezcla
    Mix_VolumeChunk(audioData[index], volume);

    Mix_PlayChannel(-1, audioData[index], 0);
}