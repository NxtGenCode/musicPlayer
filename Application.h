#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <SDL_ttf.h>
#include <sstream>

#include "Timer.h"
#include "TtfMessage.h"
#include "ResourceManager.h"
#include "Clock.h"
#include "Button.h"

class Application
{

	private:
		bool running;

		Uint32 startTicks = 0;
		const int FPS = 30;
		const int MAX_FRAMES_PER_SECOND = 1000 / FPS;

		const char* WINDOW_TITLE = "Sample Music Player Version 2.0";

		SDL_Window* mainWindow;
		SDL_Renderer* mainRender;

		Timer musicTimer;
		Clock musicClock;

		Button playButton;
		Button pauseButton;
		Button stopButton;

		TTF_Font* regularFont;
		SDL_Color whiteColor;
		SDL_Color greenColor;
		SDL_Color greyColor;
		SDL_Texture* blueTexture;
		SDL_Texture* batmanTexture;
		TtfMessage titleMessage, musicStatusMessage, musicTimerMessage;

		Mix_Music* musicSample;

	public:
		Application();

	public:
		static Application& getInstance() {
			static Application p_sInstance;

			return p_sInstance;
		}

		bool initSubSystems();
		bool init(bool fullscreen = false);
		bool loadResources();
		void handleApplication();
		void update();
		void handleEvents(SDL_Event& userEvent);
		void render();
		void free();

		bool isRunning() { return running; }
		SDL_Renderer* getRender();
};

#endif /* _APPLICATION_H_ */