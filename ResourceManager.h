#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class ResourceManager
{

	private:
		ResourceManager();

	public:
		static SDL_Texture* loadTexture(const char* file);
		static Mix_Music* loadMusic(const char* file);
		static Mix_Chunk* loadChunk(const char* file);
};

#endif /* _RESOURCE_MANAGER_H_ */