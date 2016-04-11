#include "Timer.h"
#include <iostream>
#include <SDL.h>

Timer::Timer(bool start)
{
	if (start == true) {
		this->start();
	}

	started = false;
	paused = false;
	startTicks = 0;
	pausedTicks = 0;
}

void Timer::start() {
	if (started == false) {
		started = true;
		startTicks = SDL_GetTicks();
	}
}

void Timer::stop() {
	if (started == true) {
		started = false;
		paused = false;
		startTicks = 0;
		pausedTicks = 0;
	}
}

void Timer::update(bool intervalOn) {

}

void Timer::reset(bool autoStart) {
	startTicks = 0;
	pausedTicks = 0;
	started = false;
	paused = false;
	if (autoStart == true) {
		start();
	}
	
}

void Timer::pause() {
	if (paused == false) {
		paused = true;
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void Timer::resume() {
	if (paused == true) {
		paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

int Timer::getTicks() {
	if (paused == true) {
		return (int)(pausedTicks / 1000.0f);
	}

	return ((int)(SDL_GetTicks() - startTicks) / (int)1000.0f);
}

bool Timer::isStarted() {
	return started;
}

bool Timer::isPaused() {
	return paused;
}