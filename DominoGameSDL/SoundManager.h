#pragma once

#include <SDL_mixer.h>

#include <string>
#include <map>

class SoundManager {
public:
	static SoundManager* Instance() {
		if (s_mInstance == 0) {
			s_mInstance = new SoundManager();

			return s_mInstance;
		}

		return s_mInstance;
	}

	bool load(const char* fileName, std::string id);
	void playSound(std::string id, int loop, int ms = 0);

private:
	SoundManager();
	static SoundManager* s_mInstance;
	std::map<std::string, Mix_Chunk*> s_mSfxs;
 };
