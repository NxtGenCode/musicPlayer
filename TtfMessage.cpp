#include "TtfMessage.h"
#include "Application.h"

TtfMessage::TtfMessage()
: message(""), messageBounds{ 0, 0, 0, 0 }, messageTexture(NULL), width(0), height(0)
{

}

bool TtfMessage::createMessage(std::string message, TTF_Font* font, SDL_Color textColor) {

	// Disposes of the newest texture if it's used
	if (messageTexture != nullptr) {
		SDL_DestroyTexture(messageTexture);
		messageTexture = nullptr;
	}

	// Create message from a surface and convert to the actual texture
	SDL_Surface* tempS = TTF_RenderText_Solid(font, message.c_str(), textColor);
	if (tempS == nullptr) {
		std::cout << "Error while creating message. SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	else {
		messageTexture = SDL_CreateTextureFromSurface(Application::getInstance().getRender(), tempS);
		messageBounds = { 0, 0, tempS->w, tempS->h };
		width = tempS->w;
		height = tempS->h;
		SDL_FreeSurface(tempS);

		if (messageTexture == nullptr) {
			std::cout << "Error while creating message. SDL Error: " << SDL_GetError() << std::endl;
			return false;
		}
	}

	return true;
}

void TtfMessage::setPosition(int x, int y) {
	messageBounds.x = x;
	messageBounds.y = y;
}

void TtfMessage::draw(SDL_Renderer* render) {
	SDL_RenderCopy(render, messageTexture, NULL, &messageBounds);
}

void TtfMessage::free() {
	SDL_DestroyTexture(messageTexture);
}


int TtfMessage::getWidth() {
	return width;
}

int TtfMessage::getHeight() {
	return height;
}
