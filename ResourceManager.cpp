#include "ResourceManager.h"
#include "Application.h"
#include <iostream>

ResourceManager::ResourceManager() {

}

SDL_Texture* ResourceManager::loadTexture(const char* file) {

	// Holding a temporary surface to be converted to an optimized texture shown below
	SDL_Surface* tempSurface = NULL;
	SDL_Texture* optimizedTexture = NULL;

	tempSurface = IMG_Load(file);
	if (tempSurface == nullptr) {
		std::cout << "Error in ResourceManager while loading texture. SDL Error: " << SDL_GetError() << std::endl;
		return NULL;
	} else {
		optimizedTexture = SDL_CreateTextureFromSurface(Application::getInstance().getRender(), tempSurface);

		if (optimizedTexture == nullptr) {
			std::cout << "Could not create texture from surface. SDL Error: " << SDL_GetError() << std::endl;
		}

		SDL_FreeSurface(tempSurface);
	}

	return optimizedTexture;
}

Mix_Music* ResourceManager::loadMusic(const char* file) {

	Mix_Music* loadedMusic = Mix_LoadMUS(file);

	if (loadedMusic == nullptr) {
		std::cout << "Error in ResourceManager while loading music. SDL Error: " << SDL_GetError() << std::endl;
		return NULL;
	}

	return loadedMusic;
}

Mix_Chunk* ResourceManager::loadChunk(const char* file) {
	Mix_Chunk* loadedChunk = Mix_LoadWAV(file);

	if (loadedChunk == nullptr) {
		std::cout << "Error in ResourceManager while loading chunk WAV. SDL Error: " << SDL_GetError() << std::endl;
		return NULL;
	}

	return loadedChunk;
}