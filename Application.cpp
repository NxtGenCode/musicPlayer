#include "Application.h"

Application::Application()
: whiteColor { 255, 255, 255 }, greenColor { 0, 255, 0 }, greyColor { 111, 111, 111 }
{

}

bool Application::initSubSystems() {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Error while initializing the main SDL2 library. SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
		std::cout << "Error while initializing the SDL2_Image library. SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	if (TTF_Init() < 0) {
		std::cout << "Error while initializing the SDL2_TTF library. SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	if (Mix_Init(MIX_INIT_MP3) < 0) {
		std::cout << "Error while initializing the SDL2_Mixer library. SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: %s\n" << Mix_GetError() << std::endl;
		return false;
	}

	return true;
}

bool Application::init(bool fullscreen) {

	if (initSubSystems() == false) {
		return false;
	}

	mainWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600, SDL_WINDOW_SHOWN);

	mainRender = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

	if (mainWindow == NULL || mainRender == NULL) {
		std::cout << "SDL has ran into an error. SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_SetRenderDrawColor(mainRender, 0, 0, 0, 0);

	batmanTexture = ResourceManager::loadTexture("random_bg.jpg");
	if (batmanTexture == nullptr) {
		std::cout << "Error loading background." << std::endl;
	}

	playButton.create(50, 50, 0, 0);
	playButton.setTexture("mButton_004.png");
	playButton.moveToLoc( (800 / 2) - 75, 81);

	pauseButton.create(50, 50, 0, 0);
	pauseButton.setTexture("mButton_003.png");
	pauseButton.moveToLoc((800 / 2) - 75, 81);

	stopButton.create(50, 50, 0, 0);
	stopButton.setTexture("mButton_006.png");
	stopButton.moveToLoc( (800 / 2) - 25, 81);

	nextTrackButton.create(50, 50, 0, 0);
	nextTrackButton.setTexture("mButton_002.png");
	nextTrackButton.moveToLoc((800 / 2) + 25, 81);

	running = true;
	return running;
}

bool Application::loadResources() {
	regularFont = TTF_OpenFont("Arial.ttf", 21);

	// Title Message
	TTF_SetFontStyle(regularFont, TTF_STYLE_UNDERLINE);
	titleMessage.createMessage("Sample Music Player Version 2.0", regularFont, greenColor);
	titleMessage.setPosition((800 / 2) - titleMessage.getWidth() / 2, 0);
	TTF_SetFontStyle(regularFont, TTF_STYLE_NORMAL);

	// Music Status Message
	musicStatusMessage.createMessage("Music is currently not playing", regularFont, greenColor);
	musicStatusMessage.setPosition((800 / 2) - musicStatusMessage.getWidth() / 2, 20);

	// Music Timer Message
	musicTimerMessage.createMessage(musicClock.toString(), regularFont, greenColor);
	musicTimerMessage.setPosition((800 / 2) - musicTimerMessage.getWidth() / 2, 45);

	musicSample = ResourceManager::loadMusic("icecube_gangster_rap.mp3");
	return true;
}

void Application::handleApplication() {

	SDL_Event userEvent;

	while (running == true) {
		startTicks = SDL_GetTicks();

		while (SDL_PollEvent(&userEvent)) {
			handleEvents(userEvent);
		}

		update();
		render();

		if (musicClock.isStarted() && Mix_PlayingMusic() == 1) {
				musicTimerMessage.createMessage(musicClock.toString(), regularFont, greenColor);
				musicTimerMessage.setPosition((800 / 2) - musicTimerMessage.getWidth() / 2, 45);
		} else {
				musicClock.resetClock();
		}

		// Regulate Frame Rate Here When Needed
		if ((unsigned)MAX_FRAMES_PER_SECOND > SDL_GetTicks() - startTicks)
			SDL_Delay(MAX_FRAMES_PER_SECOND - (SDL_GetTicks() - startTicks));
	}

}

void Application::update() {
	if (musicTimer.isStarted() == true && musicClock.isStarted() == false) {
		musicClock.start();
	}
	if (musicClock.isStarted() == true) {
		musicClock.update(true);
	}
}

