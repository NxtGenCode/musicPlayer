#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class ResourceManager
{

	private:
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;

	public:
		ResourceManager();

		static ResourceManager& getInstance() {
			static ResourceManager p_sInstance;

			return p_sInstance;
		}

		SDL_Texture* loadTexture(const char* file);
		Mix_Music* loadMusic(const char* file);
		Mix_Chunk* loadChunk(const char* file);
};

#endif /* _RESOURCE_MANAGER_H_ */
