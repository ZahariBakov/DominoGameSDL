#include "SoundManager.h"

#include <iostream>

bool SoundManager::Load(const char* fileName, std::string id)
{
	Mix_Chunk* chunk = Mix_LoadWAV(fileName);

    if(chunk == 0)
    {
		std::cout << "Could not load sfx " << Mix_GetError() << std::endl;
		return false;
	}

    m_mSfxs[id] = chunk;

	return true;
}

void SoundManager::PlaySound(std::string id, int loop, int ms)
{
    if(Mix_FadeInChannel(-1, m_mSfxs[id], loop, ms) == -1)
    {
		std::cout << Mix_GetError() << std::endl;
	}
}

SoundManager::SoundManager() {
    if(Mix_OpenAudio(48000, AUDIO_S16SYS, 2, 4096) == -1)
    {
		std::cout << Mix_GetError() << std::endl;
    }
}

SoundManager *SoundManager::Instance()
{
    if(m_mInstance == nullptr)
    {
        m_mInstance = new SoundManager();

        return m_mInstance;
    }

    return m_mInstance;
}

SoundManager* SoundManager::m_mInstance = 0;