void Application::handleEvents(SDL_Event& userEvent) {
	if (userEvent.type == SDL_QUIT)
		running = false;

	if (userEvent.type == SDL_KEYDOWN) {
		switch (userEvent.key.keysym.sym) {

			case SDLK_F1: // Play Music
				playMusic(musicSample);
			break;

			case SDLK_F2: // Stop Music
				stopMusic();
			break;

			case SDLK_F3: // Pause Music && Resume Music
				pauseMusic();
			break;

		}
	} else if (userEvent.type == SDL_MOUSEBUTTONDOWN) {
		switch (userEvent.button.button) {
			case SDL_BUTTON_LEFT:

				// Play & pause button
				if (userEvent.motion.x >= playButton.getX() &&
					userEvent.motion.x <= playButton.getX() + playButton.getWidth() &&
					userEvent.motion.y >= playButton.getY() &&
					userEvent.motion.y <= playButton.getY() + playButton.getheight()) {
					if (Mix_PlayingMusic() == 0) {
						playMusic(musicSample);
					}
					else
						pauseMusic();
				}

				// Stop button
				if (userEvent.motion.x >= stopButton.getX() &&
					userEvent.motion.x <= stopButton.getX() + stopButton.getWidth() &&
					userEvent.motion.y >= stopButton.getY() &&
					userEvent.motion.y <= stopButton.getY() + stopButton.getheight()) {
					stopMusic();
				}

				// Next button

			break;
		}

		std::cout << "Mouse X: " << userEvent.motion.x << std::endl;
		std::cout << "Mouse Y: " << userEvent.motion.y << std::endl;
	}

}

void Application::render()  {
	if (mainRender == nullptr) {
		std::cout << "Error while rendering Application. SDL Error: " << SDL_GetError() << std::endl;
		return;
	}

	SDL_RenderClear(mainRender);
	SDL_RenderCopy(mainRender, batmanTexture, NULL, NULL);

	if (Mix_PlayingMusic() == 1 && Mix_PausedMusic() == 0) // Pause
		pauseButton.draw(mainRender);
	else
		playButton.draw(mainRender);

	stopButton.draw(mainRender);
	nextTrackButton.draw(mainRender);

	titleMessage.draw(mainRender);
	musicStatusMessage.draw(mainRender);
	musicTimerMessage.draw(mainRender);
	SDL_RenderPresent(mainRender);
}

SDL_Renderer* Application::getRender() {
	return mainRender;
}

void Application::free() {
	titleMessage.free();
	musicStatusMessage.free();
	musicTimerMessage.free();
	playButton.free();
	pauseButton.free();
	stopButton.free();
	nextTrackButton.free();
	SDL_DestroyTexture(batmanTexture);
	Mix_FreeMusic(musicSample);
	SDL_DestroyRenderer(mainRender);
	SDL_DestroyWindow(mainWindow);

	TTF_CloseFont(regularFont);
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();
}

void Application::playMusic(Mix_Music * music)
{
	if (Mix_PlayingMusic() == 0) {
		std::cout << "Ran music action!" << std::endl;

		while (Mix_PlayMusic(music, 0) == -1) {
			std::cout << "Hi" << std::endl;
		}
		musicStatusMessage.createMessage("Music is currently playing", regularFont, greenColor);
		musicStatusMessage.setPosition((800 / 2) - musicStatusMessage.getWidth() / 2, 20);

		musicTimer.start();
	}
}

void Application::pauseMusic()
{
	if (Mix_PlayingMusic() == 1 && Mix_PausedMusic() == 0) { // Pause
		std::cout << "Pause music action!" << std::endl;
		Mix_PauseMusic();
		musicStatusMessage.createMessage("Music is currently paused", regularFont, greenColor);
		musicStatusMessage.setPosition((800 / 2) - musicStatusMessage.getWidth() / 2, 20);
		if (musicTimer.isPaused() == false) {
			musicTimer.pause();
			musicClock.pause();
		}
	}
	else if (Mix_PausedMusic() == 1) { // Resume
		std::cout << "Unpause music action!" << std::endl;
		Mix_ResumeMusic();
		musicStatusMessage.createMessage("Music is currently playing", regularFont, greenColor);
		musicStatusMessage.setPosition((800 / 2) - musicStatusMessage.getWidth() / 2, 20);
		if (musicTimer.isPaused() == true) {
			musicTimer.resume();
			musicClock.resume();
		}
	}
}
void Application::stopMusic()
{
	if (Mix_PlayingMusic() == 1) {
		std::cout << "Stop music action!" << std::endl;
		Mix_HaltMusic();
		musicStatusMessage.createMessage("Music is currently stopped", regularFont, greenColor);
		musicStatusMessage.setPosition((800 / 2) - musicStatusMessage.getWidth() / 2, 20);
		musicTimer.stop();
		musicClock.resetClock();
		musicClock.stop();
	}
}
