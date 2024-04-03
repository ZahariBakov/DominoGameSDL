#pragma once

#include <SDL_mixer.h>

#include <string>
#include <map>

class SoundManager
{
private:
    SoundManager();
    ~SoundManager() {};

public:
    static auto Instance() -> SoundManager*;

    auto Load(const char* fileName, std::string id) -> bool;
    void PlaySound(std::string id, int loop, int ms = 0);

private:
    static SoundManager* m_mInstance;
    std::map<std::string, Mix_Chunk*> m_mSfxs;
};
