#include "Button.h"
#include "ResourceManager.h"
#include <iostream>

Button::Button() : x(0), y(0), width(10), height(10), m_texture(nullptr), buttonRect { 0,0,0,0 } {

}

Button::Button(int w, int h) {
	buttonRect.w = w;
	buttonRect.h = h;
}

Button::Button(int w, int h, int x, int y) {
	buttonRect.w = w;
	buttonRect.h = h;
	buttonRect.x = x;
	buttonRect.y = y;
}

void Button::setTexture(const char* texturePath) {
	if (m_texture == nullptr) {
		m_texture = ResourceManager::loadTexture(texturePath);

		if (m_texture == nullptr)
			std::cout << "Error setting texture to button! SDL Error: " << SDL_GetError() << std::endl;
	}
}

ActionType Button::handleEvents(SDL_Event* event, static ActionType action)
{
	if (event->type == SDL_MOUSEBUTTONDOWN) {
		if (event->motion.x >= buttonRect.x && event->motion.x <= buttonRect.x + buttonRect.w &&
			event->motion.y >= buttonRect.y && event->motion.y <= buttonRect.y + buttonRect.h) {
			
			switch (action) {

			case ActionType::PLAY_ACTION:
				std::cout << "\nPlay action ran!\n";
				return action;
			break;

			case ActionType::PAUSE_ACTION:
				std::cout << "\nPause action ran!\n";
				return action;
			break;

			case ActionType::STOP_ACTION:
				std::cout << "\nStop action ran!\n";
				return action;
			break;

			case ActionType::EXIT_ACTION:
				std::cout << "\nExit action ran!\n";
				return action;
			break;

			default: std::cout << "\nError when handling button event!\n"; break;
			}

		}
	}

	return ActionType::NO_ACTION;
}

void Button::create(int w, int h, int x, int y) {
	buttonRect.w = w;
	buttonRect.h = h;
	buttonRect.x = x;
	buttonRect.y = y;
}

void Button::move(int x, int y)
{
}

void Button::moveToLoc(int x, int y) {
	this->x = x;
	this->y = y;
	buttonRect.x = x;
	buttonRect.y = y;
}
void Button::draw(SDL_Renderer* render) {
	if (render == nullptr) {
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		return;
	}

	// Draw here
	if (m_texture != nullptr)
		SDL_RenderCopy(render, m_texture, NULL, &buttonRect);
	else
		std::cout << "Error rendering button! SDL Error: " << SDL_GetError() << std::endl;
}

bool Button::resize(int w, int h)
{
	return false;
}

void Button::free() {
	SDL_DestroyTexture(m_texture);
	m_texture = nullptr;
	buttonRect = { 0 };
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}
